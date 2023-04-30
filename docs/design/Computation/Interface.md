

```mermaid
classDiagram
computation *-- comp_config_t
class computation{
<<interface>>
+ comp_config_t config
+ int comp_onfig(comp_config_t config)
+ int comp_compute(key)
}

class comp_config_t {
<<struct>>
+ int *storage_write(key,index,value)
+ string *storage_read(key,index)
}


```

## Brief

This interface describes a generic computation module. A computation module is a runnable that computes an value for an object/s.

- [ ] Probably need a common interface for gathering objects