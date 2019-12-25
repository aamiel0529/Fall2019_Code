; partners: weustis2, rmohta2

; Introduction: In this MP, we are making an LC-3 calculator that
; evalutes postfix expressions. Stacks are utilized in this assignment.
; Whenever an operand is entered, it is pushed to the stack, and whenever
; an operator is entered, 2 values are popped from the stack, and the result
; of that is pushed back onto the stack. When the equal sign is entered, and
; there's only one value in the stack (otherwise it's an invalid expression),
; the result is loaded into R5 and then converted
; to hexadecimal format and printed to the screen.
; When a valid operand is entered, the push subroutine will be used, and then we will
; go back to get another input. When a valid operator is entered, the pop subroutine will
; be used, and program would go to either the add, subtract, multiply, divide, or power
; subroutine. Then the push subroutine will be implemented again to put the result onto
; the stack. When an invalid input character is entered, or if there's a stack underflow
; when popping, or if the stack doesn't have one value when the equal sign is encountered
; the message, "Invalid Expression" will be printed.


.ORIG x3000
	
;your code goes here
	
GET_CHAR
			GETC
			OUT

			; Input character loaded into R0

			; R0 = '='
			LD R1, ASCII_EQUAL
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_CHECK_STACK

			; R0 = ' '
			LD R1, ASCII_SPACE
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GET_CHAR

			; R0 = '0'
			LD R1, ASCII_0
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_PUSH

			; R0 = '1'
			LD R1, ASCII_1
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_PUSH

			; R0 = '2'
			LD R1, ASCII_2
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_PUSH

			; R0 = '3'
			LD R1, ASCII_3
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_PUSH

			; R0 = '4'
			LD R1, ASCII_4
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_PUSH

			; R0 = '5'
			LD R1, ASCII_5
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_PUSH

			; R0 = '6'
			LD R1, ASCII_6
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_PUSH

			; R0 = '7'
			LD R1, ASCII_7
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_PUSH

			; R0 = '8'
			LD R1, ASCII_8
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_PUSH

			; R0 = '9'
			LD R1, ASCII_9
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_PUSH

			; R0 = '+'
			LD R1, ASCII_PLUS
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_PLUS

			; R0 = '-'
			LD R1, ASCII_MINUS
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_MINUS

			; R0 = '*'
			LD R1, ASCII_MULTIPLY
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_MULTIPLY

			; R0 = '/'
			LD R1, ASCII_DIVIDE
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_DIVIDE

			; R0 = '^'
			LD R1, ASCII_POWER
			NOT R1, R1
			ADD R1, R1, #1
			ADD R1, R0, R1
			BRz GO_TO_POWER

			; If R0 doesn't equal any of the above, it's an invalid character.
			LEA R0, INVALID_EXPRESSION
			PUTS
			HALT


ASCII_0 .FILL x0030
ASCII_1 .FILL x0031
ASCII_2 .FILL x0032
ASCII_3 .FILL x0033
ASCII_4 .FILL x0034
ASCII_5 .FILL x0035
ASCII_6 .FILL x0036
ASCII_7 .FILL x0037
ASCII_8 .FILL x0038
ASCII_9 .FILL x0039

ASCII_SPACE .FILL x0020
ASCII_PLUS .FILL x002B
ASCII_MINUS .FILL x002D
ASCII_MULTIPLY .FILL x002A
ASCII_DIVIDE .FILL x002F
ASCII_POWER .FILL x005E
ASCII_EQUAL .FILL x003D
ASCII_OFFSET .FILL XFFD0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PRINT_HEX

ST R5, PRINTHEX_SaveR5 ; save R5 (which contains result)

; Register Table:
; R0: temporarily stores digit before printing
; R1: digit counter (shows how many digits remain to be printed)
; R2: bit counter (shows how many bits in a 4-bit group remain to be read)
; R3: contains a 16-bit number
; R4: contains digit (4 bits)
; R5: contains offset ('A' - 10) for hex letters
; R6: contains offset (x0030) for ASCII '0'
; R7: unused

			ADD R3, R5, #0 ; result in R5 loaded into R3 for printing
			LD R5, OFFSET_1 ; offset for hex letters loaded into R5
			LD R6, OFFSET_2 ; offset for ASCII '0' loaded into R6

			AND R1, R1, #0
			ADD R1, R1, #4 ; digit counter initialized to 4

