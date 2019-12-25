/* Partners: weustis2, rmohta2 */

/* Intro Paragraph:
                In this MP we were instructed to create three methods to recreate a version of the game mastermine.
		In set_seed, we implemented the sscanf() function to read an integer, inputed by the user, from seed_str[] to use in srand().
If the inputed integer was more than 1 integer or characters, it would be invalid.
		In start_game I initialized the solutions by using the rand() function, modulus the value by 8 and add 1 to get a random number in the range 1-8. 
I also set the guess_number to 0 for intialization purposes.
		In make_guess, I set up an array to hold the solutions, an array to check if there was a perfect match, and an array to hold each guess.
The sscanf function was implemented again to see if there were 4 integers typed in by the user. 
The 4 integers are then set to each guess variable (w,x,y,z) respectively.
Pointers were then used to point to each value. 
I then compared each guess to its corresponding solution. 
If they were equal, I would set the corresponding index in the perfect_matches array to 1 and incremented the variable perfect. 
After each guess was checked for a perfect match, I then used a nested for loop to check if the guess was misplaced, meaning the guess matches a solution, but it isn't in the right place. 
After this nested for loop, the computer will print the current guess the user is on, how many perfect matches there are, and how many misplaced matches there are. After this, the user is prompted to enter another guess until it is all correct or until there have been 12 guesses, and the program eventually terminates if either of these were met. */
		



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;

int set_seed (const char seed_str[])
{

  int seed;
  int check;
  char post[2];

  check = sscanf(seed_str, "%d%1s", &seed, post); /*read in integer and "garbage" typed by user */

  if (check == 1) /* check if only an integer was typed in */
    {
    srand(seed); /* set srand() to seed value if integer was typed in */
    return 1;
    }
  else
    {
      printf("set_seed: invalid seed\n"); /* print error message if input isn't valid */
      return 0;
    }
}

   
void start_game (int* one, int* two, int* three, int* four)
{
  solution1 = *one = rand() % 8 + 1; /* set each solution to a random number 1-8 */
  solution2 = *two = rand() % 8 + 1; /* use %8 to get a number 0-7 and add 1 to get numbers 1-8 */
  solution3 = *three = rand() % 8 + 1;
  solution4 = *four = rand() % 8 + 1;

  guess_number = 0;
}


int make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{

  int w, x, y, z;
  char post[2];
  int check;
  int perfect = 0;
  int misplaced = 0;
  
  int perfect_matches[4] = {0,0,0,0};     /* array used later, stores 1 if the guess matches the solution */
  int all_solutions[4] = {solution1, solution2, solution3, solution4}; /* array used to store solutions */

  check = sscanf(guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
 
  *one = w;
  *two = x;
  *three = y;
  *four = z;

  int all_guesses[4] = {w,x,y,z}; /* array to keep track of guesses, used later to find misplaced guess */

  if(check == 4                   /* check to see if 4 integers were entered */
     && *one >= 1 && *one <=8
     && *two >= 1 && *two <= 8
     && *three >= 1 && *three <= 8
     && *four >= 1 && *four <= 8)
    {
      guess_number++;             /* increment guess if 4 integers entered */
    }
  else                            /* invalid guess if anything other than 4 integers were entered */
    {
      printf("make_guess: invalid guess\n");
      return 0;
    }


  if(*one == solution1)           /* check for perfect matches and increment perfect if they are equal */
    {
      perfect_matches[0] = 1;     /*update perfect_matches array to 1 if match */
      perfect++;
    }
  if(*two == solution2)
    {
      perfect_matches[1] = 1;
      perfect++;
    }
  if(*three == solution3)
    {
      perfect_matches[2] = 1;
      perfect++;
    }
  if(*four == solution4)
    {
      perfect_matches[3] = 1;
      perfect++;
    }
  
  int i;
  int j;
  for(i = 0; i < 4; i++)           /* loop used to go through each guess stored in array all_guesses */
    {
      if(perfect_matches[i] != 1)  /* if there isn't a perfect match, check to see if it is misplaced */
	{
	  for(j = 0; j < 4; j++)   /* loop through each solution stored in all_solutions */
	    {
	      if(all_guesses[i] == all_solutions[j]) /* if a guess is equal to a different solution */
		{
		  if(perfect_matches[j] != 1)       /* check to see if that solution was already guessed perfectly */
		    {
		      misplaced++; /* if the guess is equal to the solution that isn't already perfect, increment misplaced */
		      break;       /* break to avoid duplication */
		    }
		}
	    }
	}
    }
		
 
	
	  
  printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);
  return 1;
}


