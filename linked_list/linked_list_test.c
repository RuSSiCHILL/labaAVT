#include "list.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    SinglyLinkedList* list = create_list();
    assert(list != NULL);
    assert(get_count(list) == 0);

    add_first(list, 10);
    add_last(list, 30);
    assert(get_count(list) == 2);

    int success = add_at(list, 2, 20);
    assert(success == 1);
    assert(get_count(list) == 3);

    Node* n1 = find_at(list, 1);
    Node* n2 = find_at(list, 2);
    Node* n3 = find_at(list, 3);
    assert(n1 != NULL && n1->data == 10);
    assert(n2 != NULL && n2->data == 20);
    assert(n3 != NULL && n3->data == 30);

    assert(find_at(list, 4) == NULL);

    int removed = remove_element(list, 20);
    assert(removed == 1);
    assert(get_count(list) == 2);
    assert(find_at(list, 2)->data == 30);

    free_list(list);

    printf("List tests passed successfully!\n");
    return 0;
}
