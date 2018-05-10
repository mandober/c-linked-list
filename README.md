# Linked List

Stack implemented with a linked list.

- project: c-linked-list
- category: data structures
- lang: C
- repo: https://github.com/mandober/c-linked-list.git


## Elements
- node: element of the list, holds a payload
- list: represents the list, manages its nodes

### Macros
These macro definitions are for easing the conversion of this implementation for another payload type (todo: explore possibility for a generic list).

- `usize` is the type of list length.
- `i32` is the type of the payload; it is a nullable type:
- `NONE` is in-band signaling that represents absent `int32_t` value.

```c
#define usize size_t
#define i32 int32_t
#define NONE INT32_MAX
```

### Node
- `struct node_s`
- typedef: `Node`
- fields:
  - `next`: pointer to the next node
  - `item`: payload
  - `hits`: number of accesses to this node

### List
- `struct list_s`
- typedef: `List`
- fields:
  - `head`: pointer to the first node
  - `length`: size of the list i.e. number of nodes
- fields for quasi methods:
  - `list_len`  : `len` method, `list.len(self)`
  - `list_push` : push method, `list.push(self, 5)`
  - `list_pop`  : pop
  - `list_print`: print
  - `list_drop` : drop

```c
struct list_s {
  Node *head;
  usize length;
  /* more fields elided */
};
```



## Quasi methods
Quasi methods are realized through the function pointers contained in the list struct's fields, which point to similarly named functions. Namely, the function, for example, `list_push`, that adds an element to the front of the list, is called as `list_push(&list, 5)`, but quasi methods allow for calls that resemble methods and that can be chained:

```c
// create new list, create a ref to the list
List list = list_new(), *self = &list;
// now with pointer to list named `self`, quasi methods look like:
list.len(self);
// and allow chaining
list.print(self)->push(self, 5)->push(self, 4)->push(self, 3)->print(self);
```





  * Functions:
  - node_new
  - node_drop
  - list_new


  GENERIC LIST?
  Generic list i.e. generic payload
  - generics with macros or by adding more params to fns i.e.
    delegating more responsibility to the caller?
  - fns must take additional params to know payload size, type
  - does payload live on the stack or heap?
    who will free it if on the heap?
  - should fns take payload by value or by ref?
  - too many complications, too much relies on the caller ...
  fuck it: make payload an i32, list on stack, nodes on heap.


  UTILITIES:

  i32 Length(struct node* head);

  struct node* BuildOneTwoThree();
  // Allocates and returns the list {1, 2, 3}.

  void Push(struct node** headRef, i32 newData);
  Given an i32 and a reference to the head pointer (i.e. a struct
  node** pointer to the head pointer), add a new node at the head of the
  list with the standard 3-step-link-in:
  - create the new node
  - set its .next to point to the current head
  - change the head to point to the new node.


  USAGE:

  Push(&head, 13);
  //: {13, 1, 2, 3}
  // '&' used cuz the head is passed as a reference pointer


  struct node* head = BuildOneTwoThree();
  //: {1, 2, 3}


  Push(&(head->next), 42);
  //: {13, 42, 1, 2, 3}
  // Push 42 into the second position. Shows the use of '&' on `next` field


  i32 len = Length(head);
  //: 5