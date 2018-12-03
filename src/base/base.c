#include<uwallet/base.h>

void uwallet_null_progress(const utf_char_t* what,unsigned int current_items,unsigned int total_items,void* userdata)
{

}

void dword_cpy(void* dst,const void* src,unsigned int num_dwords)
{
	uint32_t* ddst=dst;
	const uint32_t* dsrc=src;
	for(unsigned int i=0;i<num_dwords;i++)
	{
		ddst[i]=dsrc[i];
	}
}
