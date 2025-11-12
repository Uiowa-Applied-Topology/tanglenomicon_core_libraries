---
date: 2024-09-18
authors:
    - Joe Starr
contact: support@joe-starr.com
abstract: A use case description for the PL plpath Notation.
---

# Use Case

## Functionality

### Mathematical description

##### Notation for piecewise linear path in $\R^3$

A mathematical knot is a smooth embedding of a collection of $S^1$ into $\R^3$ or $S^3$. These
smooth curves can be approximated by a collection of piecewise linear paths. Those curves can be
encoded as a collection of points in $S^3$ as a one point compactification of $\R^3$. We encode the
point at infinity with the triple $\LP\infty,\infty,\infty\RP$.

To support the encoding of tangles (as well as other similar objects) we allow for open paths.
Meaning curves with endpoints that are not equal.

### Computational Description

There are no special computational considerations for this use-case.

## Bibliography

```{bibliography}
   :filter: docname in docnames
```

```{raw} latex
    \newpage
```
