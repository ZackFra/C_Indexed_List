#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

void print_aux(Node *cursor);
void clear_aux(Node *cursor);
void decrement_indices(Node *cursor);

void test0();
void test1();
void test2();
void test3();
void test4();


// creates an empty list
BOOL create_list(List **list) {
  (*list) = malloc(sizeof(List));
  (*list)->head = NULL;
  (*list)->size = 0;
}
  
// adds a node to the end of the list
BOOL add_node(int value, List *list) {
  Node *cursor, *head, *new_node;

  // if the list is NULL, return FALSE
  // if a node with that value already exists,
  // return FALSE
  if(!list || find_node(list, value)) {
    return FALSE;
  }

  head = list->head;

  // instantiate the new node
  new_node = malloc(sizeof(Node));
  new_node->value = value;
  
  // if this is an empty list
  if(!head) {
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->index = 0;
    
    list->head = new_node;
  }
  // if the list is not empty
  else {
    cursor = list->head;


    // if we're looking at a single-node list
    // set the new_node to be the second node
    if(list->size == 1) {
      head->next = new_node;
      new_node->prev = head;
      new_node->next = NULL;
    }
    else {
      // if we're not looking at a single-node list
      // iterate the list and add the new node to the end
      while(cursor->next) {
	cursor = cursor->next;
      }

      cursor->next = new_node;
      new_node->prev = cursor;
      new_node->next = NULL;
    }
  }
  list->size++;
  new_node->index = list->size;
  return TRUE;
}

// function to destroy a list
void destroy_list(List **list) {
  // destroy every node in the list
  // free the list, then set the
  // list to NULL (no dangling pointer)
  clear_list(*list);
  free(*list);
  
  *list = NULL;
}

// function to free all the nodes of a list
void clear_list(List *list) {
  // first check that the list exists,
  // and that it is not already empty
  if(!list || !list->head) {
    return;
  }

  // clear every node, including the head
  // then set the head to NULL
  clear_aux(list->head);
  list->head = NULL;
  list->size = 0;

}

// auxillary function for clear_list
void clear_aux(Node *cursor) {
  // if there is a next node, clear that too
  if(cursor->next) {
    clear_aux(cursor->next);
  }

  free(cursor);
}

// attempts to find the node with the value specified
// if none exists, returns NULL
Node *find_node(List *list, int value) {
  if(!list || !list->head) {
    return NULL;
  }
  
  Node *cursor = list->head;
  
  while(cursor->value != value) {
    cursor = cursor->next;
    if(!cursor) break;
  }

  return cursor;
}

void remove_node(List *list, int value) {
  // if list is NULL, or list is empty,
  // return NULL
  if(!list || !list->head) {
    return;
  }

  Node *cursor = list->head;

  // iterate through the list until the
  // node is found. If we hit the
  // end of the list, just return
  while(cursor->value != value) {
    cursor = cursor->next;
    if(!cursor) return;
  }

  // decrement the indices now, before
  // we remove the node. convenient.
  decrement_indices(cursor->next);

  // if we're at the head of the list
  // set the head to next, if this
  // isn't a one-node list, set
  // the previous value to NULL
  if(cursor == list->head) {
    list->head = list->head->next;

    if(list->head) {
      list->head->prev = NULL;
    }
    
    free(cursor);
  }
  else if (!cursor->next){
    // if we're at the tail
    // set the second to last node
    // to have its next node be NULL
    cursor->prev->next = NULL;
    free(cursor);
  }
  // this handles any node between the head
  // and tail. Just reassign their next and
  // prev values, then free the cursor
  else {
    cursor->next->prev = cursor->prev;
    cursor->prev->next = cursor->next;
    free(cursor);
  }
  list->size--;
}

// function to decrement every cursor's index
// after a specified cursor
void decrement_indices(Node *cursor) {
  if(cursor) {
    cursor->index--;
    decrement_indices(cursor->next);
  }
}
  

// function to print the contents of a list
void print_list(List *list) {
  Node *cursor = list->head;
  print_aux(cursor);

  return;
}

// recursive function to assist printing the list
void print_aux(Node *cursor) {
  if(cursor) {
    printf("%d Value: %d\n", cursor->index, cursor->value);
    print_aux(cursor->next);
  }

  return;
}

void test0() {
  List *list;

  create_list(&list);

  add_node(1, list);
  add_node(2, list);
  add_node(3, list);

  print_list(list);
  destroy_list(&list);
}

void test1() {
  List *list;
  
  create_list(&list);
  for(int i = 0; i < 100; i++) {
    add_node(i + 1, list);
  }

  print_list(list);
  destroy_list(&list);
}

void test2() {
  List *list;

  create_list(&list);
  for(int i = 0; i < 100; i++) {
    add_node(i + 1, list);
  }

  remove_node(list, 1);
  print_list(list);
  remove_node(list, 100);
  print_list(list);

  destroy_list(&list);
}

void test3() {
  List *list;

  create_list(&list);

  for(int i = 0; i < 10; i++) {
    add_node(i + 1, list);
  }
  clear_list(list);

  print_list(list);

  for(int i = 0; i < 10; i++) {
    add_node(20 + i, list);
  }

  print_list(list);

  
  destroy_list(&list);
}

void test4() {
  List *list;
  int val = 10;

  create_list(&list);

  for(int i = 0; i < 10; i++) {
    add_node(i + 1, list);
  }

  Node *find_me = find_node(list, val);

  printf("Index of find_me = %d (should be %d)\n", find_me->index, val);

  destroy_list(&list);
}
