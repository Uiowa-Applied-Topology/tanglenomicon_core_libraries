# Unit Description

## Class Diagram

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
uint8_t crossingNumber;
note_tv_t *tv_n;
char *tv_str_buff;
size_t tv_str_buff_len;
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

- [Generator Interface][interface-generator]

## Uses

- [Notation Twist Vector][note-twist_vector]

## Libraries

N/A

## Functionality

### Public Structures

#### Rational Generator Configuration Structure

The configuration structure contains the data needed for generating twist vectors up to a given
crossing number. This includes:

- An integer representation of the target crossing number.
- A notation structure for a twist vector.
- A string buffer for holding the stringified twist vector.

### Public Functions

#### Configuration Function

The configuration function sets the local configuration variable of the generator.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
    state "Init local configuration" as Sc
    [*] --> Sc
    Sc --> [*]

```

#### Generate Function

The generation function carries out the rational tangle generation until the target crossing number
is met. The function may contain sub-machines that can be broken out into functions in the
implementation.

This process is described in the following state machines:

```mermaid
stateDiagram-v2
    state if_done <<choice>>
    state "Init " as State_i
    state "• i as 0 " as State_i
state State_ipp: i++
state "Construct TV from i as a bitfield" as tv_calc{
state "Init" as State_temp
state "• temp as i" as State_temp
state "• j as 0" as State_temp
state "• count as N" as State_temp
State_jpp: j++
State_cntmm: count--
State_sum_tv: TV[j]++
State_rsh: right shift temp by 1
state if_lsb <<choice>>
state if_cnteo <<choice>>
State_store_tv: Store TV

[*] --> State_temp
State_temp --> if_cnteo
if_cnteo --> State_cntmm: if cnt>0
if_cnteo --> State_store_tv: if cnt==0
State_store_tv --> [*]

State_cntmm -->if_lsb
if_lsb --> State_sum_tv: if (tmplt & 0x01u)==1u
State_sum_tv --> State_rsh
if_lsb --> State_jpp: if (tmplt & 0x01u)==0u
State_jpp --> State_rsh
State_rsh --> if_cnteo
}
[*] --> State_i
State_i --> if_done
if_done --> tv_calc: if i < 2**(N-1)
tv_calc --> State_ipp
State_ipp --> if_done
if_done --> [*]: if i == 2**(N-1)

```

## Validation

### Configuration Interface

#### Positive Tests

<!-- prettier-ignore-start -->

!!! test-card "Valid Configuration"

    A valid configuration for the generator is passed to the function.

    **Inputs:**

    - A valid configuration.

    **Expected Output:**

    A positive response.

<!-- prettier-ignore-end -->

#### Negative Tests

<!-- prettier-ignore-start -->

!!! test-card "Null Configuration"

    A null configuration for the generator is passed to the function.

    **Inputs:**

    - A null configuration.

    **Expected Output:**

    A negative response.

<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->

!!! test-card "A Configuration with null twist vector"

    A configuration with a null twist vector is passed to the function.

    **Inputs:**

    - A configuration with a null twist vector.

    **Expected Output:**

    A negative response.

<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->

!!! test-card "A Configuration with null string buffer"

    A configuration with a null string buffer is passed to the function.

    **Inputs:**

    - A configuration with a null string buffer.

    **Expected Output:**

    A negative response.

<!-- prettier-ignore-end -->

### Generate Interface

<!-- prettier-ignore-start -->

!!! test-card "Valid Configuration and generation"

    A valid configuration is set and the generation is called.

    **Inputs:**

    - A target crossing number of 5

    **Expected Output:**

    The twist vectors:

    - `[1 1 1 1 1]`
    - `[2 1 1 1 0]`
    - `[1 2 1 1 0]`
    - `[1 1 2 1 0]`
    - `[1 1 1 2 0]`
    - `[3 1 1]`
    - `[1 3 1]`
    - `[1 1 3]`
    - `[2 2 1]`
    - `[2 1 2]`
    - `[1 2 2]`
    - `[3 2 0]`
    - `[2 3 0]`
    - `[4 1 0]`
    - `[1 4 0]`
    - `[5]`

<!-- prettier-ignore-end -->
