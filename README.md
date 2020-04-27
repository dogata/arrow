# arrow
Stores sample code for Apache Arrow. This framework requires a server to run in the background in order to facilitate the object serialization between different languages.

These codes follow tutorials on Apache Arrow focusing on C++ and Python interface.

To install Arrow:
- https://arrow.apache.org/install/

Initialize plasma server:
Example: initializes a Plasma store up to 1 GB of memory and sets the socket to /tmp/plasma.
```
plasma-store-server -m 1000000000 -s /tmp/plasma
```

C++ tutorial:
- https://github.com/apache/arrow/blob/master/cpp/apidoc/tutorials/plasma.md
C++ and Python interface tutorial:
- https://github.com/apache/arrow/blob/master/cpp/apidoc/tutorials/tensor_to_py.md