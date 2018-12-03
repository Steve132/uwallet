#include "wrappers/sha256.h"
#include<uwallet/base.h>
#include<uwallet/hdkeys.h>

static uint8_t compute_cs_byte(const uwallet_mnemonic_entropy_t* ent)
{
	w_sha256_t hobj;
	w_sha256_init(&hobj);

	w_sha256_update(&hobj,ent->data,ent->num_entropy_dwords*4);
	uwallet_bits256_t out;
	w_sha256_digest(&hobj,out.data);
	w_sha256_finish(&hobj);

	return out.data[0];
}

static unsigned int extract_all_entropy_items(uint16_t* eitems,const uwallet_mnemonic_entropy_t* ent,uint8_t csbyte)
{
	uint8_t newdata[UWALLET_MNEMONIC_MAX_NUM_ENTROPY_DWORDS*4+2];
	unsigned int num_dwords=ent->num_entropy_dwords;
	dword_cpy(newdata,ent->data,num_dwords);
	
	newdata[num_dwords*4]=csbyte;
	newdata[num_dwords*4+1]=csbyte;
	
	unsigned int num_mnemonic_words=(ent->num_entropy_dwords & (UWALLET_MNEMONIC_MAX_NUM_ENTROPY_DWORDS-1)) * 3;
	const uint8_t* edat=ent->data;
	for(unsigned int index=0;index < num_mnemonic_words;index++)
	{
		unsigned int boffset=index*11;
		unsigned int byoffset=boffset/8;	
		uint32_t b2=edat[byoffset]+(edat[byoffset+1]<<8)+(edat[byoffset+2] << 16);
		b2 >>= boffset % 8;
		b2 &=0x7FF;
		eitems[index]=b2;
	}
	return num_mnemonic_words;
}
static int find_offset_of_index(uwallet_wordlist_t wl,unsigned int target_index)
{
	target_index &= 0x7FF;
	int offset=0;
	int found=-1;
	for(unsigned int i=0;i<2048;i++)		//this is structured this weird way for timing attacks.
	{
		unsigned int wlen=(unsigned int)wl[offset];
		if(i==target_index)
		{
			found=offset;
		}
		offset+=wlen+1;
	}
	return found;
}

static unsigned int get_wl_offsets(uint32_t* offsets,uwallet_wordlist_t wl,const uwallet_mnemonic_entropy_t* ent)
{
	uint16_t eitems[UWALLET_MNEMONIC_MAX_NUM_MNEMONIC_WORDS];
	uint8_t csbyte=compute_cs_byte(ent);
	
	unsigned int num_mnemonic_words=extract_all_entropy_items(eitems,ent,csbyte);
	for(unsigned int i=0;i<num_mnemonic_words;i++)
	{
		uint32_t dex=eitems[i];
		offsets[i]=find_offset_of_index(wl,dex);
	}
	return num_mnemonic_words;
}

int uwallet_seed_from_mnemonic(
	uwallet_mnemonic_seed_t* seed_out,
	uwallet_wordlist_t wl,
	const uwallet_mnemonic_entropy_t* ent,
	const utf_char_t* passphrase,size_t pplen,		//Can be null
	uwallet_progress_func_ptr progress)
{
	uint32_t offsets[UWALLET_MNEMONIC_MAX_NUM_MNEMONIC_WORDS];
	uint32_t num_mnemonic_words=get_wl_offsets(offsets,wl,ent);
	
	
}
