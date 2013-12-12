PHP_ARG_ENABLE(mockuploads, Whether to enable the "mockuploads" extension,
	[  --enable-mockuploads      Enable "php-mockuploads" extension support])

if test $PHP_MOCKUPLOADS != "no"; then
	PHP_NEW_EXTENSION(mockuploads, mockuploads.c, $ext_shared)
fi
