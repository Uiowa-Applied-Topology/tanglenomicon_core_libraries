# Unit Description: Montesinos Tangle Generator

## Class Diagram

```mermaid
classDiagram
    generator_mont --|> generator
    generator_mont_config_t --|> generator_config_t
    generator_mont_config_t *-- note_att
    generator_mont_config_t *-- note_tv
    generator_mont *-- generator_mont_config_t

    class generator {
        <<interface>>
    }

    class generator_mont {
<<>>
}

class generator_mont_config_t {
<<struct>>
note_att_t *att_n;
note_tv_t **tv_sets;
size_t *tv_set_lens;
size_t tv_sets_len;
char *str_buff;
size_t str_buff_len;
}

class generator_config_t {
<<interface>>

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

- [Generator Interface](../../generator-interface.md)

## Uses

- [Twist Vector Notation](../note-twist_vector/unit-description)
- [Algebraic Tangle Tree Notation](../note-algebraic_tangle_tree/unit-description)

## Libraries

N/A

## Functionality

### Public Structures

#### Montesinos Generator Config Structure

The config structure contains the data needed for generating a set of algebraic
tangle trees from a collection of lists of twist vectors.

This includes:

- An integer representation of the target crossing number.
- A notation structure for an algebraic tangle tree.
- A pointer to a multidimensional array of twist vectors.
- A string buffer for holding the stringified algebraic tangle tree.

### Public Functions

#### Config Function

The config function configures the local instance variable of the generator.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
  state "Init local config" as Sc

    [*] --> Sc
    Sc --> [*]

```

#### Generate Function

The generation function carries out the Montesinos tangle generation until the
inputs are exhausted. The function may contain sub machines that can be broken
out into functions in the implementation.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
    state "Init" as init1
    state "• prt=0" as init1
    state "• stack[0]=0" as init1
    state "• att node buffer to $$+$$ operation" as init1
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
    init1 --> while
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

### Private Functions

#### Process Loop State

The process loop state function handles the construction and writign of an
algebraic tangle tree in the generation process.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
    forstack:"for each element in stack except the final two"
    state forstack {
    state "Set the left twist vector child</br>of node buffer at i to twist</br>vector list i at stack[i]" as bl
    [*]-->bl
    bl-->[*]
    }
    state "Set the left twist vector child</br>of node buffer at i to twist</br>vector list i at second to</br>last stack entry" as blo
    state "Set the right twist vector child</br>of node buffer at i to twist</br>vector list i at </br>last stack entry" as bro
    state "Encode ATT" as eatt
    state "Write ATT" as wr

    [*] --> forstack
    forstack --> blo
    blo--> bro
    bro --> eatt
    eatt --> wr
    wr --> [*]
```

## Validation

### Config interface

#### Positive Tests

```{test-card} Valid Config

A valid config for the generator is passed to the function.

**Inputs:**

- A valid config.

**Expected Output:**

A positive response.

```

#### Negative Tests

```{test-card} Null Config

A null config for the generator is passed to the function.

**Inputs:**

- A null config.

**Expected Output:**

A negative response.

```

### Generate interface

```{test-card} Valid Config and generation

A valid config is set and the generation is called.

**Inputs:**

- The twist vector lists
    1. $\,$
        - [ 0 1 1 ]
        - [ 0 2 2 ]
        - [ 0 3 3 ]
    2. $\,$
        - [ 1 1 1 ]
        - [ 1 2 2 ]
    3. $\,$
        - [ 2 1 1 ]
        - [ 2 2 2 ]
        - [ 2 3 3 ]
        - [ 2 4 4 ]

**Expected Output:**

The algebraic tangle trees:
-  +[1 1 0]+[1 1 1][1 1 2]
-  +[1 1 0]+[1 1 1][2 2 2]
-  +[1 1 0]+[1 1 1][3 3 2]
-  +[1 1 0]+[1 1 1][4 4 2]
-  +[1 1 0]+[2 2 1][1 1 2]
-  +[1 1 0]+[2 2 1][2 2 2]
-  +[1 1 0]+[2 2 1][3 3 2]
-  +[1 1 0]+[2 2 1][4 4 2]
-  +[2 2 0]+[1 1 1][1 1 2]
-  +[2 2 0]+[1 1 1][2 2 2]
-  +[2 2 0]+[1 1 1][3 3 2]
-  +[2 2 0]+[1 1 1][4 4 2]
-  +[2 2 0]+[2 2 1][1 1 2]
-  +[2 2 0]+[2 2 1][2 2 2]
-  +[2 2 0]+[2 2 1][3 3 2]
-  +[2 2 0]+[2 2 1][4 4 2]
-  +[3 3 0]+[1 1 1][1 1 2]
-  +[3 3 0]+[1 1 1][2 2 2]
-  +[3 3 0]+[1 1 1][3 3 2]
-  +[3 3 0]+[1 1 1][4 4 2]
-  +[3 3 0]+[2 2 1][1 1 2]
-  +[3 3 0]+[2 2 1][2 2 2]
-  +[3 3 0]+[2 2 1][3 3 2]
-  +[3 3 0]+[2 2 1][4 4 2]

```
