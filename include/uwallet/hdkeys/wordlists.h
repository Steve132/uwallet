
#ifndef WORDLISTS_H
#define WORDLISTS_H

#include "wordlists-config.h"

#define WL_MAX_WORD_LENGTH -1
#define WL_CONSTANT(x) const x
#define WL_CONSTANT_PTR(x) const x*

typedef WL_CONSTANT_PTR(uint8_t) wl_data_ptr_t;

#ifdef WL_ENABLE_chinese_simplified
	extern WL_CONSTANT(uint8_t) wordlist_chinese_simplified_data[8192];
	//Will cause a link error if it's not available in this build.

#if WL_MAX_WORD_LENGTH < 3
#undef WL_MAX_WORD_LENGTH
#define WL_MAX_WORD_LENGTH 3
#endif

#endif

#ifdef WL_ENABLE_french
	extern WL_CONSTANT(uint8_t) wordlist_french_data[16777];
	//Will cause a link error if it's not available in this build.

#if WL_MAX_WORD_LENGTH < 12
#undef WL_MAX_WORD_LENGTH
#define WL_MAX_WORD_LENGTH 12
#endif

#endif

#ifdef WL_ENABLE_spanish
	extern WL_CONSTANT(uint8_t) wordlist_spanish_data[13996];
	//Will cause a link error if it's not available in this build.

#if WL_MAX_WORD_LENGTH < 10
#undef WL_MAX_WORD_LENGTH
#define WL_MAX_WORD_LENGTH 10
#endif

#endif

#ifdef WL_ENABLE_english
	extern WL_CONSTANT(uint8_t) wordlist_english_data[13116];
	//Will cause a link error if it's not available in this build.

#if WL_MAX_WORD_LENGTH < 8
#undef WL_MAX_WORD_LENGTH
#define WL_MAX_WORD_LENGTH 8
#endif

#endif

#ifdef WL_ENABLE_italian
	extern WL_CONSTANT(uint8_t) wordlist_italian_data[16033];
	//Will cause a link error if it's not available in this build.

#if WL_MAX_WORD_LENGTH < 9
#undef WL_MAX_WORD_LENGTH
#define WL_MAX_WORD_LENGTH 9
#endif

#endif

#ifdef WL_ENABLE_korean
	extern WL_CONSTANT(uint8_t) wordlist_korean_data[37832];
	//Will cause a link error if it's not available in this build.

#if WL_MAX_WORD_LENGTH < 33
#undef WL_MAX_WORD_LENGTH
#define WL_MAX_WORD_LENGTH 33
#endif

#endif

#ifdef WL_ENABLE_chinese_traditional
	extern WL_CONSTANT(uint8_t) wordlist_chinese_traditional_data[8192];
	//Will cause a link error if it's not available in this build.

#if WL_MAX_WORD_LENGTH < 3
#undef WL_MAX_WORD_LENGTH
#define WL_MAX_WORD_LENGTH 3
#endif

#endif

#ifdef WL_ENABLE_japanese
	extern WL_CONSTANT(uint8_t) wordlist_japanese_data[26423];
	//Will cause a link error if it's not available in this build.

#if WL_MAX_WORD_LENGTH < 27
#undef WL_MAX_WORD_LENGTH
#define WL_MAX_WORD_LENGTH 27
#endif

#endif
#endif
