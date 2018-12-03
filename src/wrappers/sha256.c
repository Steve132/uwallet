#include "sha256.h"

int w_sha256_init(w_sha256_t* ctx)
{
	mbedtls_sha256_init(ctx);
	return mbedtls_sha256_starts_ret(ctx,0);
}
int w_sha256_update(w_sha256_t* ctx,const uint8_t* data,size_t len)
{
	mbedtls_sha256_update(ctx,data,len);
	return 0;
}
int w_sha256_digest(w_sha256_t* ctx,uint8_t* out)
{
	return mbedtls_sha256_finish_ret(ctx,out);
}
int w_sha256_finish(w_sha256_t* ctx)
{
	mbedtls_sha256_free(ctx);
	return 0;
}

