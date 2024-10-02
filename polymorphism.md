# Polymorphism

## Monomorphic data structures

A data structure like a linked-list can be created fairly quickly, but the problem is that the type of payload is fixed. A list that efficiently works with integers will have to be coded again to support the double type. And again to work with floats. And again and again for each distinct type we'd like to store in it. And that is only for lists - when we consider all the other data structures we might need, the situation becomes untennable.

Of course, computer science has been aware of this problem for a long time, and it came up with a solution called *polymorphism!* or *generics* (usually they are synonyms, but sometimes slightly different).

## Polymorphism!

Polymorphism ("many forms") is about writing algorithms with the types left unspecified; the types are to be filled in later, usually at the use site, and in the mean time they are replaced with *type parameters*. Polymorphism mostly pertains to data structures and then by extension to functions that operate on them.

Polymorphism comes in several flavors determined by the set of types that type parameters range over.

When type parameters range over all types, that is called *universal* or *parameteric polymorphism*, and it even gets us theorems for free ("Theorems for free!", Philip Wadler, 1989 [tf]). These theorems we get for free are the consequence of the realization that **the more generic a value, the less we can do with it**. A *parameterically polymorphic function* can work with any and all types; with any conceivable type - past, present or future. But with such great power, comes the responsibility not to use any devious manipulations, but to handle these polymorphic values properly; which means, it can't do shit with or to them.

Sticking with the introductory level of polymorphism, a polymorphic argument that a function receives *cannot be inspected*, so the function cannot base its behavior on the result of such inspection (e.g. if it is a bool, do this, if int, do something else; it's not that this is outright prohibited, but it requires type shenanigans that only some type systems support).

The examplary parameterically polymorphic function is `identity`. It can take a value of any type at all, but the only thing it can do with it is return it. This is the way of universal polymorphism, and the behavior instilled by it can be read off from type signatures, which is for the identity function stated as `id : ∀a. a -> a` (where `a` is a type parameter). This signature says that the `id` function can accept any type (for all types `a`, it takes a value of type `a`)

`id : {A : Set} -> A -> A`



but it cannot do very much with it.

The identity function can accept 



the problem is the monomorphic nature of C



Generics pertain to functions and data structures. A generic data structure can hold the payload of different type; a generic function can work with many distinct types.


that are then instantiated when needed for specific types provided as parameters. 


## Generics in C

C has no *generics*, but we can emulate a resticted form of *polymorphism* using the **void pointer** (`void*`) to hold the payload. Just like in *universal polymorphism*, we cannot inspect such polymorphic payload.


This leads to the realization that the more generic a value is, the less we can do with it. The identity function can accept any conceivable type, past, present or future, but it cannot do very much with it.

 If all the types of a programmng language support the print method, then a proper polymorphic function can print the received value. Either that or it can only return it as is. The latter is true for languages that do not support printing functions; function types are usually the deal breaker like that. For example, C divides all its types into two groups: objects and function types [ct].


[ct]: https://en.cppreference.com/w/c/language/type#Type_groups
[tf]: https://dl.acm.org/doi/10.1145/99370.99404




we can only do things that all the types have in common.

The void pointer has the *universal pointer type* with regard to other pointers - it sits on top of the pointer type hierarchy because any typed pointer may be assigned to it.



This assignment includes the *implicit pointer type conversion*, i.e. the type conversion of a typed pointer to a pointer of type void.

The type T may be a base type or another pointer type - void pointer can hold any. Operationally, nothing happens when a pointer is assigned to a void pointer; the underlying data remains intact. And the same is true when we later assign the void pointer to a *typed pointer*.
