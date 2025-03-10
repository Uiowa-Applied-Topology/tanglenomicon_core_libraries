# Use Case: Rational Tangle Generator

```mermaid
classDiagram
    generator_rational --|> generator
    gen_rational_config_t --|> gen_config_t
    gen_rational_config_t *-- notation_tv
    generator_rational *-- gen_rational_config_t

    class generator {
        <<interface>>
    }

    class generator_rational {
<<>>
}

class gen_rational_config_t {
<<struct>>
+ notation_tv
}

class gen_config_t {
<<interface>>

}

class notation_tv{
<<>>
}

```

## Language

C

## Implements

- [Generator Interface](interface.md)

## Uses

- [Notation Twist Vector](../notations/twist_vector.md)

## Libraries

N/A

## Functionality

A rational tangle is given by alternating NE,SE and SE,SW twisting of the $0$
tangle[${}^{[2]}$](https://doi.org/10.48550/arXiv.math/0212011)[${}^{[1]}$](https://doi.org/10.1016/B978-0-08-012975-4.50034-5).
A canonical combinatorial description of a rational tangle can be given by the
[Twist Vector](../notations/twist%20vector.md).

This module generates twist vectors and in doing so rational tangles. A normal
flows go as:

### Config

```mermaid
stateDiagram-v2
  state "Init local config" as Sc

	[*] --> Sc
	Sc --> [*]

```

### Generate

```mermaid
stateDiagram-v2
  state "Get Combination of CN" as gen
  state join_state <<fork>>
  state is_even <<choice>>
  state no_combinations <<choice>>
  state "Print" as print {
  state "Set TV values" as stv
  state "Set CN value" as scv
	[*] --> stv
	stv --> scv
	scv --> [*]
  }

  state "Oddify Even combination" as even {
  state "shift array left"  as shiftL
  state "shift array right" as shiftR
  state "prepend 0" as pp0
	[*] --> shiftR
	shiftR --> pp0
	pp0 --> print
	print --> shiftL
	shiftL --> join_state


  }

	[*] --> gen
	gen --> no_combinations
  no_combinations --> is_even: if is not final combination
	no_combinations --> [*] : if is final combination

  is_even --> even: if tv.length % 2 == 0
	is_even --> print : if tv.length % 2 == 1
	print --> join_state
	join_state --> gen


```

## Cite

1. Conway, J.H. “An Enumeration of Knots and Links, and Some of Their Algebraic
   Properties.” In _Computational Problems in Abstract Algebra_, 329–58.
   Elsevier, 1970.
   [https://doi.org/10.1016/B978-0-08-012975-4.50034-5](https://doi.org/10.1016/b978-0-08-012975-4.50034-5).
2. Kauffman, Louis H., and Sofia Lambropoulou. “On the Classification of
   Rational Knots,” 2002.
   [https://doi.org/10.48550/ARXIV.MATH/0212011](https://doi.org/10.48550/arxiv.math/0212011).

```{raw} latex
    \newpage
```
