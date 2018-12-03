#ifndef UWALLET_BASE_H
#define UWALLET_BASE_H

#include<stdint.h>
#include<stdlib.h>

#ifdef CONFIG_UWALLET_SUPPORT_UNICODE
typedef char16_t utf_char_t;
#else
typedef char utf_char_t;
#endif

typedef char utf8_char_t;

typedef union uwallet_bits256_ts
{
	uint8_t data[32];
 
} uwallet_bits256_t;


typedef void (*uwallet_progress_func_ptr)(const utf8_char_t* what,unsigned int current_items,unsigned int total_items,void* userdata);
void uwallet_null_progress(const utf8_char_t* what,unsigned int current_items,unsigned int total_items,void* userdata);

void dword_cpy(void* dst,const void* src,unsigned int num_dwords);

#endif
