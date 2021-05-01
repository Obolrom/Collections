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
    if (node == NULL) return;
    if (free_data != NULL) free_data(node->data);
    free(node);
}

dlist_t* dlist_init(void (*free_node)(void*))
{
    dlist_t* list = (dlist_t*) malloc(sizeof(dlist_t));
    if (list == NULL) return NULL;
    list->size  = 0;
    list->free_data_function = free_node;
    list->left  = NULL;
    list->right = NULL;

    return list;
}

uint16_t dlist_push_back(dlist_t* list, void* data)
{
    if (list == NULL) return 0;

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
    if (list == NULL) return 0;

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

static void dlist_remove_left(dlist_t* list)
{
    // todo check for 3 cases
    //    1) if only 1 element
    //    2) if 2 elements
    //    3) 2+ elements
//    dlist_node_t* for_deletion;
//
//    for_deletion = list->left;
//    if (list->size > 0)
//    {
//        list->left = list->left->next;
//        list->left->prev = NULL;
//    }
//    else
//    {
//        list->left = NULL;
//        list->right = NULL;
//    }
//    dlist_node_free(for_deletion, NULL);
//    list->size--;
}

static dlist_node_t* find_node(dlist_t* list, void* data)
{
    dlist_node_t* searchable_node = NULL;

    for (dlist_node_t* current = list->left;
            current != list->right->next;
            current = current->next)
    {
        if (current->data == data)
        {
            searchable_node = current;
            break;
        }
    }

    return searchable_node;
}

uint16_t dlist_remove_node(dlist_t* list, void* data)
{
    if (list == NULL) return 0;

    dlist_node_t* for_removing = find_node(list, data);

    if (for_removing == NULL) return 0;

    // todo check if 'left', 'right', or another
    if (for_removing == list->left)
    {
        dlist_remove_left(list);
        return 1;
    }

    return 0;
}

uint16_t dlist_contains(dlist_t* list, void* data)
{
    return find_node(list, data) != NULL;
}

void dlist_free(dlist_t* list)
{
    if (list == NULL) return;

    dlist_node_t* for_deletion;
    for (dlist_node_t* current = list->left; current != list->right->next; )
    {
        for_deletion = current;
        current = current->next;
        dlist_node_free(for_deletion, list->free_data_function);
    }
    list->size = 0;
    free(list);
}