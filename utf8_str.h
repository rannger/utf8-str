#ifndef __UTF8_STR_H
#define __UTF8_STR_H

#include <stdint.h>

typedef struct utf8_char{
	uint32_t len;
	unsigned char data[0];
} utf8_char;

extern utf8_char* alloc_char(int size);
extern void utf8_char_free(utf8_char* ch);
extern utf8_char** rd_utf8_str(unsigned char* buf,int size);
extern void release_utf8_str(utf8_char** utf8_str);
#endif
