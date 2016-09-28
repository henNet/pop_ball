#include "jhi_list.h"


void jhi_list_init(JHI_List *list, int data_bytes)
{

	list->bytes = data_bytes;
	list->data = NULL;
	list->next = NULL;
	list->size = 0;
}

int jhi_list_is_empty(JHI_List *list)
{
	if (list->data == NULL)
	{
		return 1;
	}

	return 0;
}

int jhi_list_get_size(JHI_List *list)
{
	return list->size;
}

JHI_ListNode* jhi_list_get_next(JHI_List *list)
{
	return list->next;
}

JHI_ListNode* jhi_list_node_get_next(JHI_ListNode *node)
{
	return node->next;
}

void *jhi_list_get_data(JHI_List *list)
{
	return list->data;
}

void *jhi_list_node_get_data(JHI_ListNode *node)
{
	return node->data;
}

void *jhi_list_node_get_data_by_index(JHI_List *list, int index)
{

	JHI_ListNode *node;
	int i;

	if (index >= list->size)
	{
		return NULL;
	}

	if (index == 0)
	{
		return list->data;

	}

	node = list->next;

	for (i = 1; i < index; i++)
	{
		node = node->next;
	}

	return node->data;

}

void jhi_list_insert_element(JHI_List *list, void *element)
{

	JHI_ListNode *node;
	JHI_ListNode *node_itr;

	//head insertion
	if (list->data == NULL)
	{
		list->data = malloc(list->bytes);
		memcpy(list->data, element, list->bytes);
		list->size++;
		return;
	}

	node_itr = list->next;

	node = (JHI_ListNode*)malloc(sizeof(JHI_ListNode));

	node->data = malloc(list->bytes);

	node->next = NULL;

	memcpy(node->data, element, list->bytes);

	if (node_itr == NULL)
	{
		list->next = node;
		list->size++;
		return;
	}


	while(node_itr->next != NULL)
	{
		node_itr = node_itr->next;
	}

	node_itr->next = node;
	list->size++;

}

void jhi_list_remove_element(JHI_List *list, void *element)
{
	JHI_ListNode *aux;
	JHI_ListNode *node_itr;

	if (jhi_list_is_empty(list))
	{
		return;
	}

	//element in head
	if (!memcmp(list->data, element, list->bytes))
	{
		free(list->data);
		aux = list->next;
		if (aux != NULL)
		{
			list->data = aux->data;
			list->next = aux->next;
			free(aux);
		}
		else
		{
			list->data = NULL;
			list->next = NULL;
		}
		list->size--;
		return;
	}

	node_itr = list->next;

	if (node_itr != NULL)
	{
		if (!memcmp(node_itr->data, element, list->bytes))
		{
			aux = node_itr->next;
			list->next = aux;
			free(node_itr->data);
			free(node_itr);
			list->size--;
			return;
		}

		while(node_itr->next != NULL)
		{
			if (!memcmp(node_itr->next->data, element, list->bytes))
			{
				aux = node_itr->next->next;
				free(node_itr->next->data);
				free(node_itr->next);
				node_itr->next = aux;
				list->size--;
				return;
			}

			node_itr = node_itr->next;
		}
	}

}

void jhi_list_remove_by_index(JHI_List *list, int index)
{
	JHI_ListNode *aux, *node_itr;
	int i;

	if (index >= list->size)
	{
		return;
	}

	if (index == 0)
	{
		free(list->data);
		aux = list->next;
		if (aux != NULL)
		{
			list->data = aux->data;
			list->next = aux->next;
			free(aux);
		}
		else
		{
			list->data = NULL;
			list->next = NULL;
		}
		list->size--;
		return;
	}
	node_itr = list->next;

	if (node_itr != NULL)
	{
		if (index == 1)
		{
			aux = node_itr->next;
			list->next = aux;
			free(node_itr->data);
			free(node_itr);
			list->size--;
			return;
		}

		aux = node_itr;
		node_itr = node_itr->next;

		for (i = 2; i < index; i++)
		{
			node_itr = node_itr->next;
		}

		aux->next = node_itr->next;
		free(node_itr->data);
		free(node_itr);
		list->size--;

	}
}

void jhi_list_clear(JHI_List *list)
{
	JHI_ListNode *node, *aux;

	if (jhi_list_is_empty(list))
	{
		return;
	}

	node = list->next;
	free(list->data);

	while(node != NULL)
	{
		aux = node;
		node = node->next;
		free(aux->data);
		free(aux);
	}

	list->size = 0;
}

void jhi_list_free(JHI_List *list)
{
	free(list);
}
