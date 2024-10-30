# Monomorphism

## Contents

<!-- TOC -->

- [Contents](#contents)
- [Monomorphic data structures](#monomorphic-data-structures)
- [Monomorphization](#monomorphization)

<!-- /TOC -->

## Monomorphic data structures

A monomorphic data structure is a structure that is fixed at a particular concrete type; that is, the type of elements the structure holds is fixed.

We'd have to code another version of this structure to have it support a different type of elements.

A list that efficiently works with integers will have to be coded again to support the double type. And again to work with floats. And again and again for each distinct type we'd like to store in it. And that is only for lists - when we consider all the other data structures we might need, the situation becomes untennable. Of course, computer science has been aware of this problem for a long time, and it came up with a solution called *polymorphism*.

## Monomorphization

Some programming languages implement polymorphism by having type parameters range over all types. The user (client) of some polymorphic data structure can use that structre at any type. Come compilation time, all the different (by type) instances of the same data structure are determiend and the comiler then creates a monomorphic version of the data structure, that is, one monomorphic version for each type the user has instantiated the structure at.

Data structures are polymorphic, but each instantiation of a data structure ends up creating a monomorphic version of that data structure. This is probably similar to obtaining generics through macros in C; each distinct (type-wise) call to a macro function creates a distinct piece of the resulting code.

>Monomorphization is the creation of different versions of the same data structure at each type the user has instantiated it.

Monomorphization happens with C++ templates, and it is the default way of realizing generics in Rust. The final executable will contain as many versions of the same data structure as there were concrete types it was instantiated at, which is the reason some people complain about code bloat.
