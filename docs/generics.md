## Generics in C

## TL/DR

C lacks generics, but we can emulate a resticted form of polymorphism using void pointers to hold the payload of unknown type. Just like in universal polymorphism, we cannot inspect the polymorphic payload, meaning we cannot dereference a void pointer.

## Pointers

Pointers belong to a group of types called *derived types*. This is because each pointer is derived from some *base type*. For any (base) type `T`, we can derive a new type, a pointer to `T` denoted by `T*`.





## Void pointer

Void pointer is a *universal pointer type* because any *typed pointer* may be assigned to it, and it can be assigned to any typed pointer. No explicit type conversion (type cast) needed - this is an *implicit type conversion* between compatible types.

```c
int x;    // here, x contains a garbage value
x = 42;   //   now x contains the integer 42
int* px;  // here, px points to an arbitrary, possibly invalid, address
px = &x;  //   now px contains a valid address
void vp;  // here, vp points to an arbitrary, possibly invalid, address
vp = px;  //   now vp contains a valid address
```


The type T may be a base type or another pointer type - void pointer can hold any.

Operationally, nothing happens when a pointer is assigned to a void pointer; the underlying data remains intact. And the same is true when we later assign the void pointer to a *typed pointer*.
