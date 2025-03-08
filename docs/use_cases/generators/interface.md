# Use Case: Generator Interface

```mermaid
classDiagram
    generator *-- gen_config_t
    class generator {
        <<interface>>
        + gen_config_t config
        + int gen_config(gen_config_t config)
        + int gen_generate()
    }

    class gen_config_t {
        <<struct>>
        + int maxCrossingNumber
        + int storage_write(key, index, value)
        + const char * storage_read(key, index)
    }


```

## Brief

This interface describes a generic generator module. A generator module is a
runnable that generates objects of a specific class up to a crossing number.

```{raw} latex
    \newpage
```
