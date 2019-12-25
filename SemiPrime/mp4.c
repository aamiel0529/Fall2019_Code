// Partners: weustis2, rmohta2
	
	// Introduction:
	// In this MP, we are printing all the semi-prime numbers in a given range entered
	// by the user. A semi-prime number is a number that can be written as a product of
	// two prime numbers. First, the user is told to enter two integers. The program
	// will not continue if any integer is negative, and it will not continue if the
	// first number entered is greater than the second number entered.
	// If the user enters the numbers correctly, then the
	// 'print_semiprimes' function is called. The 'print_semiprimes' function has
	// a for loop in a for loop. The outer loop runs for every integer 'n' in [a, b].
	// The inner loop runs for every integer 'k' in [2, n-1]. 'n' is a semiprime
	// number if 'k' is a prime factor of 'n' and 'n/k' is a prime number. The factors
	// of n are 'k' and 'n/k'. Duplicates initially formed as k went through the loop.
	// For example, 35 has prime factors 5 and 7, so at first, 35 would be printed
	// twice - once when k = 5 and again when k = 7. To avoid duplication, I added
	// a break to the inner for loop as soon as we figured out that n is a semi-prime
	// number. 
	
	
	#include <stdlib.h>
	#include <stdio.h>
	
	// function prototypes
	int is_prime(int number);
	int print_semiprimes(int a, int b);
	
	
	int main(){   
	   int a, b;
	   printf("Input two numbers: ");
	   scanf("%d %d", &a, &b);
	   if( a <= 0 || b <= 0 ){
	     printf("Inputs should be positive integers\n");
	     return 1;
	   }
	
	   if( a > b ){
	     printf("The first number should be smaller than or equal to the second number\n");
	     return 1;
	   }
	
	   // Call 'print_semiprimes' function
	   print_semiprimes(a, b);
	}
	
	int is_prime(int number)
	{
	  // Return 1 if 'number' is prime, else return 0
	  int i;
	  for (i = 2; i <= number / 2; i++)
	    {
	      if (number % i == 0)
		return 0;
	    }
	  return 1;
	}
	
	int print_semiprimes(int a, int b)
	{
	  // 'n' is a semi-prime number if k is a prime factor of n and n/k is prime number
	  int n, k;
	  int count = 0; // counts how many integers in the range are semi-prime numbers
	  for (n = a; n <= b; n++) {
	    for (k = 2; k <= n - 1; k++) {
	      if ( ((is_prime(k)) && (n%k == 0)) && (is_prime(n/k)) ) {
		count = count + 1;
		printf("%d ", n);
		break; // Break from inner loop after we confirmed 'n' is semi-prime number. This avoids duplication.
	      }
	    }
	  }
	
	  printf("\n");
	
	  // If there are semi-prime numbers in [a, b], return 1. Else, return 0.
	  if (count != 0)
	    return 1;
	  else
	    return 0;
	}
