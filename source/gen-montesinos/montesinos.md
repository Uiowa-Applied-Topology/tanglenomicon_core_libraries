# @@@TODO Unit Description: Montesinos Tangle Generator

```mermaid
classDiagram
    generator_mont --|> generator
    generator_mont_config_t --|> generator_config_t
    generator_mont_config_t *-- generator_mont_rat_tang_set
    generator_mont_config_t *-- note_att
    generator_mont_rat_tang_set *-- note_tv
    generator_mont *-- generator_mont_config_t

    class generator {
        <<interface>>
    }

    class generator_mont {
<<>>
}

class generator_mont_config_t {
<<struct>>
+ note_att
+ gen_mont_rat_tang_set []
}

class generator_config_t {
<<interface>>

}

class generator_mont_rat_tang_set{
+ note_tv []
+ num_rat_tangs
}

class note_att{
<<>>
}

class note_tv{
<<>>
}

```

## Language

C

## Implements

- [Generator Interface](../../docs/unit_description/generators/interface.md)

## Uses

- [Twist Vector Notation](../note-twist_vector/twist_vector.md)
- [Algebraic Tangle Tree Notation](../note-algebraic_tangle_tree/algebraic_tangle_tree.md)

## Libraries

N/A

## Functionality

A canonical description of a Montesinos Knots is given by Bonahon and Siebenmann
in Theorem 11.6 of "New Geometric Splittings of Classical Knots and the
Classiﬁcation and Symmetries of Arborescent Knots"
[${}^{[1]}$](https://dornsife.usc.edu/assets/sites/1191/docs/preprints/bonsieb.pdf).
The given construction can be modified to describe a canonical Montesinos
Tangle. That is a tangle with $n$ rational sub-tangles summed together with $+$,
with potentially $1$ integral tangle as the final sub-tangle. This means our
generation strategy for Montesinos tangles is to take combinations of our
rational tangles (non-integral), where the crossing numbers of the components
sum to the target crossing number.

```{important}
![Mont](../media/mont.svg)

Algebraically:
$$[1 2 0]+[2 1 0]+[2 2 0]$$

att:
$$+[1 2 0]+[2 1 0][2 2 0]$$


```

This module generates att of unique Montesinos tangles. A normal flows go as:

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
	state "Set prt=0" as init1
	state "Set stack[0]=0" as init2
	state "ptr++" as ptr_inc
	state "ptr--" as ptr_dec
	state "stack[ptr]++" as st_inc1
	state "stack[ptr]++" as st_inc2

	state "stack[ptr]=0" as st_zero
	state "Process Loop State" as ds
	state join_while <<join>>
  state while <<choice>>
  state for_loop_is_done <<choice>>
  state should_move_ptr <<choice>>

	[*] --> init1
	init1 --> init2
	init2 --> while
	while --> for_loop_is_done : if outer most loop not done
	while --> [*] : if outer most loop done

	for_loop_is_done --> should_move_ptr : if current inner loop not done
	for_loop_is_done --> ptr_dec : if current inner loop done


	should_move_ptr --> ptr_inc: if inner loop needs to be started
	should_move_ptr --> st_inc1: if current loop is inner most

	ptr_dec --> st_inc2
	ptr_inc --> st_zero
	st_zero --> join_while
	st_inc1 --> ds
	ds --> join_while
	st_inc2 --> join_while
join_while --> while



```

#### Process Loop State

```mermaid
stateDiagram-v2
	state "Convert notation and store" as print
	state "insert tangle into att" as itiatt
	state "for each tangle in state" as fetis{
	  [*] --> itiatt
	  itiatt -->[*]
	  }

		[*] --> fetis
		fetis --> print
		print --> [*]



	note left of fetis
	            It's assumed state is inherited from parent diagram
	end note
```

## Cite

1. F. Bonahon and L. C. Siebenmann, “New Geometric Splittings of Classical Knots
   and the Classiﬁcation and Symmetries of Arborescent Knots”. Version: January
   26, 2016
   [pdf](https://dornsife.usc.edu/assets/sites/1191/docs/preprints/bonsieb.pdf)

```{raw} latex
    \newpage
```
