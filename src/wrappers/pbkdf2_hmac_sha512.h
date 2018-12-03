#ifndef W_PBKDF2_HMAC_SHA512_H
#define W_PBKDF2_HMAC_SHA512_H

#include<stdint.h>
#include<uwallet/base.h>

int pbkdf2_hmac_sha512(
	const utf8_char_t *password,size_t plen, 
	const utf8_char_t *salt, size_t slen,
	unsigned int iteration_count,
	uint32_t key_length, unsigned char *output );

#endif
