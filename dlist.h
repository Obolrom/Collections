#ifndef COLLECTIONS_DLIST_H
#define COLLECTIONS_DLIST_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct dlist_node
{
    void* data;
    struct dlist_node* prev;
    struct dlist_node* next;
} dlist_node_t;

typedef struct dlist
{
    struct dlist_node* left;
    struct dlist_node* right;
    size_t size;
    void (*free_data_function)(void*);
} dlist_t;

dlist_node_t* dlist_node_init(void* data);
void dlist_node_free(dlist_node_t* node, void (*free_node)(void*));

dlist_t* dlist_init(void (*free_data)(void*));
uint16_t dlist_push_back(dlist_t* list, void* data);
uint16_t dlist_remove_node(dlist_t* list, void* data);
uint16_t dlist_push_front(dlist_t* list, void* data);
uint16_t dlist_contains(dlist_t* list, void* data);
void dlist_reverse(dlist_t* list);
void dlist_sort(dlist_t* list, int (*comparator)(const void* , const void* ));
void dlist_free(dlist_t* list);

#endif
