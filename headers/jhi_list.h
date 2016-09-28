#ifndef JHI_LIST_H
#define JHI_LIST_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct JHI_ListNode JHI_ListNode;

struct JHI_ListNode {
	JHI_ListNode* next;
	void *data;
};

typedef struct {
	void *data;
	int bytes;
	int size;
	JHI_ListNode *next;
}JHI_List;

void jhi_list_init(JHI_List *list, int data_bytes);

int jhi_list_get_size(JHI_List *list);

int jhi_list_is_empty(JHI_List *list);

void *jhi_list_get_data(JHI_List *list);

void *jhi_list_node_get_data(JHI_ListNode *node);

void *jhi_list_node_get_data_by_index(JHI_List *list, int index);

JHI_ListNode* jhi_list_get_next(JHI_List *list);

JHI_ListNode* jhi_list_node_get_next(JHI_ListNode *node);

void jhi_list_insert_element(JHI_List *list, void *element);

void jhi_list_remove_element(JHI_List *list, void *element);

void jhi_list_clear(JHI_List *list);

void jhi_list_free(JHI_List *list);

#endif


