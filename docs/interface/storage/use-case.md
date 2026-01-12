# Use Case

The storage interface defines the general form for a component that reads and writes key value
pairs. These functions are generally defined by the user interface layer and passed to components as
function pointers. Data is assumed to be formatted in a key value store with two layers. The
outermost layer is indexed by a value called a **key**. The value for the key is another collection
of key value pairs. At this level, the key value is called an **index** and the value entry is
called a **value**.

````{prf:example}
```json
{
    "key": {
        "index": "value"
    },
    "[1 1 1]": {
        "crossing_number": "3",
        "is_rational": "true"
    }
}
```
A JSON data store with the key:index:value structure.
````
