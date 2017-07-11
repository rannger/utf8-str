#include "utf8_str.h"
#include <stdlib.h>
#include <strings.h>
#include <assert.h>

int char_len(unsigned char ch)
{
		int ret = 1;
		if (ch>>5 == 0x6) ret = 2;
		if (ch>>4 == 0xe) ret = 3;
		if (ch>>3 == 0x1e) ret = 4;

		return ret;
}

utf8_char* alloc_char(int size)
{
		utf8_char* ret = (utf8_char*)malloc(sizeof(utf8_char)+sizeof(unsigned char)*size);
		bzero(ret,sizeof(utf8_char)+sizeof(unsigned char)*size);
		ret->len = size;
		return ret;
}

void utf8_char_free(utf8_char* ch)
{
		free(ch);
}

utf8_char** rd_utf8_str(unsigned char* buf,int size)
{
	int32_t index = 0;
	int32_t item_size = 0;
	int32_t item_index = 0;
	utf8_char** utf8_str = NULL;
	do {
		int len = char_len(buf[index]);
		index += len;
		++item_size;
		if (index-1==size) 
				break;
	}while(1);

	utf8_str = (utf8_char**)malloc(sizeof(utf8_char*) * (item_size+1));
	index = 0;
	do {
		int len = char_len(buf[index]);
		utf8_char* ch = alloc_char(len);
		strncpy((char*)&(ch->data[0]),(const char*)buf+index,ch->len);
		utf8_str[item_index++] = ch;
		index += len;
		if (index-1==size) 
				break;
	} while(1);
	
	utf8_str[item_size] = NULL;

	return utf8_str;
}

void release_utf8_str(utf8_char** utf8_str)
{
		for(int index=0;NULL!=utf8_str[index];++index) {
				free(utf8_str[index]);
		}
		free(utf8_str);
}

