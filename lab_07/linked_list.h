#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct linked_list_node_t
{
    void *data;
    struct linked_list_node_t *next_node;
    
} linked_list_node_t;

// Adding to tail
typedef struct linked_list_t
{
    linked_list_node_t *head;
    linked_list_node_t *tail;

    int size;
} linked_list_t;

/*  Node  */
linked_list_node_t *create_node(void *data);
void set_null_node(linked_list_node_t *node);

void delete_node(linked_list_node_t *node, void destructor(void*));

/*  List  */
void set_null_list(linked_list_t *list);
int add_element(linked_list_t *list, void *data);
int del_element(linked_list_t *list, int index_to_delete, void destructor(void*));

int copy_linked_list(linked_list_t *dest, linked_list_t *source);
// If error return NULL. But if data == NULL same behaivor
void *get_element(linked_list_t *list, int index);

int delete_linked_list(linked_list_t *list, void destructor(void*));
int cut_linked_list(linked_list_t *list, int new_size, void destructor(void*));
int cat_linked_list(linked_list_t *first, linked_list_t *second);

int is_list_correct(linked_list_t *list);
int is_list_not_empty(linked_list_t *list);
int is_list_empty(linked_list_t *list);

#endif