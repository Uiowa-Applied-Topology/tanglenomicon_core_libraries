---
date: 2024-09-18
status: test
authors:
    - Joe Starr
contact: support@joe-starr.com
abstract: A use case description for defs on rational tangle data.
---

# Use Case

## Functionality

### Mathematical Description

The rational tangle computation module computes 3 pieces of data for a rational tangles; rational
number, parity, and algebraic equivalence of closures.

#### Rational Number

In Conways original tangle paper {cite:p}`conwayEnumerationKnotsLinks1970` he states that rational
tangles and rational numbers are in one to one correspondence, this was later proven for tangles by
Goldman and Kauffman {cite:p}`goldmanRationalTangles1997`. The correspondence comes from
interpreting the twist vector of a rational tangle as a finite continued fraction that is:
$\LB a\ b\ c\RB=c+\frac{1}{b+\frac{1}{a}}$

#### Parity

The parity of a rational tangle describes it's fixed point connectivity

````{prf:example} Parities

```{table}
:widths: auto
:align: center


| ![./media/0.svg](./media/312.svg){w=100px}   | ![./media/0.svg](./media/321.svg){w=100px} | ![./media/0.svg](./media/322.svg){w=100px}      |
|----------------------------------------|--------------------------------------|-------------------------------------------|
| ![./media/inf.svg](./media/inf.svg){w=100px} | ![./media/0.svg](./media/0.svg){w=100px}   | ![./media/0.svg](./media/parity_1.svg){w=100px} |

```
````

the connectivity, formally described by Kauffman and Lambropoulou
{cite:p}`kauffmanClassificationRationalKnots2002` as

```{prf:theorem} Kauffman, Lambropoulou
:class: theorem
A rational tangle $T$ has connectivity type $\asymp$ if and only if
its fraction has parity e/o. $T$ has connectivity type $><$ if and only if its
fraction has parity o/e. $T$ has connectivity type $\chi$ if and only if its
fraction has parity o/o. (Note that the formal fraction of $[\infty]$ itself
is $1 / 0$.) Thus the link $N(T)$ has two components if and only if $T$ has
fraction $F(T)$ of parity e/o.
```

#### Algebraic Equivalence

The algebraic equivalence class for a tangle describes the knot equivalence class of the numerator
closure of the tangle. Equivalence is give by Schubert {cite:p}`schubertKnotenMitZwei1956` as:

```{prf:theorem} Schubert
:label: thm-schubert

 Suppose that rational tangles with fractions $\frac{p}{q}$ and
 $\frac{p^{\prime}}{q^{\prime}}$ are given ( $p$ and $q$ are relatively prime
 and $0<p$. Similarly for $p^{\prime}$ and $q^{\prime}$). If
 $N\left(\frac{p}{q}\right)$ and $N\left(\frac{p^{\prime}}{q^{\prime}}\right)$
 denote the corresponding rational knots obtained by taking numerator closures
 of these tangles, then $N\left(\frac{p}{q}\right)$ and
 $N\left(\frac{p^{\prime}}{q^{\prime}}\right)$ are topologically equivalent if
 and only if
1. $p=p^{\prime}$
2. $q \equiv q^{\prime}(\bmod p)$ or $q q^{\prime} \equiv 1(\bmod p)$.
```

where $N()$ indicates the numerator closure of the object tangle.

## Bibliography

```{bibliography}
   :filter: docname in docnames
```

```{raw} latex
    \newpage
```
