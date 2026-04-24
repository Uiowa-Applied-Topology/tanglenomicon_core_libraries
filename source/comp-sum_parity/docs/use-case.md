---
date: 2026-03-31
authors:
    - joe_starr
contact: dr@joe-starr.com
abstract: A use case description for computation of the parity for a vertex in a WPTT
---

## Mathematical Description

Every two string tangle comes equipped with four fixed points labeled NW, NE, SW, and SE. In every
tangle these fixed points are connected to each other in pairs by two strings. We classify these
connections by those present in the four basic tangles ($0$, $1$, $-1$, and $\infty$). The full
table of connectivity can be seen be low.

| x   | NW                                    | NE                                    | SW                                    | SE                                    |
| --- | ------------------------------------- | ------------------------------------- | ------------------------------------- | ------------------------------------- |
| NW  | x                                     | ![zero](./media/0.svg){ width="40" }  | ![inf](./media/inf.svg){ width="40" } | ![1](./media/1.svg){ width="40" }     |
| NE  | ![zero](./media/0.svg){ width="40" }  | x                                     | ![1](./media/1.svg){ width="40" }     | ![inf](./media/inf.svg){ width="40" } |
| SW  | ![inf](./media/inf.svg){ width="40" } | ![1](./media/1.svg){ width="40" }     | x                                     | ![zero](./media/0.svg){ width="40" }  |
| SE  | ![1](./media/1.svg){ width="40" }     | ![inf](./media/inf.svg){ width="40" } | ![zero](./media/0.svg){ width="40" }  | x                                     |

Notice that the $\pm 1$ tangles have the same connectivity we label this as $\chi$. We call the
connectivity class of a tangle its **parity**.

Now, we examine parity under the $+$ and $\vee$ operations.
We enumerate the parity under the operations as follows:

| $+$      | $0$      | $\chi$   | $\infty$ |
| -------- | -------- | -------- | -------- |
| $0$      | $0$      | $\chi$   | $\infty$ |
| $\chi$   | $\chi$   | $0$      | $\infty$ |
| $\infty$ | $\infty$ | $\infty$ | $\infty$ |

| $\vee$   | $0$ | $\chi$   | $\infty$ |
| -------- | --- | -------- | -------- |
| $0$      | $0$ | $0$      | $0$      |
| $\chi$   | $0$ | $\infty$ | $\chi$   |
| $\infty$ | $0$ | $\chi$   | $\infty$ |

An interesting consequence of the $\infty+\infty$ and $0\vee0$ cases is the introduction off of a
knotted component of the tangle.

<!-- rumdl-disable -->
> [!Example]
>
> Consider the algebraic tangle expression $\frac{1}{2}+\frac{1}{2}$ which resolves as
>
> ![$\frac{1}{2}+\frac{1}{2}$](./media/[2_0]+[2_0].svg){width="500"}
>
> /// caption
>
> Result of $\frac{1}{2}+\frac{1}{2}$.
>
>///
>
> We see in red the knotted component introduced by the operation.
>
> ![bubble](./media/bubble.svg){width="500"}
>
> /// caption
>
> Components of the resultant tangle.
>
>///
<!-- rumdl-enable -->

Taking parity with a count of components is invariant for the tangle.

## Computational Description

No special computational considerations.
