#include <stdio.h>
#include <stdlib.h>
#include "sorted_list.h"

int compare_function(void *x, void *y) {
    int i = *(int *) x;
    int i2 = *(int *) y;
    return i == i2 ? 0 : i > i2 ? 1 : -1;
}

void destroy_function(void *object) {
}

static void print_list(list_t *list) {
    list_element_t *index = list->head;
    while (index != NULL) {
        printf("ELEMENT: %i\n", *(int *) index->value);
        index = index->next;
    }
}

int main(int argc, char **argv) {
    printf("Test case 1:\n");
    list_t *list = create_list(&compare_function, &destroy_function);
    int i = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;
    insert_object(list, &i2);
    insert_object(list, &i);
    insert_object(list, &i3);
    insert_object(list, &i5);
    remove_object(list, &i5);
    remove_object(list, &i2);
    print_list(list);
    destroy_list(list);

    printf("Test case 2:\n");
    list = create_list(&compare_function, &destroy_function);
    i = 17, i2 = 2, i3 = 8, i4 = 30, i5 = 14;
    insert_object(list, &i);
    insert_object(list, &i2);
    insert_object(list, &i3);
    insert_object(list, &i4);
    insert_object(list, &i5);
    remove_object(list, &i5);
    print_list(list);
    destroy_list(list);

    printf("Test case 3:\n");
    list = create_list(&compare_function, &destroy_function);
    i = 17, i2 = 2, i3 = 8, i4 = 30, i5 = 14;
    int i6 = 9;
    insert_object(list, &i);
    insert_object(list, &i2);
    insert_object(list, &i3);
    insert_object(list, &i4);
    insert_object(list, &i5);
    remove_object(list, &i5);
    insert_object(list, &i6);
    print_list(list);
    destroy_list(list);
    return 0;
}