#include "sparsemat.h"
	#include <stdio.h>
	#include <stdlib.h>
	
//partners: rmohta2, weustis2
	/* 
	
	In this MP we create a sparse array as well as some functions to do math across them. We implemented functions that:
	load the sparse array in from a formatted, but not nessecarily ordered, txt file
	return the value of a node at a given point
	set the value of a node (existing or not) to a different value (0 or non-zero)
	save the sparse matrix into a txt file similarly to how it was loaded in
	add two matrices together
	multiply two matrices together
	destroy the matrices from memory without leaks
	
	
	Overall this was a very challenging MP as it took a lot of unique solutions to solve the problems. There were many different edge cases that needed to be accounted for which forced for very general and robust solutions. I believe that while my solutions could be better, that they are good.
	*/
	
	
sp_tuples * load_tuples(char* input_file)
{
  sp_tuples *mat_t = (sp_tuples *)malloc(sizeof(sp_tuples));
  FILE *f = fopen(input_file, "r");
  int r, c, count=0;
  double v;
  fscanf(f, "%d ", &mat_t->m); // get m
  fscanf(f, "%d ", &mat_t->n); // get n;
  while(!feof(f)){ // for each line in the file
    fscanf(f, " %d %d %lf", &r, &c, &v); // get the node's info
    count++;
    sp_tuples_node *new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    new_node->row = r; // create and allocate the node
    new_node->col = c;
    new_node->value = v;
    new_node->next = NULL;
    if(count == 1){ // if it's the first, set tuples_head
      mat_t->tuples_head = new_node;
    }// if it isn't the first, we need to add it to the right spot
    else{
      sp_tuples_node *tmp;
      tmp = mat_t->tuples_head;
      if(tmp->row>r){ // if the first item should be replaced
	mat_t->tuples_head = new_node;
	new_node->next = tmp;
      }
      else if(tmp->row==r && tmp->col>c){ // if the first item should be replaced 2nd case
	mat_t->tuples_head = new_node;
	new_node->next = tmp;
      }
      else{ // otherwise search
	while(tmp->next != NULL && tmp->next->row<r){
	  // traverse list until we find the end or the next item has a greater row
	  tmp = tmp->next;
	}
	if(tmp->next == NULL){ // if it was the last item, add it
	  tmp->next = new_node;
	}
	else
	  { // if the next item has a greater row (or equal)
	    while(tmp->next != NULL && tmp->next->col<c){ // find either the end of the list or the next greatest item
	      if(tmp->next->row==r){
		tmp = tmp->next;
	      }
	      else{ // if we go too far, exit
		break;
	      }
	    }
	    if(tmp->next == NULL){ // if at the end, add it
	      tmp->next = new_node;
	    }
	    else{ // otherwise insert it
	      if(!(r==tmp->next->row && c==tmp->next->col)){
		new_node->next = tmp->next; // reassign pointers
		tmp->next = new_node;
	      }
	      else{
		count--; // if it exists, just replace the value.
		tmp->next->value = v;
		free(new_node);
	      }
	    }
	  }
      }
    }
  }
  sp_tuples_node *tmp = mat_t->tuples_head; // remove the first n items if it has a value of 0
  while(tmp->value == 0){
    mat_t->tuples_head = mat_t->tuples_head->next;
    free(tmp);
    tmp = mat_t->tuples_head;
    count--;
  } // check all other items if they have a value of 0
  while(tmp->next != NULL){
    if(tmp->next->value == 0){
      sp_tuples_node *tmp2;
      tmp2 = tmp->next;
      tmp->next = tmp->next->next;
      free(tmp2);
      count--;
    }
    else{
      tmp = tmp->next;
    }
  }
  fclose(f);
  mat_t->nz=count;
  return mat_t;
}
	
	
	
double gv_tuples(sp_tuples * mat_t,int row,int col)
	
{ // we go until we find the row and column that we want (or the end)
  sp_tuples_node *curr = mat_t->tuples_head;
  while(curr != NULL && curr->row<=row){
    if(curr->row == row && curr->col == col){
      return curr->value;
    }
    curr = curr->next;
  }
  return 0;
}
	
	
void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
	
  sp_tuples_node *curr = mat_t->tuples_head;
  while(curr->next != NULL && curr->next->row<row){ // first we find the row we want. We stop either at the end of the list
    // or right before the row begins
    curr=curr->next;
  }
  if(curr->next == NULL && value != 0){ // We want to add to the end of the list if the value isnt 0
    sp_tuples_node *new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); // allocate memory
    new_node->row = row; // set row, col, value
    new_node->col = col;
    new_node->next = NULL;
    new_node->value = value;
    curr->next = new_node; // curr->next was NULL, so now it can be new_node
    mat_t->nz = mat_t->nz + 1; // increment nz
    return;
  }
  while(curr->next != NULL && curr->next->col<col){ // now we want the right column
    if(curr->next->row==row){ // but we don't want to leave the row
      curr = curr->next;
    }
    else{
      break;
    }
  }
  // here curr is either: pointing at the node before row, col should be or pointing at the end of the list
  if(curr->next == NULL && value != 0){
    sp_tuples_node *new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); // allocate memory
    new_node->row = row; // set row, col, value
    new_node->col = col;
    new_node->value = value;
    new_node->next = NULL;
    curr->next = new_node; // curr->next was NULL, so now it can be new_node
    mat_t->nz = mat_t->nz + 1; // increment nz
    return; // if the node doesn't exist, we will create it
  }
  // at this point, we are pointing at the node before the place we want to edit/create
  // let's check if the next node is row, col
  if(row==curr->next->row && col==curr->next->col){ // yes? do we need to edit or delete
    if(value == 0){
      sp_tuples_node *tmp = curr->next;
      curr->next = curr->next->next;
      free(tmp);
      mat_t->nz = mat_t->nz - 1;
    }
    else{
      curr->next->value = value;
    }
  }
  else{ // no? if val is 0, do nothing. if val is not 0, create node
    if(value == 0){
      return;
    }
    else{
      sp_tuples_node *tmp = curr->next;
      sp_tuples_node *new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); // allocate memory
      new_node->row = row; // set row, col, value
      new_node->col = col;
      new_node->value = value;
      new_node->next = NULL;
      tmp = curr->next;
      curr->next = new_node; // curr->next is not NULL, so we need to get tmp
      new_node->next = tmp;
      mat_t->nz = mat_t->nz + 1; // increment nz
      return;
    }
  }
}
	
	
	
