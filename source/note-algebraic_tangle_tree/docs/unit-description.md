# Unit Description

## Class Diagram

```mermaid
classDiagram
    note_att --|> notation
    note_att *-- note_att_t
    note_att_t *-- note_att_node_t
    note_att_node_t *-- note_att_operation_enum
    note_att_node_t *-- note_tv_t

    class note_att_t {
        <<struct>>
        note_att_node_t* root
        note_att_node_t *node_buffer;
        size_t node_buffer_len;
        note_tv_t *tv_buffer;
        size_t tv_buffer_len;
    }

    class note_att_operation_enum {
        <<enum>>
        Plus
        Vee
    }

    class note_att_node_t {
        <<struct>>
        note_att_node_t* left_child
        note_att_node_t* right_child
        note_tv_t *right_tv
        note_tv_t *left_tv
        note_att_node_enum operation
    }

    class notation {
        <<interface>>
    }

    class note_tv_t {
        <<struct>>
    }

```

## Language

C

## Implements

- [Notations Interface][interface-notation]

## Uses

- [Twist Vector Interface][note-twist_vector]

## External Libraries

The algebraic tangle tree notation component does not use any external libraries.

## Functionality

### Public Structures

#### Notation Structure

The interface notation structure contains the data needed to store the data structure for an
algebraic tangle tree. The notation structure contains a pointer to the root node of an algebraic
tangle tree. Additionally, the notation interface contains two buffers for storing elements of the
tree. The first buffer is a node buffer for storing non-leaf nodes of a tree. The second is a twist
vector buffer for storing leaf nodes of the tree.

#### Node Structure

The second structure is the node structure. This structure defines the data needed by a non-leaf
node of an algebraic tangle tree. An algebraic tangle tree is a binary tree, for any node the
children of that node can be of two types. We store these possibilities with two sets of pointers.
First, pointers for left and right child nodes and second, pointers for left and right twist vector
leaf nodes. Additionally, each node must contain an operation, either $+$ or $\vee$. This operation
data is stored as a bit field.

| Operation | NA  | NA  | NA  | NA  | NA  | NA  | Op  | Op  |
| --------- | --- | --- | --- | --- | --- | --- | --- | --- |
| uninit    | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
| Plus      | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 1   |
| Vee       | 0   | 0   | 0   | 0   | 0   | 0   | 1   | 0   |

### Public Functions

#### Decode Function

The decode function takes in the linearized string form of the algebraic tangle tree and encodes it
as a `note_att_t`.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
    state "Init" as vj
    state "• root as empty node" as vj
    state "• str_idx as 0" as vj
    state "• tv_idx as 0" as vj
    state "Set root operation to +" as sop
    state "Set root operation to v" as sov
    state "Traverse string" as rc
    state if_pv <<choice>>
    [*] --> vj
    vj --> if_pv
    if_pv --> sop: Operation is a +
    if_pv --> sov: Operation is a v
    sop --> rc
    sov --> rc
    rc --> [*]

```

#### Encode Function

The encode function takes in a `note_tv_t` and encodes it into the linearized string form of the
algebraic tangle tree.

```mermaid
stateDiagram-v2
    state "Traverse Tree" as rc
    [*] --> rc
    rc --> [*]
```

### Private Functions Decode Path

#### Traverse String

This function recursively processes a string into the non-root elements of an algebraic tangle tree.

```mermaid
stateDiagram-v2
    state "Init" as rn
    state "• node left pointers to NULL" as rn
    state "• node right pointers to NULL" as rn
    state "• Count of new nodes to 0" as rn
    state "Get initial operation" as gio
    state "Set operation" as so
    state "Set operation to +" as sopl
    state "Set operation to v" as sovl
    state "Set operation to +" as sopr
    state "Set operation to v" as sovr
    state "Execute this state machine</br>with Left node as active</br>node" as lan
    state "Execute this state machine</br>with Right node as active</br>node" as ran
    state "Process Twist Vector</br>into Left child" as ptvl
    state "Process Twist Vector</br>into Right child" as ptvr
    state if_obl <<choice>>
    state if_obr <<choice>>
    state if_pl <<choice>>
    state if_pr <<choice>>
    state if_vl <<choice>>
    state if_vr <<choice>>
    [*] --> rn
    rn --> gio
    gio --> so
    so --> if_obl
    if_obl --> if_pl: Current char is not [
    if_pl --> if_vl: Current char is not +
    if_obl --> ptvl: Current char is [
    if_pl --> sopl
    if_vl --> sovl
    sopl --> lan
    sovl --> lan
    ptvl --> if_obr
    lan --> if_obr
    if_obr --> if_pr: Current char is not [
    if_pr --> if_vr: Current char is not +
    if_obr --> ptvr: Current char is [
    if_pr --> sopr
    if_vr --> sovr
    sopr --> ran
    sovr --> ran
    ran --> [*]
    ptvr --> [*]

```

### Private Functions Encode Path

#### Traverse Tree

This function recursively processes a string into the non-root elements of an algebraic tangle tree.

```mermaid
stateDiagram-v2
    state "Init" as rn
    state "• node left pointers to NULL" as rn
    state "• node right pointers to NULL" as rn
    state "• Count of new nodes to 0" as rn
    state "Move string forward" as msf
    state "Jump string forward" as jsf
    state "Add + to string" as mps
    state "Add v to string" as mvs
    state "Execute this state machine</br>with Left node as active</br>node" as lan
    state "Execute this state machine</br>with Right node as active</br>node" as ran
    state "Add twist vector to string" as tvsl
    state "Add twist vector to string" as tvsr
    state if_op <<choice>>
    state if_nnnl <<choice>>
    state if_nnnr <<choice>>
    [*] --> rn
    rn --> if_op
    if_op --> mps: If node operation is +
    if_op --> mvs: If node operation is v
    mps --> msf
    mvs --> msf
    msf --> if_nnnl
    if_nnnl --> lan
    if_nnnl --> tvsl
    lan --> jsf
    tvsl --> jsf
    jsf --> if_nnnr
    if_nnnr --> ran
    if_nnnr --> tvsr
    ran --> [*]
    tvsr --> [*]
```

## Validation

### Decode Interface

<!-- prettier-ignore-start -->

!!! test-card "Valid string representing a algebraic tangle tree"

    A valid string representing a algebraic tangle tree is fed to the function.

    **Inputs:**

    - A valid string representing a algebraic tangle tree.

    **Expected Output:**

    A correct and valid decoding of the string

<!-- prettier-ignore-end -->

### Encode Interface

<!-- prettier-ignore-start -->

!!! test-card "Valid algebraic tangle tree"

    A valid algebraic tangle tree is fed to the function.

    **Inputs:**

    - A correct and valid algebraic tangle tree.

    **Expected Output:**

    A valid string representing the algebraic tangle tree.

<!-- prettier-ignore-end -->
