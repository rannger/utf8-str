#include "utf8_str.h"
#include <stdlib.h>
#include <strings.h>
#include <assert.h>

typedef struct linklist_item {
		utf8_char* ch;
		struct linklist_item* next;
} linklist_item;

typedef struct linklist {
		int count;
		linklist_item* head;
		linklist_item* tail;
} linklist;

static linklist* alloc_linklist(void)
{
	linklist* list = (linklist*)malloc(sizeof(linklist));
	list->count = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

static void linklist_append(linklist* list,linklist_item* item)
{
		if (0 == list->count) {
				list->count = 1;
				list->head = item;
				list->tail = item;
		} else {
				list->count++;
				list->tail->next = item;
				list->tail = item;
		}
}

static void linklist_release(linklist* list)
{
		while(list->count!=0) {
			linklist_item* item = list->head;
			list->head = list->head->next;
			free(item);
			list->count--;
		}
		free(list);
}

static linklist_item* alloc_linklist_item(utf8_char* ch)
{
		linklist_item* ret = (linklist_item*)malloc(sizeof(linklist_item));
		ret->ch = ch;
		ret->next = NULL;
		return ret;
}

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
	int index = 0;
	linklist* list = alloc_linklist();
	do {
		int len = char_len(buf[index]);
		utf8_char* ch = alloc_char(len);
		strncpy((char*)&(ch->data[0]),(const char*)buf+index,ch->len);
		index += len;
		linklist_append(list,alloc_linklist_item(ch));
		if (index-1==size) 
				break;
	}while(1);

	utf8_char** utf8_str = (utf8_char**)malloc(sizeof(utf8_char*) * (list->count+1));
	linklist_item* item = list->head;
	for (int i = 0;i<list->count;++i) {
		utf8_str[i] = item->ch;
		item = item->next;
	}
	utf8_str[list->count] = NULL;
	linklist_release(list);

	return utf8_str;
}

void release_utf8_str(utf8_char** utf8_str)
{
		for(int index=0;NULL!=utf8_str[index];++index) {
				free(utf8_str[index]);
		}
		free(utf8_str);
}

