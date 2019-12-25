#include <stdio.h>
#include <stdlib.h>

//partners: weustis2, rmohta2
	
	/*
	   In this mp, the user will enter a row index of the Pascal Triangle,
	   and the program will print the row that the user entered.
	   To do this, a for loop was nested inside another for loop. The outer
	   loop kept track of the position in the row. The inner loop kept track
	   how many times [(row + 1 - i) / i] had to be multiplied to itself (with
	   'i' being incremented each time). This depended on the position in the row,
	   and in the end, the result will be the coefficient of that position.
	   Position '0' in the row is always '1', but the expression we used does not
	   work when the row position is '0'. That is why the expression started from
	   position '1'. To print position '0', there is a print statement to print '1 '
	   before the rest of the row is printed.
	
	 */


int main()
{
  int k, row;
  long double i, a, b;
  unsigned long coefficient;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here
  
  printf("1 ");

  for(k = 1; k <= row; k++)
    {
      b = 1;

      for(i = 1; i <= k; i++)
	{
	  a = (row + 1 - i) / (i);
	  b = a * b;
	}

      coefficient = (unsigned long)b;
      printf("%lu ", coefficient);

    }

  printf("\n");
  


  return 0;
}
