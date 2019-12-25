#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

//partners: rmohta2, weustis2

/*Intro: In this mp we created 4 functions to represent a maze.
The first function createMaze() does many things. 
First, it allocates memory for the maze and each cell within the maze.
It then reads the file to determine the maze's width, height, start and end index. 
It also reads each ascii value in the file and assigns it to the corresponding
cell to create the maze.
The second function destroyMaze() frees all memory associated with the maze struct.
It also frees the memory space for each cell within the maze.
The third function, printMaze(), iterates through each cell in the maze,
and prints out the ascii value of each cell to the monitor so it is easy for
people to read it.
The last function, solveMazeDFS(), does a few things. 
First it checks if the row and col are within the bounds of the maze. 
Next, it checks if it is an empty cell. Then it recursively calls itself to check
if any of the four cells around the cell that is being checked is valid to move to.
'*' indicates a cell is part of the solution path, '~' indicates the cell was 
visited, but it isn't part of the solution's path. 
 
That's all. Thank you!!
*/




/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
  int i, j, height, width;
  char charac; //charac holds next char in the file
  FILE *file = fopen(fileName, "r"); //open file for reading

  fscanf(file, "%d %d", &height, &width); //read the numbers for #heights and #rows

  maze_t *maze = (maze_t *)malloc(sizeof(maze_t)); //allocate memory for maze

  maze->cells = (char **)malloc(sizeof(char *) * height); //allocate memory for the rows in cells array
  for(i = 0; i < height; i++)
    {
     maze->cells[i] = (char *)malloc(sizeof(char) * width); //allocate memory for each column in cells
    }

  //this nested for loop reads the char and assigns it to the cell
  for(i = 0; i < height; i++) 
    {
      for(j = 0; j < width; j++)
	{
	  charac = fgetc(file);
	  if(charac == '\n') //dont want to assign new line to a cell
	    {
	      charac = getc(file);
	    }
	  maze->cells[i][j] = charac; //assign char into maze
	}
    }

  maze->width = width; //assign width for maze
  maze->height = height; //assign height for maze

  //nested for loop checks if the cell is start or end or the maze
  for(i = 0; i < height; i++) 
    {
      for(j = 0; j < width; j++)
	{
	  if(maze->cells[i][j] == START) //check to see if cell is Start cell
	    {
	      maze->startRow = i; //initialize start row and column
	      maze->startColumn = j;
	    }
	  if(maze->cells[i][j] == END) //check to see if cell is End cell
	    {
	      maze->endRow = i; //initialize end row and column
	      maze->endColumn = j;
	    }
	}
    }

  fclose(file); //close file
  return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
  int i;

  for(i = 0; i < maze->height; i++)
    {
      free(maze->cells[i]); //free each cell
    }
  free(maze->cells); //free memory space that was allocated for the cells
  free(maze); //free memory space allocated for the maze itself
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{

  int i, j;

  for(i = 0; i < maze->height; i++)
    {
      for(j = 0; j < maze->width; j++)
	{
	  printf("%c", maze->cells[i][j]); //print each cells ASCII char to screen
	}
      printf("\n");
    }
}
		 

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
  //checks for row and column parameters are within range of the maze
  if(row < 0 || row >= maze->height || col < 0 || col >= maze->width)
    {
      return 0;
    }

  //checks if the cell is not a space, 'S', or 'E'
  //returns 0 if it isn't empty
  if(maze->cells[row][col] != EMPTY && maze->cells[row][col] != START && maze->cells[row][col] != END) 
    {
      return 0;
    }

  //check if cell is at the end
  //assigns start location to 'S' since it was made a '*' previously
  if(maze->cells[row][col] == END)
    {
      maze->cells[maze->startRow][maze->startColumn] = START;
      return 1;
    }

  //mark location as '*' to indicate it 
  //is part of the path's solution
  maze->cells[row][col] = PATH;

  //recursively call to check the 4 cells around the current one
  //if a 1 is returned then it is a valid cell to go to
  if(solveMazeDFS(maze, col-1, row) == 1)
    {
      return 1;
    }
  if(solveMazeDFS(maze, col+1, row) == 1)
    {
      return 1;
    }
 if(solveMazeDFS(maze, col, row-1) == 1)
    {
      return 1;
    }
 if(solveMazeDFS(maze, col, row+1) == 1)
    {
      return 1;
    }

 //if this is reached, the cell must have been visited ('~')
 //but not part of the path for the solution
 //0 is returned
 maze->cells[row][col] = VISITED;
 return 0;
}

