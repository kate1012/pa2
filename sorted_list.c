#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sorted_list.h"

/*
 * Creates a sorted list.
 */
list_t *create_list(compare_function_t *compare_func, destroy_function_t *destroy_func) {
    list_t *list = malloc(sizeof(list_t));
    if (list == NULL) {
        return NULL;
    }
    list->compare_function = compare_func;
    list->destroy_function = destroy_func;
    list->head = NULL;
    return list;
}

/*
 * Destroys a sorted list.
 */
void destroy_list(list_t *list) {
    list_element_t *index = list->head;
    while (index != NULL) {
        list->destroy_function(index->value);
        free(index);
        index = index->next;
    }
    free(list);
}

/*
 * Creates an element for a sorted list.
 */
list_element_t *create_list_element(void *value, list_element_t *next) {
    /* We dynamically allocate memory for an element node */
    list_element_t *element = malloc(sizeof(list_element_t));
    if (element == NULL) {
        return NULL;
    }
    /* We set the value and the next node for the new element.*/
    element->value = value;
    element->next = next;
    return element;
}

/*
 * Inserts a given element directly after the given index.
 */
static void insert_after(list_element_t *index, list_element_t *element) {
    list_element_t *tmp = index->next;
    element->next = tmp;
    index->next = element;
}

/*
 * Inserts a given element directly before the given index.
 * This function returns true when it succeeds, and false when it fails.
 */
static bool insert_before(list_t *list, list_element_t *index, list_element_t *element) {
    if (index == list->head) {
        /* If the insert index is the head, we insert the node before the head */
        element->next = list->head;
        list->head = element;
    } else {
        /* We loop through the indices until we find the insert index, and insert the node before */
        list_element_t *tmp = list->head;
        while (tmp != NULL) {
            if (tmp->next == index) {
                insert_after(tmp, element);
                return true;
            }
            tmp = tmp->next;
        }
    }
    return false;
}

/*
 * Inserts an object in the given sorted list.
 * This function returns 1 when it succeeds, and 0 when it fails.
 */
int insert_object(list_t *list, void *object) {
    if (list->head == NULL) {
        /* If the head is null, we insert the object as the head. */
        list->head = create_list_element(object, NULL);
    } else {
        list_element_t *index = list->head;
        /* We loop through the list and compare each node to the object we want to insert */
        while (true) {
            int result = list->compare_function(object, index->value);
            switch (result) {
                case 0:// equal
                    /* If the result is equal, there is an error. */
                    printf("Error! Cannot insert duplicate values.\n");
                    return 1;
                case 1:// greater than
                    /* If the result is greater than, we insert the object before the element */
                    insert_before(list, index, create_list_element(object, NULL));
                    return 1;
                case -1:// less than
                    /* We ignore less than, because we need to continue looking */
                default:
                    break;
            }
            if (index->next == NULL) {
                /* If we are at the end of the list, we insert the object at the end. */
                insert_after(index, create_list_element(object, NULL));
                return 1;
            }
            index = index->next;
        }
    }
    return 0;
}

/*
 * Removes an object from the given sorted list.
 * This function returns 1 when it succeeds, and 0 when it fails.
 */
int remove_object(list_t *list, void *object) {
    list_element_t *index = list->head;
    /* We loop through the list */
    while (index != NULL) {
        if (index == list->head && index->value != NULL) {
            if (list->compare_function(index->value, object) == 0) {
                /* If the object is the head, we set the new head to the next node */
                list->head = index->next;
                return 1;
            }
        }
        if (index->next != NULL && index->next->value != NULL) {
            if (list->compare_function(index->next->value, object) == 0) {
                /* Once we find the object, we remove the node from the list */
                index->next = index->next->next;
                return 1;
            }
        }
        index = index->next;
    }
    return 0;
}

/*
 * Checks if a list contains the given object.
 */
bool contains_object(list_t *list, void *object) {
    list_element_t *index = list->head;
    while (index != NULL) {
        if (index->value != NULL && list->compare_function(index->value, object) == 0) {
            return true;
        }
        index = index->next;
    }
    return false;
}

/*
 * Constructs a sorted list iterator, given the list.
 */
sorted_list_iterator_t *create_iterator(list_t *list) {
    sorted_list_iterator_t *iterator = malloc(sizeof(sorted_list_iterator_t));

    /* list must be initialized and have at least 1 element */
    if (list == NULL || list->head == NULL) {
        printf("Error");
        return NULL;
    }
    iterator->current_index = list->head;
    return iterator;
}

/*
 * Gets the value of the current node that the sorted list
 * iterator is pointing to.
 */
void *get_item(sorted_list_iterator_t *iterator) {
    return iterator->current_index->value;
}

/*
 * Gets the next item in the sorted list iterator, and sets
 * the current index to that node.
 */
void *next_item(sorted_list_iterator_t *iterator) {
    list_element_t *next_element = iterator->current_index->next;
    iterator->current_index = next_element;
    return next_element->value;
}