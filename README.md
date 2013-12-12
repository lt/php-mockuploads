php-mockuploads
===============

This extension provides the ability to register file paths as if they were uploaded via an HTTP request, for the purpose of unit testing code that is otherwise untestable.

The funtions `is_uploaded_file` and `move_uploaded_file` reference an internal hash table, and cannot be influenced by changing the `$_FILES` superglobal.

The extension exposes a single new function that injects a path into the internal hash table, and also adds an entry to the `$_FILES` array.

The function is: `register_uploaded_file($path)`
