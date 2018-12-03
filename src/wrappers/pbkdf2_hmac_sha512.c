#include "pbkdf2_hmac_sha512.h"
#include "mbedtls/pkcs5.h"
#include "mbedtls/md.h"

int pbkdf2_hmac_sha512(
	const utf8_char_t *password,size_t plen, 
	const utf8_char_t *salt, size_t slen,
	unsigned int iteration_count,
	uint32_t key_length, unsigned char *output)
{
	mbedtls_md_context_t mdctx;
	mbedtls_md_init(&mdctx);
	const mbedtls_md_info_t*   info=  mbedtls_md_info_from_type(MBEDTLS_MD_SHA512);
	int a=mbedtls_md_setup(&mdctx, info,1);
	if(a != 0)
	{
		return 0;
	}
	a=mbedtls_pkcs5_pbkdf2_hmac(&mdctx, 
	      password,plen,
	      salt,slen,
	      iteration_count,
	      key_length,output);
	mbedtls_md_free(&mdctx);
	return a;
}
