---
date: 2026-03-16
authors:
  - joe_starr
contact: support@joe-starr.com
abstract: A use case description for computation of a piecewise linear path in $\R^3$ arborescent tangle computation.
---

## Mathematical Description

Definitionally, a tangle is a set of $S^1$ and intervals in $\R^3$ or $S^3$. In practice, we often
encode tangles as planar diagrams with over/under crossings. In computational contexts these
diagrams are encoded into convenient combinatorial forms, in the case of an arborescent tangle these
are the WPTT. For some research contexts, particularly those with physical considerations, encoding
a tangle into a piecewise linear (PL) path in $\R^3$ is ideal. We now describe a method for
converting a WPTT (in reality we will describe a method for identity tangle trees ITT) into a PL
path.

An ITT can be converted to a PL path in a number of different ways. For example, we could leverage
the necklace model given by Bonahon and Siebenmann[@bonahonNewGeometricSplittings2016]. This method
has the benefit of being easily manipulated by Möbius transformations. Unfortunately, the method of
Bonahon and Siebenmann is quite complex, in the interest of effort we will describe here a slightly
more convenient method. This method, when compared to the Bonahon and Siebenmann construction, is
hard to modify mathematically but quite easy to work with computationally.

When we render an ITT diagrammatically we see that one clear choice for building blocks are the
basic ($0$, $\ifty$, and $\pm 1$) tangles. The $\pm 1$ tangles can be built into horizontal and
vertical integral tangles with the $+$ and $\vee$ operations, seen in different colors below.

![ITT](./media/example_tangle.svg)

/// caption

The ITT $((2[3][-3])[4])$ rendered diagrammatically.

///

To build with theses we first select a coordinate system (below) and define PL encodings for the
four basic tangles.

![coordinate system](./media/v4_rotations.svg)

/// caption

The coordinate system used for the encoding of tangles as PL paths.

///

| Tangle   | Image                   | Component One                       | Component Two                       |
| -------- | ----------------------- | ----------------------------------- | ----------------------------------- |
| $0$      | ![0](./media/0.svg)     | $(-1,1,0)\to(0,0.5,0)\to(1,1,0)$    | $(-1,-1,0)\to(0,-0.5,0)\to(1,-1,0)$ |
| $\infty$ | ![inf](./media/inf.svg) | $(-1,1,0)\to(-0.5,0,0)\to(-1,-1,0)$ | $(1,1,0)\to(0.5,0,0)\to(1,-1,0)$    |
| $1$      | ![-1](./media/1.svg)    | $(-1,1,0)\to(0,0,-1)\to(1,-1,0)$    | $(-1,-1,0)\to(0,0,1)\to(1,1,0)$     |
| $-1$     | ![1](./media/m1.svg)    | $(-1,1,0)\to(0,0,1)\to(1,-1,0)$     | $(-1,-1,0)\to(0,0,-1)\to(1,1,0)$    |

Next we describe how to build integral tangles from the $\pm 1$ tangles. Start by placing a PL
$\pm 1$ tangle into the ambient space. Next, take a second $\pm1$ tangle and translate it so the
left endpoints of the second tangle align with the right endpoints of the initial tangle (or bottom
and top for $\vee$). Finally, combine paths where they coincide by taking the union of the paths.

To extend this method to the general arborescent case is straight forward, requiring only a few
additions. The first addition is a change to the "gluing" of paths. When applying a $+$ or $\vee$
operation to a general tangle the endpoints will generally not agree. In these cases instead of
taking a union we will introduce a new path segment between the sets of endpoints. It's also
important to note that in some cases an operation will "cap off" an internally knotted component,
locations where components are capped off are determined based on the
[parity][comp-wptt_vertex_parity] of the operands. Where this occurs can be determined by the parity
of the two summands. Finally, we will enforce that the fixed points of every tangle sit on the
corners of the bounding cube box of that tangle. This requires the addition of up to four extra
path segments per subtangle.

> [!example]
>
> ### $1+1$
> To build an integral $2$ tangle we start with two copies of the strands
> $(-1,1,0)\to(0,0,-1)\to(1,-1,0)$ and $(-1,-1,0)\to(0,0,1)\to(1,1,0)$. We then translate the second
> set of strands over by two units in $x$ resulting in the paths $(1,1,0)\to(2,0,-1)\to(3,-1,0)$ and
> $(1,-1,0)\to(2,0,1)\to(3,1,0)$. Combining the four path components then yields:
>
>| Tangle | Image               | Component One                                                                              | Component Two                                                                               |
>| ------ | ------------------- | ------------------------------------------------------------------------------------------ | ------------------------------------------------------------------------------------------- |
>| $2$    | ![2](./media/2.svg) | $\begin{aligned}(-1,1,0)&\to(0,0,-1)\\&\to(1,-1,0)\\&\to(2,0,1)\\&\to(3,1,0)\end{aligned}$ | $\begin{aligned}(-1,-1,0)&\to(0,0,1)\\&\to(1,1,0)\\&\to(2,0,-1)\\&\to(3,-1,0)\end{aligned}$ |
>
> ### $\infty+\infty$
>
> To build an integral $\infty + \infty$ tangle we start with two copies of the strands
> $(-1,1,0)\to(-0.5,0,0)\to(-1,-1,0)$ and $(1,1,0)\to(0.5,0,0)\to(1,-1,0)$. We then translate the
> second set of strands over by two units in $x$ resulting in the paths
> $(1,1,0)\to(1.5,0,0)\to(1,-1,0)$ and $(3,1,0)\to(2.5,0,0)\to(3,-1,0)$. Combining the four path
> components then yields:
>
>| Tangle           | Image                                  | Component One                                                       | Component Two                                                    | Bonus Component (Red)                                                                        |
>| ---------------- | -------------------------------------- | ------------------------------------------------------------------- | ---------------------------------------------------------------- | -------------------------------------------------------------------------------------------- |
>| $\infty +\infty$ | ![$\infty+\infty$](./media/bubble.svg) | $\begin{aligned}(-1,1,0)&\to(-0.5,0,0)\\&\to(-1,-1,0)\end{aligned}$ | $\begin{aligned}(3,1,0)&\to(2.5,0,0)\\&\to(3,-1,0)\end{aligned}$ | $\begin{aligned}(1,1,0)&\to(0.5,0,0)\\&\to(1,-1,0)\\&\to(1.5,0,0)\\&\to(1,1,0)\end{aligned}$ |

## Computational Description

We will maintain some extra information with our paths. First we will track the width and heights of
tangles as they are being built. Tracking this allows us to easily translate components of paths.
Next we must track or compute the parity of tangles as we build. This allows us to detect when we
must cap off internally knotted components.

Additionally, for aesthetic reasons our PL paths will skip all zero weights of non-leaf vertices.
