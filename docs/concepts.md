# Linked List

C implementation of a generic singly-linked list relying on void pointers.

- name: c-linked-list
- desc: generic singly-linked list data structure
- lang: C
- repo: https://github.com/mandober/c-linked-list.git



## Concepts

Generics in C are realized with void pointers (`void*`). Generics are a form of restricted [polymorphism](./polymorphism.md). Generics primarily pertain to data structures, and then by extension, to functions that operate on them.

In generic programming, algorithms are written in terms of an unspecified type, a type that will be specified later. The type is not known at the time of implementation, but it will be known later, at the time of instantiation.

For a data structure to work over many different types, the type of the payload cannot be some concrete type (like `int`); instead, the type of the payload is represented by a type parameter. A *type parameter* is placeholder for a type, just like a term-level variable is a placeholder for a value. When a generic data structure is *instantiated*, a concrete type replaces the corresponding type parameter consistently (everywhere it is mentioned). Such a data structure is *homogeneous* because once the type parameter is instantiated, it is fixed. *Heterogeneous* data structure, on the other hand, can store data of different types. A list can be realized as both.

## The plan

First, we implement a singly-linked list as a monomorphic data structure, fixed to the type `long`, to get a grip how the data is manipulated without worrying also about generics. This will present the base case for the comparision with the generic implementation.

implementation (wip)


## Topics

- [Monomorphism](./monomorphism.md)
  - [Monomorphic data structures](./monomorphism.md#monomorphic-data-structures)
  - [Monomorphization](./monomorphism.md#monomorphization)
- [Polymorphism](./polymorphism.md)
  - [Types of polymorphism](./polymorphism.md#types-of-polymorphism)
    - [Parametric polymorphism](./polymorphism.md#parametric-polymorphism)
      - [Theorems for free](./polymorphism.md#theorems-for-free)
    - [Ad hoc polymorphism](./polymorphism.md#ad-hoc-polymorphism)
    - [Subtyping polymorphism](./polymorphism.md#subtyping-polymorphism)
      - [Variance](./polymorphism.md#variance)
    - [Row polymorphism](./polymorphism.md#row-polymorphism)
