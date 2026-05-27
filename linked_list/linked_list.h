#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct SinglyLinkedList {
    Node* head;
    int count;
} SinglyLinkedList;

SinglyLinkedList* create_list();
void free_list(SinglyLinkedList* list);

void add_first(SinglyLinkedList* list, int data);
void add_last(SinglyLinkedList* list, int data);
int add_at(SinglyLinkedList* list, int position, int data);

int remove_element(SinglyLinkedList* list, int data);
Node* find_at(SinglyLinkedList* list, int position);
int get_count(SinglyLinkedList* list);

void print_list_to_file(SinglyLinkedList* list, const char* filename);

#endif
