import json
import unicodedata
import binascii
import os
import sys
from collections import Counter
import argparse

wordlists={}
def load_wordlist(wlfname):
	global wordlists
	wlname,ext=os.path.splitext(os.path.basename(wlfname))
	wlfile=open(wlfname,'r')
	wordlists[wlname]=[x.strip() for x in iter(wlfile)]
	
def do_wordlist(wlname):
	wl=wordlists[wlname];
	
	all_dataelems=[]
	for w in wl:
		nw=unicodedata.normalize('NFKD',w)
		data=nw.encode('utf-8')
		all_dataelems.append(data)

	max_width=max([len(d) for d in all_dataelems])
	ba=bytearray()
	baa=bytearray()
	for d in all_dataelems:
		ba+=bytearray([len(d)])
		ba+=d
		baa+=d
	
	cc=Counter(baa)	#todo: huffman or entropy decode the bytes?
	#print((wlname,len(cc)))
	return ba,max_width

def chunks(l, n):
    """Yield successive n-sized chunks from l."""
    for i in range(0, len(l), n):
        yield l[i:i + n]


def c_impl(wlfilename,wldi):
	cou=open(wlfilename,'w')
	cou.write(
"""
#include<stdint.h>
#include <uwallet/hdkeys.h>

#define WL_INTERNAL_BYTECOUNT 0

""")
	
	for wlname,ba,maxwidth in wldi:
		cou.write("""
#ifdef WL_ENABLE_%s
WL_CONSTANT(uint8_t) wordlist_%s_data[%d]={
""" % (wlname,wlname,len(ba))
		)
		chunkstrs=[]
		for row in chunks(ba,12):
			chunkstrs.append(','.join(['0x%02X' % (b) for b in row]))
		cou.write(',\n'.join(chunkstrs))
		cou.write("""
};

#endif
""")


	
	

def h_impl(wlhfilename,wldi):
	hout="""
#ifndef WORDLISTS_H
#define WORDLISTS_H

#include "wordlists-config.h"

#define WL_MAX_WORD_LENGTH -1
#define WL_CONSTANT(x) const x
#define WL_CONSTANT_PTR(x) const x*

typedef WL_CONSTANT_PTR(uint8_t) wl_data_ptr_t;
"""
	for wlname,ba,maxwidth in wldi:
		hstr="""
#ifdef WL_ENABLE_%s
	extern WL_CONSTANT(uint8_t) wordlist_%s_data[%d];
	//Will cause a link error if it's not available in this build.

#if WL_MAX_WORD_LENGTH < %d
#undef WL_MAX_WORD_LENGTH
#define WL_MAX_WORD_LENGTH %d
#endif

#endif
""" % (wlname,wlname,len(ba),maxwidth,maxwidth)
		hout+=hstr
	
	hout+="#endif\n"
	wlhf=open(wlhfilename,'w')
	wlhf.write(hout)
	
def hc_impl(wlhfilename,wldi):
	hout="""

#ifndef WORDLISTS_CONFIG_H
#define WORDLISTS_CONFIG_H

"""
	for wlname,ba,maxwidth in wldi:
		hstr="""#define WL_ENABLE_%s\n""" % (wlname)
		hout+=hstr
	
	hout+="#endif\n"
	wlhf=open(wlhfilename,'w')
	wlhf.write(hout)



if __name__=='__main__':

	parser=argparse.ArgumentParser()
	parser.add_argument("wordlistfiles",nargs='+',type=str)
	parser.add_argument("--output_src_dir","-os",type=str,default='.')
	parser.add_argument("--output_inc_dir","-oi",type=str,default=None)
	parser.add_argument("--add_config",action="store_true",default=False)
	args=parser.parse_args()
	for wlf in args.wordlistfiles:
		load_wordlist(wlf)

	if(args.output_inc_dir is None):
		args.output_inc_dir=args.output_src_dir

	wldi=[]
	total_size=0
	for wlname,wl in wordlists.items():
		#print(wlname)
		ba,max_width=do_wordlist(wlname)
		wldi.append((wlname,ba,max_width))
		total_size+=len(ba)

	c_impl(os.path.join(args.output_src_dir,'wordlists.c'),wldi)
	h_impl(os.path.join(args.output_inc_dir,'wordlists.h'),wldi)
	if(args.add_config):
		hc_impl(os.path.join(args.output_inc_dir,'wordlists-config.h'),wldi)
	print("Total size: %d bytes" % (total_size))
