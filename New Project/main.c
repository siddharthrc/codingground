#include <stdio.h>
#include <stdlib.h>

typedef struct list_s {
    struct list_s *flink;
    int data;
} list_t;

int
l_insert (list_t* head, int data)
{
    list_t *new_node, *temp_node;

    if (head == NULL) {
        return -1;
    }

    new_node = malloc(sizeof(list_t));
    if (!new_node) {
        /* No memory */
        return -1;
    }

    if (head->flink == NULL) {
        /* First entry */
        head->flink = new_node;
        new_node->flink = NULL;
        new_node->data = data;
        head->data++;
        printf("Data node %d add successful\n", data);
        return 0;
    }

    temp_node = head;
    while (temp_node->flink != NULL) {
        temp_node = temp_node->flink;
        if (temp_node->data == data) {
            printf("Duplicate data (%d) add attempt\n", data);
            return -1;
        }
    }

    temp_node->flink = new_node;
    new_node->flink = NULL;
    new_node->data = data;
    head->data++;
    printf("Data node %d add successful\n", data);

    return 0;
}

int
l_delete (list_t *head, int data)
{
    list_t *temp_node = NULL, *prev_node = NULL;

    for (prev_node = head, temp_node = head->flink;
         temp_node;
         temp_node = temp_node->flink, prev_node = prev_node->flink) {
        if (temp_node->data == data) {
            break;
        }
    }

    if (temp_node == NULL) {
        printf("Data node not found\n");
        return -1;
    }

    prev_node->flink = temp_node->flink;
    free(temp_node);
    head->data--;
    printf("Data node %d delete successful\n", data);

    return 0;
}

int
l_print (list_t *head)
{
    list_t *temp_node;

    if (!head) {
        return -1;
    }

    printf("Total number of elements in the list is %d\n", head->data);

    for (temp_node = head->flink; temp_node; temp_node = temp_node->flink) {
        printf("Data: %d ", temp_node->data);
    }

    printf ("\n");

    return 0;
}

int
main()
{
    int choice, data;
    list_t* head = NULL;

    head = malloc(sizeof(list_t));

    if (!head) {
        return -1;
    }

    head->flink = NULL;
    head->data = 0;

    while (1) {
        printf("Choose options (1 to add, 2 to print, 3 to delete and 4 to exit):");
        scanf("%d", &choice);

        if ((choice > 4) || (choice < 1)) {
            printf("Invalid choice %d\n", choice);
            continue;
        }

        if (choice == 1) {
            printf("Enter data to add to list:");
            scanf("%d", &data);
            l_insert(head, data);
            continue;
        }

        if (choice == 2) {
            l_print(head);
            continue;
        }

        if (choice == 3) {
            printf("Enter data to delete from list:");
            scanf("%d", &data);
            l_delete(head, data);
            continue;
        }

        if (choice == 4) {
            break;
        }
    }

    return 0;
}