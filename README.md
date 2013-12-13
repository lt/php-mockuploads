php-mockuploads
===============

This extension provides the ability to register file paths as if they were uploaded via an HTTP request, for the purpose of unit testing code that is otherwise untestable.

The funtions `is_uploaded_file` and `move_uploaded_file` reference an internal hash table, and cannot be influenced by changing the `$_FILES` superglobal.

The extension adds two new functions to register and unregister file paths in the internal hash table.

How to build:
-------------

```
cd php-mockuploads
phpize
./configure
make
```

Then add an `extension=/path/to/php-mockuploads.so` to your php.ini

How to use:
-----------

```
$myFilePath = '/path/to/test/file.abc';

$_FILES['myFormField'] = [
	'name' => 'file.abc',
	'type' => 'application/abc',
	'error' => UPLOAD_ERR_OK,
	'size' => filesize($myFilePath),
	'tmp_name' => $myFilePath
];

register_uploaded_file($myFilePath);

// Run tests

unregister_uploaded_file($myFilePath);
unset($_FILES['myFormField']);
```

TODO:
-----

* Check if path actually exists (maybe)
* Lock file when registered as an upload (PHP does this until you move the uploaded file)
