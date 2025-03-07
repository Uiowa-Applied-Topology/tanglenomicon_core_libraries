# @@@TODO Use Case: Translator Interface

```mermaid
classDiagram
    translator *-- trans_config_t
    class translator {
        <<interface>>
        + trans_config_t config
        + int trans_config(trans_config_t config)
        + int trans_translate(key)
    }

    class trans_config_t {
        <<struct>>
        + int *storage_write(key, index, value)
        + string *storage_read(key, index)
    }

```

## Brief

This interface describes a generic storage module to be consumed by generation
modules. The main data type on the interfaces is a `string`. We pick string
since anything in LTS needs to be human consumable.



```{raw} latex
    \newpage
```