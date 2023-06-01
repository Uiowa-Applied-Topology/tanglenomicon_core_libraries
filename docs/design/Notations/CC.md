```mermaid
classDiagram

note_cc --|> notation
note_cc --|> note_cc_t
note_cc_t --|> note_vertex_t
note_vertex_t --|> note_vertex_e


class notation{
<<interface>>
}

class note_cc_t {
int graphtype
List~note_alg_Tree_t~ forest
}

class note_vertex_t{
note_vertex_e vertex_type
string leaf
int integral_leaf
note_vertex_t* leaf
note_vertex_t* left_child;
note_vertex_t* right_child;
}

class note_vertex_e{
<<Enumeration>>
NOTE_cc_HOR_SUM
NOTE_cc_MARKED
NOTE_cc_VERT_SUM
NOTE_cc_LEAF_INTEGRAL
NOTE_cc_LEAF_STRING
NOTE_cc_LEAF_cc
}

```


## Description 

This defines notation object for the combined "Caudron-Conway" notation. The top level is the Conway notation for polyhedral knots. Each element of the conway polyhedra is an algebraic knot defined as Caudron's binary operation tree, with operations $+$ horizontal sum and $\vee$ vertical sum. 

## Language

C

## Implements

* [Interface](Notations/Interface.md)

## Used by

* [Rational](Generators/Rational.md)
* [Pd-To-cc](Translators/Pd-To-cc.md)

## Cautions

We need to be very careful about not having a memory leaks.

## Design Description 

### note_cc_t
- [ ] TODO note_cc_t
### note_vertex_t
- [ ] TODO note_vertex_t
### note_vertex_e
- [ ] TODO note_vertex_e