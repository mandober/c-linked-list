/*
  LINKED LIST
  Stack implemented with a linked list.

  stack.h
*/
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// pointer size
#define usize size_t
// payload type
#define i32 int32_t
// payload marker: nothing to return (used in `pop`)
#define NONE INT32_MAX

// test inferrence
#define var __auto_type
#define let __auto_type const

// forward declarations
struct node_s;
struct list_s;

// pop: payload return: either NULL(err) or i32(ok)
union Option {
  i32* err;
  i32  ok;
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