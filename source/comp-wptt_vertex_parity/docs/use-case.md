---
date: 2026-03-18
authors:
    - joe_starr
contact: dr@joe-starr.com
abstract: A use case description for computation of the parity for a vertex in a WPTT
---

## Mathematical Description

We can model the production of a WPTT by combinations of the classical algebraic tangle operations
$+$ and $\vee$. When a vertex (band) is at an odd depth from the root of a WPTT the children of that
band are connected via $+$ operations. When a vertex is at an even distance from the root of a WPTT
its children are connected via $\vee$.

## Computational Description

To compute the parity of a WPTT we recursively compute the parity for each vertex starting at the
root. For computing the parity of weights on a band, we note that for even values the parity is $0$
(or $\infty$) and for odd the parity is $\chi$. We will assume the object vertex to be the root of
an identity WPTT this drastically simplifies the interface for the component. If a non-root vertex
is needed it's easy to convert the resultant parity to the "correct" form.