NEXT_DIGIT 
			ADD R1, R1, #0 ; set condition codes to R1 (digit counter)
			BRz DONE_PRINT ; halt program if all 4 digits have been printed

			AND R2, R2, #0
			ADD R2, R2, #4 ; bit counter initialized to 4
			AND R4, R4, #0 ; digit initialized to 0

NEXT_BIT 
			ADD R2, R2, #0 ; set condition codes to R2 (bit counter)
			BRz PRINT_READY ; get ready to print digit if 4 bits have been gotten from R2

			ADD R4, R4, R4 ; shift digit left
			ADD R3, R3, #0 ; set condition codes to R3
			BRzp SHIFT ; branch if MSB is 0 (R3 is not negative)
			ADD R4, R4, #1 ; add 1 to digit if R3 is negative
SHIFT 
			ADD R3, R3, R3 ; shift R3 left

			ADD R2, R2, #-1 ; decrement bit counter
			BRnzp NEXT_BIT

PRINT_READY 
			ADD R4, R4, #-9 ; checking if digit is <= 9 or > 9
			BRnz ADD_0 ; branch if digit <= 9
			ADD R4, R4, #9 ; restore original value for R4
			ADD R4, R4, R5 ; add offset ('A' - 10) for hex letters
			BRnzp PRINT ;

ADD_0 
			ADD R4, R4, #9 ; restore original value for R4
			ADD R4, R4, R6 ; add offset (x0030) for ASCII '0'

PRINT 
			ADD R0, R4, #0 ; put digit into R0 so it can be printed
			OUT ; print digit to monitor

			ADD R1, R1, #-1 ; decrement digit counter
			BRnzp NEXT_DIGIT

DONE_PRINT
			LD R5, PRINTHEX_SaveR5 ; result back into R5
			;  do not need to load original values back into other registers
			;  because program has halted, don't need them anymore
			HALT

OFFSET_1 .FILL x0037
OFFSET_2 .FILL x0030

PRINTHEX_SaveR5 .BLKW #1



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here


GO_TO_CHECK_STACK
			LD R3, STACK_START
			LD R4, STACK_TOP
			ADD R4, R4, #1
			NOT R4, R4
			ADD R4, R4, #1				
			ADD R4, R3, R4				;CHECK IF THERE'S 1 VALUE IN STACK
			BRnp INVALID_EXPRESSION		;IF NOT, IT IS INVALID
			LDI R5, STACK_START			;OTHERWISE LOAD THE VALUE INTO R5 
			BRnzp PRINT_HEX				;GO TO PRINT VALUE TO SCREEN
			

GO_TO_PUSH
			LD R2, ASCII_OFFSET			;CONVERT ASCII HEX TO CORRESPONDING DECIMAL VALUE
			ADD R0, R0, R2
			JSR PUSH					;PUSH TO STACK
			BRnzp GET_CHAR				;GET NEXT CHAR

GO_TO_PLUS
			JSR POP						;POP AND CHECK IF IT IS VALID
				ADD R5, R5, #0
				BRp UNDER_FLOW_ERROR
				AND R4, R4, #0
				ADD R4, R4, R0			;PUT VAL TO R4
			JSR POP						;POP SECOND VAL AND CHECK IF VALID
				ADD R5, R5, #0
				BRp UNDER_FLOW_ERROR
				AND R3, R3, #0			
				ADD R3, R3, R0			;PUT VAL TO R3
			JSR PLUS					;ADD SUB ROUTINE
			JSR PUSH					;PUSH (R4+R3) ONTO STACK
			BRnzp GET_CHAR

GO_TO_MINUS
			JSR POP						;POP AND CHECK IF IT IS VALID
				ADD R5, R5, #0
				BRp UNDER_FLOW_ERROR
				AND R3, R3, #0
				ADD R3, R3, R0			;PUT VAL TO R3
			JSR POP						;POP SECOND VAL AND CHECK IF VALID
				ADD R5, R5, #0
				BRp UNDER_FLOW_ERROR
				AND R4, R4, #0
				ADD R4, R4, R0			;PUT VAL TO R4
			JSR MIN						;CALL MINUS SUB ROUTINE
			JSR PUSH					;PUSH (R4-R3) ONTO STACK
			BRnzp GET_CHAR

GO_TO_MULTIPLY
			JSR POP						;POP AND CHECK IF IT IS VALID
				ADD R5, R5, #0
				BRp UNDER_FLOW_ERROR
				AND R3, R3, #0
				ADD R3, R3, R0			;PUT VAL TO R3
			JSR POP
				ADD R5, R5, #0			;POP SECOND VAL AND CHECK IF VALID
				BRp UNDER_FLOW_ERROR
				AND R4, R4, #0
				ADD R4, R4, R0			;PUT VAL TO R4
			JSR MUL						;CALL MULTIPLY SUB ROUTINE
			JSR PUSH					;PUSH (R4*R3) ONTO STACK
			BRnzp GET_CHAR

