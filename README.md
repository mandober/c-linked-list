# Linked List

Stack implemented with a linked list.

- name: c-linked-list
- project: Linked lists in programming languages
- category: data structures
- lang: C
- repo: https://github.com/mandober/c-linked-list.git


## Elements
- Node: element of the list, holds a payload. Allocated on the heap
- List: represents the list, manages its nodes. List is a struct on the stack.
- Macros: misc. types grouped in one place (todo: explore genericity).


### Macros
These macro definitions are for easing the conversion of this implementation for another payload type.

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

```c
struct node_s {
  Node *next; // 8
  i32   item; // 4
  i32   hits; // 4
};
```


### List
- `struct list_s`
- typedef: `List`
- fields:
  - `head`: pointer to the first node
  - `length`: size of the list i.e. number of nodes
- fields for quasi methods:
  - `list_len`  : `len` method, `list.len(self)`
  - `list_push` : `push` method, `list.push(self, 5)`
  - `list_pop`  : `pop` method, `list.pop(self)`
  - `list_print`: `print` method, `list.print(self)`
  - `list_drop` : `drop` method, `list.drop(self)`

```c
struct list_s {
  Node *head;
  usize length;
  /* more fields elided */
};
```


## Quasi methods
In order to have prettier call sites, the list maintains a collection of function pointers to functions whose parameter is a pointer to the list,`List*`,

Quasi methods are realized through the function pointers contained in the list struct's fields, which point to similarly named functions. Namely, the function, for example, `list_push`, that adds an element to the front of the list, is called as `list_push(&list, 5)`, but quasi methods allow for calls that resemble methods and that can be chained:

```c
// create new list, create a ref to the list
List list = list_new(), *self = &list;
// now with pointer to list named `self`, quasi methods look like:
list.len(self);
// and allow chaining
list.print(self)->push(self, 5)->push(self, 4)->push(self, 3)->print(self);
```
