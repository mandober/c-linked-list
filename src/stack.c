/*

  LINKED LIST
  Stack implemented with a linked list.

*/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>

// ====================================================== PROTOTYPES
#define usize size_t
#define i32 int32_t
#define NONE INT32_MAX

// forward declarations
struct node_s;
struct list_s;

// aliases: bring identifiers from tag into ordinary namespace
typedef struct node_s Node;
typedef struct list_s List;

// function prototypes (param names may be omitted)
Node* node_new(Node* next, i32 item);
Node* node_drop(Node* node);
List  list_new();
i32   list_pop(List* list);
usize list_len(List* list);
List* list_drop(List* list);
List* list_push(List* list, i32 item);
List* list_print(List* list);


// ====================================================== DECLARATIONS
/*
  Node is an element of the list that carries a payload.
  Nodes are stored on the heap.
*/
struct node_s {
  Node *next; // 8
  i32   item; // 4
  i32   hits; // 4
};

/*
  List itself is stored on the stack.
  It points to the first node and
  manages nodes and quasi methods.
*/
struct list_s {
  Node *head;
  usize length;
  // quasi methods
  usize (*len)(List*);
  List *(*push)(List*, i32);
  List *(*drop)(List*);
  List *(*print)(List*);
  i32   (*pop)(List*);
};


// ===================================================== NODE NEW
/**
 * Creates a new node with supplied item.
 *
 * @param   Node*  next  Takes a reference to (the next) node.
 * @param   i32    item  Takes a payload by value.
 * @return  Node*  Reference to new node or NULL on error.
**/
Node* node_new(Node* next, i32 item) {
  Node* np = malloc(sizeof *np);
  if(np != NULL) {
    np->next = next;
    np->item = item;
    np->hits = 0;
  }
  // ref to node or NULL if allocation failed
  return np;
}

// ===================================================== LIST NEW
/**
 * Creates a new empty list on the stack.
 *
 * @return  List  Returns the new list by value.
**/
List list_new() {
  // Initialize new list
  List list = {
    .head   = NULL,
    .length = 0,
    .len    = list_len,
    .push   = list_push,
    .pop    = list_pop,
    .print  = list_print,
    .drop   = list_drop
  };
  return list;
}

// ===================================================== NODE DROP
/**
 * Deallocates a node.
 *
 * @param   Node*  node  Takes a node by reference.
 * @return  Node*  Returns a reference to the next node in sequence.
**/
Node* node_drop(Node* node) {
  // temp node ptr
  Node* np = NULL;

  // check supplied node ref
  if(node != NULL) {
    // save its `next` value
    np = node->next;
    // drop it
    free(node);
  }
  // return a ref to next node. Or NULL on failure? (TODO) what if
  // that was the last node? NULL gets returned in either case...
  return np;
}

// ===================================================== LIST DROP
/**
 * Iteratively deallocates all nodes in the list.
 * Empties the list.
 *
 * @param   List*  list  Takes list reference.
 * @return  List*  Returns list reference.
**/
List* list_drop(List* list) {
  // take each node starting with head and call node_drop,
  // which drops the current and returns a ref to the next.
  Node *np = list->head;

  while(np != NULL) {
    np = node_drop(np);
  }

  list->head = NULL;

  return list;
}

// ===================================================== LIST POP
/*
 * Removes the head node and returns its payload.
 *
 * @param   List*  list  Takes list reference.
 * @return  i32    Payload by value or NONE if list empty.
*/
i32 list_pop(List* list) {
  if (list->head != NULL) {
    // at least 1 node
    i32 rv = list->head->item;
    list->head = node_drop(list->head);
    list->length--;
    return rv;
  }
  // in-band signaling: no payload to return
  return NONE;
}

// ===================================================== LIST PUSH
/*
 * Insert new node at the front of the list.
 *
 * @param   List*  list  Takes a list by reference.
 * @param   i32    item  Takes a payload by value.
 * @return  List*  Returns the list by reference.
*/
List* list_push(List* list, i32 item) {
  // alloc new node, set current head as its next, may be NULL
  Node* new_node = node_new(list->head, item);

  // check alloc of new node
  assert(new_node != NULL);

  // set new node as new head
  list->head = new_node;

  // set new length
  list->length++;

  return list;
}

// ===================================================== LIST LEN
/*
 * Get list's length.
 *
 * @param   List*  list  Takes list by reference.
 * @return  usize  Number of nodes in the list.
*/
usize list_len(List* list) {
  return list->length;
}

// ===================================================== LIST PRINT
/*
 * Display list.
 *
 * @param   List*  list  Takes list reference.
 * @return  List   Returns list reference.
*/
List* list_print(List* list) {
  Node *np = list->head;
  i32 i = 1;

  printf("List: ");
  while(np != NULL) {
    printf("[%d: %d] -> ", i++, np->item);
    np = np->next;
  }
  printf("NULL\n\n");

  return list;
}




// ===================================================== MAIN
int main() {
  // new: list, list ref
  List list = list_new(), *self = &list;
  assert(list.len(self) == 0);

  // push quasi method
  list.push(self, 99);
  assert(list.len(self) == 1);

  // quasi method chaining
  list.push(self, 88)->push(self, 77)->push(self, 66)->print(self);

  // len quasi method
  printf("List length: %zu\n", list.len(self));

  // print quasi method
  list.print(self);

  // pop quasi method
  i32 x;
  while ( (x = list.pop(self)) != NONE ) {
    printf("popped: %d\n", x);
    list.print(self);
  }

  // drop quasi method
  list.drop(self)->print(self)->push(self, 5)->push(self, 4)->print(self);



  printf("so far so good\n");
  return 0;
}


// ===================================================== TEST