GO_TO_DIVIDE
			JSR POP						;POP VAL AND CHECK IF VALID
				ADD R5, R5, #0
				BRp UNDER_FLOW_ERROR
				AND R3, R3, #0
				ADD R3, R3, R0			;PUT VAL TO R3
			JSR POP						;POP SECOND VAL AND CHECK IF VALID
				ADD R5, R5, #0
				BRp UNDER_FLOW_ERROR
				AND R4, R4, #0
				ADD R4, R4, R0			;PUT VAL TO R4
			JSR DIV						;CALL DIVISION SUB ROUTINE
			JSR PUSH					;PUSH (R4/R3) ONTO STACK
			BRnzp GET_CHAR

GO_TO_POWER
			JSR POP						;POP VAL AND CHECK IF VALID
				ADD R5, R5, #0
				BRp UNDER_FLOW_ERROR
				AND R3, R3, #0
				ADD R3, R3, R0			;PUT VAL TO R3
			JSR POP						;POP SECOND VAL AND CHECK IF VALID
				ADD R5, R5, #0
				BRp UNDER_FLOW_ERROR
				AND R4, R4, #0
				ADD R4, R4, R0			;PUT VAL TO R4
			JSR EXP						;CALL EXP SUB ROUTINE
			JSR PUSH					;PUSH (R4^R3) ONTO STACK
			BRnzp GET_CHAR

UNDER_FLOW_ERROR
			LEA R0, INVALID_EXPRESSION	;PRINT INVALD EXPRESSION IF R5 = 1
			PUTS
			HALT


INVALID_EXPRESSION 		.STRINGZ "INVALID EXPRESSION"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	
			ADD R0, R4, R3
			RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
	
			NOT R3, R3
			ADD R3, R3, #1
			ADD R0, R4, R3
			RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here

			AND R0, R0, #0
			ADD R0, R4, R0			;SET R4 TO R0
			ADD R3, R3, #-1			;SUBTRACT R3 BY 1
			BRz DONE_MULT			;DONE IF = 0
MULT_LOOP
			ADD R4, R4, R0			;ADD R4 AND R0
			ADD R3, R3, #-1			;SUBTRACT R3 BY 1
			BRp MULT_LOOP			;LOOP IF POSTIVE
DONE_MULT
			AND R0, R0, #0
			ADD R0, R4, #0			;SET R4 TO R0
			RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	
			AND R0, R0, #0			;R0 COUNTER FOR HOW MNAY TIMES R3 GOES INTO R4
			NOT R3, R3
			ADD R3, R3, #1			;NEGATE R3 (WHAT UR DIVIDING BY)
DIV_LOOP			
			ADD R4, R4, R3			;ADD R4 AND R3
			BRn DONE_DIV			;DONE IF NEGATIVE
			ADD R0, R0, #1			;INCREMENT COUNTER
			ADD R4, R4, #0			;LOOP BACK TO DIV_LOOP
			BRnzp DIV_LOOP			
DONE_DIV
			RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
			
			AND R1, R1, #0
			AND R0, R0, #0
			ADD R0, R4, #0			;SET R4 TO R0, R1, AND R2 
			ADD R1, R4, #0
			AND R2, R2, #0
			ADD R2, R4, #0
OUTER_LOOP	
			ADD R3, R3, #-1			;DECREMENT POWER
			BRz DONE_EXP			;DONE IF 0
			AND R0, R0, #0			;INITIALIZE R0 AND R1 AGAIN
			AND R1, R1, #0
			ADD R0, R2, #0			;SET R2 TO R0 FOR COUNT OF R4
			ADD R1, R4, #0			;SET R4 TO R1 FOR COPY OF R4 THAT UPDATES 
INNER_LOOP	
			ADD R0, R0, #-1			;DECREMENT R0 COUNTER
			BRz OUTER_LOOP			;BRANCH TO OUTER LOOP IF 0
			ADD R4, R4, R1			;ADD R4 AND R1
			BRnzp INNER_LOOP		;BRANCH TO INNER LOOP
DONE_EXP
			AND R0, R0, #0
			ADD R0, R4, #0			;SET R4 TO R0
			RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
