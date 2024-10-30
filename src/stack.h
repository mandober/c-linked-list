/*
  stack.h
  linked list: stack implemented with a linked list.
*/
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define usize size_t // pointer size
#define i32 int32_t  // payload type

// test inferrence
// #define var __auto_type
// #define let __auto_type const

// pop: payload return: either NULL(err) or i32(ok)
union Option {
  i32* err;
  i32  ok;
};

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
  It points to the first node and manages nodes and quasi methods.
*/
struct list_s {
  Node *head;
  Node *tail;
  usize length;
  // quasi methods
  usize (*len)(List*);
  List *(*push)(List*, i32);
  List *(*drop)(List*);
  List *(*print)(List*);
  union Option (*pop)(List*);
};

// aliases: bring identifiers from tag into ordinary namespace
typedef struct node_s Node;
typedef struct list_s List;

// function prototypes
Node* node_new(Node* next, i32 item);
Node* node_drop(Node* node);
List  list_new();
union Option list_pop(List *list);
usize list_len(List* list);
List* list_drop(List* list);
List* list_push(List* list, i32 item);
List* list_print(List* list);

void test();
