---
date: 2025-11-16
authors:
  - Joe Starr
contact: support@joe-starr.com
abstract: A use case description for mutation of a WPTT by $F_i$ move.
---

# Use Case

## Functionality

### Mathematical Description

Bonahon and Siebenmann [@bonahonNewGeometricSplittings2016] define a collection of moves on
[weighted planar tangle trees (WPTT)][note-wptt] that preserve the isotopy type of the underlying
tangle. This component realizes three of those moves: $F_3^\prime$, $F_2$, and $F_1$.

<!-- prettier-ignore-start -->

!!! definition "Bonahon and Siebenmann Section 12.7.3 [@bonahonNewGeometricSplittings2016]"

    The **$F_3^\prime$ move** on a weighted arborescent tree moves a weight $w$ as
    ![](./media/f3/f3p_def.svg) and, if $w$ is odd, reverse the cyclic order of weights and
    bonds at all vertices of the purple subtree lying at odd distance (count of edges between two
    vertices) from the vertex shown. Also, when $w$ is odd, apply $\xi$ ( $X$-axis rotation) to all free
    bonds in the purple subtree that are attached to a vertex at even distance from the vertex shown,
    and $\eta$ ($Y$-axis rotation) to those at odd distance. The rotations are relative to the
    orientation of the plumbing square (Conway sphere) of the band being acted on.

<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->

!!! definition "Bonahon and Siebenmann Section 12.7.1 [@bonahonNewGeometricSplittings2016]"

    The **$F_2$ move** on a weighted arborescent tangle tree reverses the cyclic order of bonds and
    weights at one vertex on the tree and at every vertex at even distance from it; also apply $\eta$
    ($Y$-axis rotation) to every free bond of a vertex at even (or zero) distance, and apply $\xi$
    ($X$-axis rotation) to every free bond at odd distance. The rotations are relative to the
    orientation of the plumbing square (Conway sphere) of the band being acted on.

<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->

!!! definition "Bonahon and Siebenmann Section 12.7.1 [@bonahonNewGeometricSplittings2016]"

    The **$F_1$ move** on a weighted arborescent tangle tree reverses the cyclic order of bonds and
    weights at every vertex of the graph and applies $\zeta$ ($Z$-axis rotation) to every free bond. The
    rotations are relative to the orientation of the plumbing square (Conway sphere) of the band being
    acted on.

<!-- prettier-ignore-end -->

### Computational Description

A computational framing of the moves on a [weighted planar tangle trees (WPTT)][note-wptt] is
slightly problematic. The notational WPTT is formed by a collection of singly linked lists where
parents point to children. This directional linkage means moving "up" a tree from child to parent is
functionally difficult. This requires special handling for each of the moves. When a $F_3^\prime$
shift is requested over a parent connection, we will instead model the shift as the equivalent
collection of $F_3^\prime$ moves in the opposite direction. Next, for the $F_1$ and $F_2$ moves, we
will assume that the vertex passed to the mutator is the root vertex. Our final consideration is for
the $F_2$ move, we must indicate whether to operate on the equivalence class of the indicated vertex
or that of its children.