void save_tuples(char * file_name, sp_tuples * mat_t)
{
  FILE *f =fopen(file_name, "w+");
  fprintf(f, "%d %d\n", mat_t->m, mat_t->n); // save the metadata
  sp_tuples_node *curr = mat_t->tuples_head;
  while(curr!=NULL){
    fprintf(f, "%d %d %lf\n", curr->row, curr->col, curr->value); // for each node, save it
    curr = curr->next;
  }
  fclose(f); // close the file and return
  return;
}
	
	
	
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
  if(matA->m != matB->m || matA->n != matB->n){ // if it isn't valid, return null
    return NULL;
  }
  sp_tuples *retmat = (sp_tuples *)malloc(sizeof(sp_tuples)); // initalize the new graph as well as a new node to begin pointing off of, this is later removed if not overwritten
  retmat->m = matA->m;
  retmat->n = matA->n;
  sp_tuples_node *new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
  new_node->row = 0;
  new_node->col = 0;
  new_node->value = 0;
  new_node->next = NULL;
  retmat->tuples_head = new_node;
  retmat->nz = 0;
  sp_tuples_node *curr = matA->tuples_head;
  while(curr != NULL){ // for each item, get the current value in our graph and set the new value to the addition of it and graphA
    // technically, this should always be 0, but it doesn't hurt to be robust :) (except for ineffiency but oh well)
    float currentVal = gv_tuples(retmat,curr->row,curr->col);
    set_tuples(retmat, curr->row, curr->col, curr->value + currentVal);
    curr=curr->next;
  }
  curr = matB->tuples_head; // set curr to the beginning of matB
  while(curr != NULL){
    float currentVal = gv_tuples(retmat,curr->row,curr->col); // repeat the process, now the values aren't always 0 so we
    // definitely need to add the current and new values
    set_tuples(retmat, curr->row, curr->col, curr->value + currentVal);
    curr=curr->next;
  }
  if(retmat->tuples_head->value == 0){ // remove the dummy node
    sp_tuples_node *willy = retmat->tuples_head;
    retmat->tuples_head = retmat->tuples_head->next;
    free(willy); // :)
  }
  curr = retmat->tuples_head; // count the nodes
  int count = 0;
  while(curr != NULL){
    count++;
    curr=curr->next;
  }
  retmat->nz = count; // set the count
  return retmat;
}
	
	
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB)
{
	
  // if invalid, return null
  if(matA->n != matB->m){
    return NULL;
  }
  sp_tuples *retmat = (sp_tuples *)malloc(sizeof(sp_tuples)); // similarly to addition, we initialize retmat and set a dummy head node
  retmat->m = matA->m;
  retmat->n = matB->n;
  retmat->nz = 0;
  sp_tuples_node *new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
  new_node->row = 0;
  new_node->col = 0;
  new_node->value = 0;
  new_node->next = NULL;
  retmat->tuples_head = new_node;
  sp_tuples_node *curr = matA->tuples_head; // for each NZ in A
  while(curr != NULL){
    int iA, jA, jB;
    iA = curr->row;
    jA = curr->col; // set iA and jA
    sp_tuples_node *currb = matB->tuples_head; // for each NZ in B
    while(currb != NULL && currb->row<=jA){
      if(currb->row == jA){ // if it's a valid position
	jB = currb->col;
	float currentVal = gv_tuples(retmat,iA,jB); // get the current value
	
	set_tuples(retmat, iA, jB, currentVal + curr->value * currb->value);  // set the new value = current value + the product of curr and currb
      }
      currb = currb->next;
    }
    curr = curr->next;
  }
	
  // clear the dummy node if it exists still
  if(retmat->tuples_head->value == 0){
    sp_tuples_node *willy = retmat->tuples_head;
    retmat->tuples_head = retmat->tuples_head->next;
    free(willy); // :)
  }
  curr = retmat->tuples_head; // count the nodes
  int count = 0;
  while(curr != NULL){
    count++;
    curr=curr->next;
  }
  retmat->nz = count; // set the count and return the new graph
  return retmat;
}
	
	
	
void destroy_tuples(sp_tuples * mat_t){
  sp_tuples_node *tmp = mat_t->tuples_head; // for each NZ in A
  while(tmp != NULL){
    mat_t->tuples_head = tmp->next; // first free all of the tuple nodes
    free(tmp);
    tmp = mat_t->tuples_head;
  }
  free(tmp); // then free tmp, it should be NULL but just in case
  free(mat_t); // then free the struct itself and return
  return;
}


