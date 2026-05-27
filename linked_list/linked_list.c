#include "list.h"
#include <stdio.h>
#include <stdlib.h>

SinglyLinkedList* create_list(void) {
    SinglyLinkedList* list = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));
    if (list) {
        list->head = NULL;
        list->count = 0;
    }
    return list;
}

void free_list(SinglyLinkedList* list) {
    if (!list) return;
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void add_first(SinglyLinkedList* list, int data) {
    if (!list) return;
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return;
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->count++;
}

void add_last(SinglyLinkedList* list, int data) {
    if (!list) return;
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return;
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->count++;
}

int add_at(SinglyLinkedList* list, int position, int data) {
    if (!list || position < 1 || position > list->count + 1) return 0;

    if (position == 1) {
        add_first(list, data);
        return 1;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return 0;
    newNode->data = data;

    Node* current = list->head;
    for (int i = 1; i < position - 1; i++) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    list->count++;
    return 1;
}

int remove_element(SinglyLinkedList* list, int data) {
    if (!list || list->head == NULL) return 0;

    Node* current = list->head;
    if (current->data == data) {
        list->head = current->next;
        free(current);
        list->count--;
        return 1;
    }

    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }

    if (current->next != NULL) {
        Node* toDelete = current->next;
        current->next = toDelete->next;
        free(toDelete);
        list->count--;
        return 1;
    }

    return 0;
}

Node* find_at(SinglyLinkedList* list, int position) {
    if (!list || position < 1 || position > list->count) return NULL;

    Node* current = list->head;
    for (int i = 1; i < position; i++) {
        current = current->next;
    }
    return current;
}

int get_count(const SinglyLinkedList* list) {
    return list ? list->count : 0;
}
