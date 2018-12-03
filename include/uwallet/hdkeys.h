#ifndef UWALLET_HDKEYS_H
#define UWALLET_HDKEYS_H

#include "base.h"
#include "hdkeys/wordlists.h"


/*
############################MNEMONIC API
*/

#define UWALLET_MNEMONIC_SEED_MAX_WORD_BYTES WL_MAX_WORD_LENGTH
typedef wl_data_ptr_t uwallet_wordlist_t;

#define UWALLET_MNEMONIC_MAX_NUM_ENTROPY_DWORDS 8
#define UWALLET_MNEMONIC_MAX_NUM_MNEMONIC_WORDS (UWALLET_MNEMONIC_MAX_NUM_ENTROPY_DWORDS*3)
//Store this encrypted if you need to be able to export the mnemonic to the user.
typedef struct uwallet_mnemonic_entropy_ts
{
	uint8_t data[UWALLET_MNEMONIC_MAX_NUM_ENTROPY_DWORDS*4];
	uint8_t num_entropy_dwords;

} uwallet_mnemonic_entropy_t;

//store this encrypted if you need to use the wallet quickly (think of this like a cache to the root)
typedef struct uwallet_mnemonic_seed_ts
{
	uint8_t data[64];
} uwallet_mnemonic_seed_t;

int uwallet_parse_mnemonic(
	uwallet_mnemonic_entropy_t* ment_out,
	uwallet_wordlist_t wl,
	const utf8_char_t* mnemonic_string_data,size_t mslen);

int uwallet_mnemonic_to_seed(
	uwallet_mnemonic_seed_t* seed_out,
	uwallet_wordlist_t wl,
	const uwallet_mnemonic_entropy_t*,
	const utf8_char_t* passphrase,size_t pplen,		//Can be null
	uwallet_progress_func_ptr progress);

int uwallet_get_word_in_mnemonic(utf8_char_t* wordout,size_t* outlen,
	uwallet_wordlist_t wl,
	const uwallet_mnemonic_entropy_t*,
	unsigned int index);

/*
#########################XKEY API
*/

typedef union uwallet_hdpath_item_ts
{
	struct
	{
		unsigned hardened:1;
		unsigned value:31;
	};
	uint32_t dword; 
} uwallet_hdpath_item_t;

uint32_t uwallet_h(uint32_t dw);

#define UWALLET_HDPATH_MAX_PATH_LENGTH 8
typedef struct uwallet_hdpath_ts
{
	uwallet_hdpath_item_t items[UWALLET_HDPATH_MAX_PATH_LENGTH];
	uint8_t num_items;
} uwallet_hdpath_t;

typedef struct uwallet_hdpath_type_ts
{
	uint32_t hdprefix;
	uint32_t flags;

} uwallet_hdpath_type_t;

typedef struct uwallet_hdkey_ts
{
	uwallet_hdpath_type_t typ;
	uwallet_hdpath_t path;
	uint8_t chain_code[32];
	uint8_t keydata[33]; 	//YES, this is supposed to be 33
} uwallet_hdkey_t;

int uwallet_hdkey_descend(uwallet_hdkey_t* xkey,uwallet_hdpath_item_t itm);
int uwallet_hdkey_extract_key(uwallet_bits256_t* key_out,const uwallet_hdkey_t* xkey);

#endif
