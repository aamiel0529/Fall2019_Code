//partners: rmohta2, weustis2

//intro: In this MP we modeled the game of sudoku. Our task was to implement 5 functions.
//The first function checked if the value appeared in the same row.
//The second function checked if the value appeared in the same column.
//The third function checked if the value appeared in the same 3x3 box.
//A value cannot appear in the same row, column, or 3x3 box more than once.
//The fourth function checked if the value was not in each case, and therefore was a valid value.
//The fifth function solved the sudoku puzzle. The base case of this algorithm was to check if each cell was occupied by a value 1-9. 
//If each cell was occupied by a value 1-9, it would be solved, and therefore terminated. 
//If the base case wasn't reached, it would go through the recursive case. 
//The recursive case first checks if the cell holds is empty (holds a 0). 
//If it does, it would then go through each number 1-9 to check if it was valid.
// It it is valid, it would be placed in the cell. Then recursion would happen to see if the base case is satisfied.
// If it still isn't satisfied, and the value can't be placed in that cell, backtracking will occur and the cell will now be empty. 
//Once the base case is satisifed, the game will terminate and the puzzle will be solved.




#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  for(int j = 0; j < 9; j++) //check each column
    {
      if(val == sudoku[i][j]) //check if the value is in the row
	{
	  return 1; //return true if it is
	}
    }

  
  return 0;
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);
  
  for(int i = 0; i < 9; i++) //check each row
    {
      if(val == sudoku[i][j]) //check if the value is in the column
	{
	  return 1; //return true if it is
	}
    }
  
  return 0;
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
 // BEG TODO
  int x;
  int row, col;
  // x = 1 corresponds to top left box
  // x = 2 corresponds to top middle box
  // x = 3 corresponds to top right box
  // x = 4 corresponds to middle left box
  // x = 5 corresponds to middle middle box
  // x = 6 corresponds to middle right box
  // x = 7 corresponds to bottom left box
  // x = 8 corresponds to bottom middle box
  // x = 9 corresponds to bottom right box

  if ( (i >= 0) && (i <= 2) ) //if in rows 1-3
    {
      if ( (j >= 0) && (j <= 2) ) //if in col 1-3
	{
	  x = 1;
	}
      if ( (j >= 3) && (j <= 5) ) //if in col 4-6
	{
	  x = 2;
	}
      if ( (j >= 6) && (j <= 8) ) //if in col 7-9
	{
	  x = 3;
	}
    }

  if ( (i >= 3) && (i <= 5) ) //if in row 4-6
    {
      if ( (j >= 0) && (j <= 2) ) //if in col 1-3
	{
	  x = 4;
	}
      if ( (j >= 3) && (j <= 5) ) //if in col 4-6
	{
	  x = 5;
	}
      if ( (j >= 6) && (j <= 8) ) //if in col 7-9
	{
	  x = 6;
	}
    }

  if ( (i >= 6) && (i <= 8) ) //if in row 7-9
    {
      if ( (j >= 0) && (j <= 2) ) //if in col 1-3
	{
	  x = 7;
	}
      if ( (j >= 3) && (j <= 5) ) //if in col 4-6
	{
	  x = 8;
	}
      if ( (j >= 6) && (j <= 8) ) //if in col 7-9
	{
	  x = 9;
	}
    }

  if (x == 1) //if in top left box
    {
      for (row = 0; row <=2; row++)
	{
	  for (col = 0; col <=2; col++)
	    {
	      if (val == sudoku[row][col])
		return true;
	    }
	}
    }

  if (x == 2) //if in top middle box
    {
      for (row = 0; row <= 2; row++)
	{
	  for (col = 3; col <= 5; col++)
	    {
	      if (val == sudoku[row][col])
		return true;
	    }
	}
    }

  if (x == 3) //if in top right box
    {
      for (row = 0; row <= 2; row++)
	{
	  for (col = 6; col <= 8; col++)
	    {
	      if (val == sudoku[row][col])
		return true;
	    }
	}
    }

  if (x == 4) //if in middle left box
    {
      for (row = 3; row <= 5; row++)
	{
	  for (col = 0; col <= 2; col++)
	    {
	      if (val == sudoku[row][col])
		return true;
	    }
	}
    }

  if (x == 5) //if in middle middle box
    {
      for (row = 3; row <= 5; row++)
	{
	  for (col = 3; col <= 5; col++)
	    {
	      if (val == sudoku[row][col])
		return true;
	    }
	}
    }

  if (x == 6) //if in midde right box
    {
      for (row = 3; row <= 5; row++)
	{
	  for (col = 6; col <= 8; col++)
	    {
	      if (val == sudoku[row][col])
		return true;
	    }
	}
    }
 
  if (x == 7) //if in bottom left box
    {
      for (row = 6; row <= 8; row++)
	{
	  for (col = 0; col <= 2; col++)
	    {
	      if (val == sudoku[row][col])
		return true;
	    }
	}
    }

  if (x == 8) //if in bottom middle box
    {
      for (row = 6; row <= 8; row++)
	{
	  for (col = 3; col <= 5; col++)
	    {
	      if (val == sudoku[row][col])
		return true;
	    }
	}
    }

  if (x == 9) //if in bottom right box
    {
      for (row = 6; row <= 8; row++)
	{
	  for (col = 6; col <= 8; col++)
	    {
	      if (val == sudoku[row][col])
		return true;
	    }
	}
    }

  return 0;
}
  

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  if(!(is_val_in_row(val, i, sudoku)) && !(is_val_in_col(val, j, sudoku)) && !(is_val_in_3x3_zone(val, i, j, sudoku))) //check if the value is not in either case
    {
      return 1; //return true if each case doesn't have the value we are looking for
    }

  return 0;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  int count = 0;
  int i, j;
  int flag = 0;

  for(i = 0; i < 9; i++)
    {
      for(j = 0; j < 9; j++) //check if each cell is filled with a value between 1 and 9
	{
	  if((sudoku[i][j] == 1) || (sudoku[i][j] == 2) || (sudoku[i][j] == 3) || 
	     (sudoku[i][j] == 4) || (sudoku[i][j] == 5) || (sudoku[i][j] == 6) || 
	     (sudoku[i][j] == 7) || (sudoku[i][j] == 8) || (sudoku[i][j] == 9))
	    {
	      count += 1; //increment count if the cell has a valid value
	    }
	}
    }

  if(count == 81) //base case: if each cell is occupied with a value between 1 and 9
    {
      return true; //return true if it is
    }

  else //recursive case: check for an empty cell
    {
      for(i = 0; i < 9; i++)
	{
	  for(j = 0; j < 9; j++)
	    {
	      if(sudoku[i][j] == 0)
		{
		  flag = 1;
		  break;
		}
	    }
	  if(flag == 1)
	    {
	  break;
	    }
	}
    }
		 
      
  for(int num = 1; num <= 9; num++) //if cell is empty, go through each value to check if it is valid for entry into the cell
    {
      if(is_val_valid(num, i, j, sudoku)) //check if value is valid
	{
	  sudoku[i][j] = num; //fill cell with the number if it is valid
	  if(solve_sudoku(sudoku)) //call recursive case to check if base case is satisfied
	    {
	      return true; //if base case satisfied, return true
	    }
	  sudoku[i][j] = 0; //backtracking if the value couldn't be placed
	}
    }
		  
  return 0;
 
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





