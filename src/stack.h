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

#define usize size_t
#define i32 int32_t
#define NONE INT32_MAX

// forward declarations
struct node_s;
struct list_s;

// aliases: bring identifiers from tag into ordinary namespace
typedef struct node_s Node;
typedef struct list_s List;

// function prototypes
Node* node_new(Node* next, i32 item);
Node* node_drop(Node* node);
List  list_new();
i32   list_pop(List* list);
usize list_len(List* list);
List* list_drop(List* list);
List* list_push(List* list, i32 item);
List* list_print(List* list);
