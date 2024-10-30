# List

- lang: C
- repo: https://github.com/mandober/c-linked-list.git
- desc: various lists in C

## Features

Properties
- [x] singly-linked
- [ ] singly-linked with extra tail link
- [ ] doubly-linked
- [ ] homogeneous list
- [x] heterogeneous list
- [ ] monomorphic list
- [ ] monomorphization
- [x] implementation-owned data (storing copy of client's data)
- [ ] client-owned data (storing pointers to client's data)
- [x] generic list
- [ ] generics via macros
- [ ] generics via selections (enum polymorphism)
- [x] generics via void pointers and callbacks
- [ ] generics via class hierarchy (OOP emulation)
- [x] non-empty list
- [x] empty list possible by convention only (i.e. set `data` to NULL)
- [ ] unrolled list
- [ ] xor addressing
- [x] mutable
- [ ] immutable
- [ ] persistent
- [x] ephemeral
- [x] payload's type is `void*`
- [x] `Node` struct only
- [ ] `List` struct (holds common config + list "handle")
- [ ] circular list
- [x] open-ended list
- [x] linear
- [ ] non-linear
- [ ] algebraic, ℒₐ = 1 + a ℒₐ = 1+a²+aℒₐ = 1+a²+a³+aℒₐ = 1+a²+a³+a⁴+aℒₐ
- [x] recursive
- [ ] type-theoritical, λα. μβ. 1 + α × β
- [ ] non-recursive (ListF functor)
- [ ] List as least fixpoint
- [ ] List as greatest fixpoint
- [ ] ListT mt
- [ ] list as GADT, List a where Nil | Cons a (List a)
- [ ] list as sum type, List a = Nil | Cons a (List a)
- [ ] cons as pair, List a = Nil | Cons (a, List a)
- [ ] cons as Either, List a = Either () (a, List a)
- [ ] cons as Maybe, List a = Maybe (a, List a)
- [ ] list as product type (pair)
- [ ] list as right-associative, nested pair, (a, (b, (c, d)))
- [ ] list as left-associative, nested pair, (((a, b), c), d)
- [ ] list as lambda
- [ ] Church-encoded list
- [ ] Scott-encoded list
- [ ] list in Mogensen-Scott encoding
- [ ] list in Böhm-Berarducci encoding
- [ ] list in Parigot encoding
