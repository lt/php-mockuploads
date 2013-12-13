#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "rfc1867.h"

PHP_FUNCTION(register_uploaded_file)
{
	char *path;
	int path_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &path, &path_len) == FAILURE) {
		RETURN_FALSE;
	}

	// Add path to uploaded_files hash table (fixes is_uploaded_file and move_uploaded_file)
	if (!SG(rfc1867_uploaded_files)) {
		HashTable *uploaded_files = NULL;

		// It looks like sapi_deactivate in main/SAPI.c handles the freeing of this
		ALLOC_HASHTABLE(uploaded_files);
		zend_hash_init(uploaded_files, 5, NULL, (dtor_func_t) free_estring, 0);
		SG(rfc1867_uploaded_files) = uploaded_files;
	}

	zend_hash_add(SG(rfc1867_uploaded_files), path, path_len, &path, sizeof(char *), NULL);

	RETURN_TRUE;
}

PHP_FUNCTION(unregister_uploaded_file)
{
	char *path;
	int path_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &path, &path_len) == FAILURE) {
		RETURN_FALSE;
	}

	if (SG(rfc1867_uploaded_files)) {
		if (zend_hash_del(SG(rfc1867_uploaded_files), path, path_len) == SUCCESS) {
			RETURN_TRUE;
		}
	}

	RETURN_FALSE;
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_register_uploaded_file, 0, 0, 1)
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

const zend_function_entry mockuploads_functions[] = {
	PHP_FE(register_uploaded_file, arginfo_register_uploaded_file)
	PHP_FE(unregister_uploaded_file, arginfo_register_uploaded_file)
	PHP_FE_END
};

PHP_MINFO_FUNCTION(mockuploads)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "mockuploads support", "enabled");
	php_info_print_table_end();
}

zend_module_entry mockuploads_module_entry = {
	STANDARD_MODULE_HEADER,
	"mockuploads",
	mockuploads_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	PHP_MINFO(mockuploads),
	NO_VERSION_YET,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_MOCKUPLOADS
ZEND_GET_MODULE(mockuploads)
#endif
