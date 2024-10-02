# Generic Linked List

C implementation of a generic singly-linked list relying on void pointers.

- name: c-linked-list
- desc: generic singly-linked list data structure
- lang: C
- repo: https://github.com/mandober/c-linked-list.git

## Concepts

Generics in C are realized with the help of void pointers (`void*`). Generics are a form of [polymorphism](./polymorphism).

Generics primarily pertain to data structures, and then by extension, to functions that operate on them. 

In generic programming, algorithms are written in terms of an unspecified type, a type that will be specified later. The type is not known at the time of implementation, but it will be known later, at the time of instantiation. 

For a data structure to work over many different types, the type of the payload cannot be some concrete type (like `int`); instead, it is represented by a type parameter. A *type parameter* is placeholder for a type, just like a term-level variable is a placeholder for a value. When a generic data structure is *instantiated*, a concrete type replaces the corresponding type parameter.

## Considerations

Some things to consider when implementing support for polymorphism
- type of polymorphism
  - universal polymorphism
  - ad hoc polymorphism
    - enumeration polymorphism
  - row polymorphism
  - subtyping polymorphism
- variance
- instantiation

## Instantiation

Instantiation of a generic data structure
- monomorphism

*Monomorphism* is about creating as many concrete variants of a generic data structure as there are uses at different concrete types. If the user instantiates a generic list at the concrete type `Person`, then the compiler *monomorphizes the generic data structure*, creating a *concrete list implementation* in terms of the type `Person`, i.e. with `Person` as the type of payload. If the user instantiates a new list at the type `int` (it's always the bloody `int`, ain't it), then the compiler generates another implementation of list in terms of `int`.

>Each time the user instantiates a generic data structure at some type, the compiler generates an implementation of that data structure in terms of that concrete type.

It is usually said that this approach can lead to code bloat with all the different implementations increasing code size, but that is not a valid point within the confines of C, cos it would be no different, code size-wise, if we coded all thoese variants ourselves. Alas, C doesn't support monomorphization, so you are hypothetically-complaining about the counterfactual code bloat just for the sake of complaining (l'snivelling pour l'snivelling).



## Elements

- Node: element of the list, holds a payload. Allocated on the heap
- List: represents the list, manages its nodes. List is a struct on the stack.
- Macros: misc. types grouped in one place (todo: explore genericity).

## Macros

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
  Node *next; // 8B  \
  i32   item; // 4B   > 16 Bytes
  i32   hits; // 4B  /
};
```

Node struct has 3 fields (8, 4, 4 bytes), it is aligned on 16 bytes, no padding needed. Nodes are stored on the heap, so only a pointer to the node (8 bytes) is being passed around. The third field `hits` counts the number of times a node is accessed in order to implement move-to-front optimization.



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
  usize (*len)(List*);
  List *(*push)(List*, i32);
  List *(*drop)(List*);
  List *(*print)(List*);
  i32   (*pop)(List*);
};
```

Although list struct has several fields, only a pointer to it is passed around, except on list creation by the `list_new` function that retururns a list by value. The list is stored on the stack.


## Quasi methods

In order to have method-like calls, the list maintains a collection of function pointers to functions whose parameter is a pointer to the list,`List*`, which point to similarly named functions.

Namely, the function, for example, `list_push`, that adds an element to the front of the list, called as `list_push(&list, 5)`, can now be called in method-like style, which also allows for call chaining:

```c
// create new list `list`, declare ptr to the list, `self`
List list = list_new(), *self = &list;

// so the calls can be:
list.len(self);

// or:
list.print(self)->push(self, 5)->push(self, 4)->push(self, 3)->print(self);
```

If list had a stable address (alloc), the list struct could also hold a pointer to it, which would allow ommitting the `self` parameter, but then the arrow operator would be mandatory everywhere.

```c
// with list on the stack
list.len(self);

// with list on the heap
list->len();
```
