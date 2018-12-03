#ifndef W_SHA256_H
#define W_SHA256_H

#include "mbedtls/sha256.h"
#include<stdint.h>

typedef mbedtls_sha256_context w_sha256_t;

int w_sha256_init(w_sha256_t* ctx);
int w_sha256_update(w_sha256_t* ctx,const uint8_t* data,size_t len);
int w_sha256_digest(w_sha256_t* ctx,uint8_t* out);
int w_sha256_finish(w_sha256_t* ctx);

#endif
