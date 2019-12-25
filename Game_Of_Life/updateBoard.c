// Partners: rmohta2, aamiel2

// Introduction:
 
// In this MP, we are implementing the Game of Life in C programming
// through 3 primary functions and pointers and arrays.
// One of the functions is the countLiveNeighbor function. Given a cell in the board
// and its current row and column position, we will check all the adjacent cells to see
// which ones are alive (1) and which ones are dead (0). The number of adjacent live cells
// is returned. Another function is the updateBoard function. For each step, if a cell is alive
// and has fewer than 2 or more than 3 alive neighbors, the cell dies. Otherwise, it lives on.
// If a cell is dead and it has exactly 3 alive neighbors, the cell becomes alive. The third function
// is the aliveStable function. It checks if the game board is going to change for the next step and
// returns 1 if the board stays the same and returns 0 if it doesn't. The board is thought of as a 2-D
// array, but in this lab, it is represented as a 1-D array. All the elements in the first row are the first
// elements in the 1-D array, all the elements in the second row are the next elements in the 1-D array,
// and so on.


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

  int live_neighbors = 0; //#of live neighbors
  int i,j;
  for(i = row-1; i <= row+1; i++) //for rows directly above, below, and current row of cell
    {
      if((i >= 0) && (i < boardRowSize)) //check if row is in bounds of the board
	{
	  for(j = col-1; j<= col+1; j++) //for cols directly left, right, and current cols of cell
	    {
	      if((j >= 0) && (j<boardColSize)) //check if col is in bounds of the board
		{
		  if((i*boardColSize + j) != (row*boardColSize + col)) //if the cell we are checking isn't the current cell 
		    {
		      if(board[i*boardColSize + j] == 1) //check if cell we are checking is alive
			{
			  live_neighbors += 1; //increment count if it is alive
			}
		    }
		}
	    }
	}
    }	
  return live_neighbors;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {


  int i, j;
  int number_live_neighbors[boardRowSize*boardColSize];

  for(i = 0; i < boardRowSize; i++)
    {
      for(j = 0; j < boardColSize; j++)
	{
	  number_live_neighbors[i*boardColSize + j] = countLiveNeighbor(board, boardRowSize, boardColSize, i, j); //array holds # live neighbors for the array of cells respectively
	}
    }

  for(i = 0; i < boardRowSize; i++)
    {
      for(j = 0; j < boardColSize; j++)
	{
	  if(board[i*boardColSize + j] == 1) //check to see if the cell is alive
	    {
	      if(number_live_neighbors[i*boardColSize + j] < 2 || number_live_neighbors[i*boardColSize + j] > 3) //check to see if the number of live neighbors is <2 or >3
		{
		  board[i*boardColSize + j] = 0; //if it is true, update cell to dead (0)
		}
	    }

	  else if(board[i*boardColSize + j] == 0) //if the cell isn't alive, goes to this statement (it is dead)
	    {
	      if(number_live_neighbors[i*boardColSize + j] == 3) //check to see if the number of alive cells for the particular cell is 3
		{
		  board[i*boardColSize + j] = 1; //if it is true, update cell to alive (1)
		}
	    }
	}
    }			
	      

}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){

  int i;
  int new_board[boardRowSize*boardColSize]; //make a new board with same dimensions as current board
  int old_board[boardRowSize*boardColSize]; //make an old board with same dimensions as current board

  for(i = 0; i < boardRowSize*boardColSize; i++)
    {
      new_board[i] = board[i]; //set each element in new board to current board
      old_board[i] = board[i]; //set each element in old board to current board
    }

  updateBoard(new_board, boardRowSize, boardColSize); //call update board to update the new_board

  for(i = 0; i < boardRowSize*boardColSize; i++) // go through each element in the array
    {
      if(old_board[i] != new_board[i]) //check to see if the old board is not equal to the new board (the alive cells change)
	{
	  return 0; //return 0 if it does
	}
    }
  return 1; //otherwise return 1
}

				
				
			

