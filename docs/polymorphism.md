# Polymorphism

## TL/DR

This is about polymorphism in general; it has less to do with C.

## Contents

<!-- TOC -->

- [TL/DR](#tldr)
- [Contents](#contents)
- [Polymorphism](#polymorphism)
- [Types of polymorphism](#types-of-polymorphism)
  - [Parametric polymorphism](#parametric-polymorphism)
    - [Theorems for free](#theorems-for-free)
  - [Ad hoc polymorphism](#ad-hoc-polymorphism)
  - [Subtyping polymorphism](#subtyping-polymorphism)
    - [Variance](#variance)
      - [Covariance](#covariance)
      - [Contravariance](#contravariance)
  - [Row polymorphism](#row-polymorphism)

<!-- /TOC -->

## Polymorphism

Polymorphism ("many forms") is about writing algorithms with the types left unspecified; the types are to be filled in later, when the structure is instantiated (usually at the call site), and in the mean time, the type is represented with a *type parameter*. However, once the structure is instantiated at some concrete type, the type is fixed for that instance. But we can instantiate that data structure at another type, meaing we can have e.g. a list of integers, and another (separate) list of doubles.

Some programming languages implement polymorphism exactly in this way: a data structure is polymorphic, but each instantiation creates a version of that data structure at some concrete type. The compiler then monomorphizes the data structure at each type the user has instantiated it. *Monomorphization* happens in C++ when using templates, as well as with Rust's generics. The final executable will contain as many versions of the same data structure as there were concrete types it was instantiated at.

This is contrasted with how generics work in C: using the void pointers, there is eventually only one data structure that works with all types. This is certainly better but the downside is the loss of type safety that comes with the use of void pointers. However, since such implementations are typically done as non-standard libraries (once to last), there is plenty of chance to get it right.

One of the differences between proper polymorphism and C's generics is that void pointers are not really like type parameters. Type parameters are related by name - the same type parameter represents the same type. When a function takes and returns a type parameter `A`, then when it is called with a concrete type suppiled, that concrete type will replace all occurrences of the type parameter `A`. On the other hand, in C, each `void*` parameter may be bound to a different pointer type, i.e. there is no way to relate them.

## Types of polymorphism

Polymorphism comes in several flavors determined by the set of types that type parameters may range over.
- parametric polymorphism, universal polymorphism
- ad hoc polymorphism, overloading, generics
- subtyping polymorphism
- row polymorphism

### Parametric polymorphism

In parametric or universal polymorphism, type parameters range over all types. Because the types are not restricted, this is often regarded as a true form of polymorphism.

A *parameterically polymorphic function* works with any and all types. Moreover, it works with any conceivable type, past, present or future type. But with such great power, comes the responsibility to avoid using devious manipulations, but to handle the polymorphic values properly; which means, we can't do shit with them. Devious manipulations include inspecting the type of a polymorphic value and then dispatching base on it. 

The examplary parameterically polymorphic function is `identity`. It takes a value of any type, but the only thing it can do with that value, according to its signature, is to return it untouched. The signature of the `identity` specifies its behavior:

```agda
id : {A : Set} -> A -> A
id {A} x = x
```

This code is in a theorem prover Agda, where the base types are collected in a set called `Set`; and `A : Set` means that `A` is in `Set`. This is the standard type theoretical notation where the thing on the left is said to have the type on the right. Here, `A` having the type `Set` means that `A` is a type parameter that ranges over all base types.

Aside: Unlike Haskell, Agda avoids the Type-In-Type axiom by having an infinite hierarchy of type, similar to the Russell's stratified type theory. This is needed exactly to avoid the Russell's paradox that could arise with Type-In-Type. Namely, everything must have a type, so if `Int : Set`, then we can also ask for the type of `Set`, and in Agda, `Set : Set₁`, then `Set₁ : Set₂`, and so on, ad infinitum. Anyway, base types of `Set₀`, aka `Set₀`, are where all the usual interesting types live.

Sticking with the introductory level of polymorphism, a polymorphic argument that a function receives *cannot be inspected*, so the function cannot base its behavior on the result of such inspection (e.g. if it is a `bool`, do this, if `int`, do something else; it's not that this is outright prohibited, but it requires type shenanigans that only some type systems support).

Back to the `identity` function; it shows a very interesting property of parameteric polymorphism:
>The more generic a value, the less we can do with it.

It is the signature of a polymorphic function that dictates its behavior. The signature constrains the identity function so much that the only sensible thing it can do is just return the value. 

#### Theorems for free

However, there are polymorphic functions that can do more interesting things. For example, the `map` function that applies a unary function to all elements of a list, or the `++` (concat) that joins two lists.

```haskell
map :: (a -> b) -> [a] -> [b]
map f []     = []
map f (x:xs) = f x : (map f xs)

(++) :: [a] -> [a] -> [a]
xs ++ [] = xs
(x:xs) ++ ys = x : (xs ++ ys)
```

Parameterically polymorphic function are associated with the so-called theorems for free ("Theorems for free!", Philip Wadler, 1989 [tf]). They show us the proofs of equivalences such as

    map f ++ map g = map (f ++ g)

These theorems we get for free are a consequence of parameteric polymorphism; namely, they are a consequence of the realization that the more generic a value, the less we can do with it. A function that works with all possible types can only do things to a polymorphic parameter that all those types have in common, which is usually very little or nothing at all. Since polymorphic data structures cannot inspect their payload, they can only perform manipulations that are the same regardless of the containing type. And this is exactly how we should approach generics in C.

### Ad hoc polymorphism

Ad hoc polymorphism, aka overloading, is a restricted form of universal polymorphism: instead of having type parameters range over all types, they only range over particular subsets.

In OO, these type subsets are formed based on iterfaces. An inteface like `Printable` collects the types that (whose values) can be printed. This interface could expose a single method like `print`. Then all types that are printable can elect to become members of the `Printable` type subset. We can then write functions with type parameters that range only over this subset. Such a function won't accept an argument type unless it implements the interface `Printable`. Such function then knows that it can safely call the `print` on the polymorphic argument because that type must support it. Other interfaces often include `Num` that collects the types whose values support basic arithemtic operations; if the `Num` interface defines a method called `+`, then we can use `+` at any two types that are members of `Num`. Some languages, including C, support `+` and similar operators as primitives. This is similar to manually implementing the *overloading* of symbols like `+`, `-`, `*`, `/`, etc.

**Overloading** is sometimes considered a form of ad hoc polymorphism, but it is often synonymous with it. Overloading is about using the same symbol, like `+`, at different types. That is, the meaning of the symbol is determined from the type it is used at. C++ favors overloading allowing us to define multiple versions of the same-named method provided each method has a distinct *signature* aka *prototype*.

This warants a precise definition of what constitutes a valid method signature. Namely, method signatures are distinguished by the number (arity) and type of parameters, and the return type (in fact, some languages don't count the return type as part of the method's prototype). So, e.g. in C++, when a method (with multiple versions) is called, the number and type of arguments is examined to determine which version of the method to invoke.

### Subtyping polymorphism

Subtyping polymorphism happens in OO languages when these kinds of questions arise: can a function, that normally accepts a subtype of `T`, safely accept the type `T` as well?

The fact that `S` is a subtype of type `T` may be denoted by `S <: T`. A subtype is a *more specialized* version of the type. The supertype is a *more general* version compared to its subtypes.

A type `T` is a *more general and less specialied* type then its subtype `S`.

`T` probably contains fewer fields, and/or its fields have a more general type then the same fields in its subtypes.

A subtype `S` is a *more specialied and less general* type then its supertype `T`.

In OO, the supertype `T` is usually a *base class*, from which multiple child classes are derived - the subtypes of `T`.

>*Subtype polymorphism* is about the questions like: Can a function that normally accepts some type `S`, safely accept the type `T` as well, knowing that `S <: T` (`S` is a subtype of `T`)?

#### Variance

Consider a type `Animal` (a class) from which a subtype `Cat` (child class) is derived using, e.g., `Cat extends Animal`. The subtyping relation is clear: Cat is a subtype of Animal, denoted `Cat <: Animal`. Dually, Animal is the supertype of Cat, denoted by: `Animal :> Cat`. `Animal` is the more general and less specialized type (compared to its subtype Cat); `Cat` is the more specialized and less general type (compared to its supertype Animal). This *subtyping relation* suggests that we may pass a `Cat` whenever an `Animal` is expected.

>Supertype is more general and less specialized (then its subtypes). 
>Subtype   is less general and more specialized (then its supertype).

We can now construct *compund types* based on these types. For example, we can construct a list of `Animal` and a list of `Cat`.

Now that we have base types `Animal` and `Cat` (its subtype), as well as compound types [Animal] and [Cat] based on them, is where the notion of variance kicks in.

>Variance refers to how the subtyping relation between the base types affects the subtyping relation between the compound types based on them.

More concretely, variance answers the question of how does `[Animal]` relates to `[Cat]`, knowing that `Cat <: Animal`.

Importantly, variance is not an emerging quality, but it is decided by 
the authors of a programming language. The authors can implement variance in one way or another, or they can choose to forgo of it completely. If they choose to implement variance, it would be weird for them to decide on some unprecedented variance relation; that is, if variance exists, people expect a certain behavior.

Types of variance
- covariance,     `v <: w` ⇒ `T(v) <: T(w)`
- contravariance, `v <: w` ⇒ `T(w) <: T(v)`
- invariance

The first two types of variance are the interesting ones, the third, *invariance*, just means the absence of variance.

##### Covariance

If `Cat <: Animal` then `[Cat] <: [Animal]`

means that the subtyping relation is preserved. That is, a list of `Cat` is (still) a subtype of a list of `Animal`, stemming from the fact that `Cat` is substype of `Animal`. This is called **covariance**, and it can be understood as a change in the same direction.

More formally, this classifies the `List` *type constructor* as being *covariant*. An example of a definition with a type constructor `List` may be:

```hs
data List a = Nil | Cons a (List a)
```

This type definition introduces a new type called list. `List` is also the name of one of the two type constructors; it is a unary type ctor since it takes a single type parameter, here denoted by `a`. The other type ctor, called `Nil`, represents an empty list, but it is not that interesting, variance-wise, as it takes no type params. The `List` type constructor takes a type param `a` and produces a list of `a`'s. We can represent this as a pseudo (type) function:

```hs pseudo
-- pseudo type function List
List :: a -> List a

-- can be instantiated at many types:
List Int = List Int
List String = List String
List (Maybe Char) = List (Maybe Char)

List Animal = List Animal
List Cat = List Cat
```

The type constructors List *preserves the subtyping relation*, so we can provide a `List Cat` (also denoted by `[Cat]`) when `List Animal` is expected.

##### Contravariance

Another compound type made from simple types is a *function type*.

However, unlike the plain unary `List` type ctor, the function type ctor is more complicated. First, it is a binary type ctor - it takes two type parameters to produce a *saturated type*. Second, it's not easy to denote it; using a pseudo Haskell syntax again, *function type* could be defined as:

```hs
data (->) a b = (->) a b
-- which is the same as
data a -> b = a -> b
-- which is equivalent to
data Function a b = Function a b
```

Function data type uses a symbolic name, `->`, but it could've been very well used an alphabetic name like `Function` (in Haskell, constructors with symbolic names can be used infix, i.e. between two type params).

With lists, there was never a question in which type parameter is the type ctor covariant because there was only a single one. But with functions, we need to be specific about the type parameter when we talk about the variance of function type ctor.

Function type ctor needs to be applied to two types in order to construct a complete (saturated) type - a function type. The first type param, `a` above, signifies the type of input (nominally, all functions are unary) and the second type param, `b` above, signifies the type of output (return type).

Variance is a relation between a type ctor and a particular type parameter. In case of a polyadic (arity > 1) type ctor, there is a separate notion of variance for each association of the type ctor and each type param. Since function type ctor is binary, there are two notions of variance for function types: one for the input type param (and the type ctor), and another for the output type param (and the type ctor).


To investigate it, we first set our example types as output types, with the input type fixed at `string` type. The question is does this seem reasonable:

if `Cat <: Animal` then `(string -> Cat) <: (string -> Animal)`

Can we say that whenever a function of type `string -> Animal` is expected, we can instead provide a function of type `string -> Cat`?

It seems reasonable: `Cat` is an `Animal`, so we should be good; whatever (fields) `Animal` has, `Cat` has as well. So we can count this as another case of *covariance*.

>Function type ctor is covariant in the output parameter.

Again, the decision to support variance and to make this be covariant is at the discretion of the language authors (it is not something predestined). That said, the situations that ask for variance have long ago been recognized and are now well explored, so unless there is a specific need, most languages that support variance will do so in the expected manner. This means that most type ctors will be (unsurprisingly) covariant. Function type ctor is a well known exception, being both covariant and contravariant.



To see how the function type ctor is **contravariant** in the input type, consider if this relation seems reasonable:

if `Cat <: Animal` then `(Animal -> string) <: (Cat -> string)`   
vs the (perhaps) expected alternative:   
if `Cat <: Animal` then `(Cat -> string) <: (Animal -> string)`

Look at that! So far `Cat` was always on the left, but now `Cat` and `Animal` have swapped places in the compound type.

The subtyping relation between the simple and compound type **reverses**, such that `Animal -> String` <: `Cat -> String`, i.e. a function from `Animal` to `String` is a subtype of function from `Cat` to `String`. 

Because the function type constructor is contravariant in the input type parameter, the subtyping relation is *reversed*, meaning that we can provide a function of type `Animal -> String` when a function of type `Cat -> String` is expected.

>Function type ctor is covariant in the input parameter, and contravariant is the output param.

---

Subtyping is a relation between more general and more specific types regarding some base type.

`Animal` type is a more general type then its subtype, `Cat`. `Cat` is a more specific type then its supertype, `Animal`. All `Cat`'s are `Animal`s, so whenever an `Animal` is expected, a `Cat` should do.

>When a more general type is expected, its subtype, although more specific, may be provided.

When there's subtype polymorphism, there's variance. Variance is about the relation between a type constructor and its type parameters.

*Covariance*: when a list of a more general type is expected, a list of a more specific type (a subtype of the more general type) may be provided.

*Contravariance*: when a more specific type is expected (as a function's input type), then a more general type (its supertype) may be provided instead.

- Covariance:     if `s <: a` then `C(s) <: C(a)`
- Contravariance: if `s <: a` then `F(a) <: F(s)`

- Covariance:     `s <: a ⇒           [s] <: [a]`
- Contravariance: `s <: a ⇒ (a -> String) <: (s -> String)`

```
s <: t ⇒          Set s  <:  Set t
s <: t ⇒         List s  <:  List t
s <: t ⇒        Maybe s  <:  Maybe t
s <: t ⇒   Map String s  <:  Map String t

s <: t ⇒     String → s  <:  String → t
s <: t ⇒     t → String  <:  s → String

a <: a ⇒     String → a  <:  String → a
a <: a ⇒     a → String  <:  a → String
```

When the same type parameter represents both an input and output type, the relation between the function type ctor and such type param is *invariance*.



### Row polymorphism

Row polymorphism pertains to tuples or record types. It is about compatibility of two records that differ in the number and type of their fields.

For example, considering these two records that differ only in that the `Employee` record has an extra field, `id: int`, the question is can a function that normally accepts instances (values) of the `Person` record, also accept a `Employee` record instance?

```
record Person { name: string, age: int }
record Employee { name: string, age: int, id: int }
```

We can see that it could since the `Employee` record contains all the necessary fields, so that function could support this type as well, simply ignoring the extra field.

Whether a language supports row polymorphism is down to its authors and the potential benefits of supporting it.


[tf]: https://dl.acm.org/doi/10.1145/99370.99404
