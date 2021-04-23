#include "dlist.h"

dlist_node_t* dlist_node_init(void* data)
{
    dlist_node_t* node = (dlist_node_t*) malloc(sizeof(dlist_node_t));
    if (node == NULL) return NULL;
    node->data = data;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

void dlist_node_free(dlist_node_t* node, void (*free_data)(void*))
{
    if (free_data != NULL) free_data(node->data);
    free(node);
}

dlist_t* dlist_init(void (*free_node)(void*))
{
    dlist_t* list = (dlist_t*) malloc(sizeof(dlist_t));
    if (list == NULL) return NULL;
    list->size  = 0;
    list->free_data = free_node;
    list->left  = NULL;
    list->right = NULL;

    return list;
}

uint16_t dlist_push_back(dlist_t* list, void* data)
{
    dlist_node_t* node = dlist_node_init(data);
    if (node == NULL)
        return 0;

    if (list->size == 0)
    {
        list->left = node;
        list->right = node;
    }
    else
    {
        list->right->next = node;
        node->prev = list->right;
        list->right = node;
    }
    list->size++;

    return 1;
}

uint16_t dlist_push_front(dlist_t* list, void* data)
{
    dlist_node_t* node = dlist_node_init(data);
    if (node == NULL)
        return 0;

    if (list->size == 0)
    {
        list->left = node;
        list->right = node;
    }
    else
    {
        list->left->prev = node;
        node->next = list->left;
        list->left = node;
    }
    list->size++;

    return 1;
}

uint16_t dlist_remove_node(dlist_t* list, void* data)
{
    return 0;
}

void dlist_free(dlist_t* list)
{
    dlist_node_t* temp;
    for (dlist_node_t* current = list->left; current != list->right; )
    {
        temp = current;
        current = current->next;
        dlist_node_free(temp, list->free_data);
    }
    free(list);
}