#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*1.Створити однозв’язний список товарів в магазині (Назва, Ціна, Кількість).
Виділити в динамічній пам’яті і додати до списку 5 товарів.
Додавати товари, один на початок списку, наступний в кінець списку і так всі 5 товарів.
Написати функцію, яка видаляє перший і останній товар зі списку.
В кінці звільнити весь список.*/

/*2.Створити однозв’язний список товарів в магазині (Назва, Ціна, Кількість).
Виділити в динамічній пам’яті і додати до списку 5 товарів.
Додавати товари так: 1-ий товар на почаок списку, а всі інші 4-ри на другу позицію в списку. Тобто кожен товар крім першого, який
додається до списку, повинен бути доданим в список на 2-гу (одразу після голови) позицію.
Написати функцію, яка видаляє 1-ий і 4-ий товар зі списку.
В кінці звільнити весь список.*/

/*3.Створити однозв'язний список товарів в магазині (Назва, Ціна, Кількість).
Виділити в динамічній пам’яті і додати до списку 5 товарів.
Додавати товари щоразу на кінець списку.
Написати функцію, яка переставляє місцями 4-ий товар і товар, кількість якого найбільша.
Звільнити пам'ять*/

/*4.Створити однозв’язний список товарів в магазині (Назва, Ціна, Кількість).
Виділити в динамічній пам’яті і додати до списку 5 товарів.
Написати функцію, яка додає товар до списку так, що він одразу стає в свою
позицію в порядку зростання ціни. (напр. якщо в списку є товари з цінами 1.5 6.0
9.0 і ви додаєте товар з ціною 7.0, то він повинен бути вставлений між товарами з
цінами 6.0 і 9.0)
Всі 5 товарів додати задопомогою цієї вашої функції.
Видалити зі списку 2,3 і 4-ий елементи.*/

typedef struct NodeData
{
    char name[20];
    double price;
    int amount;
} Data;

typedef struct Node {

    Data data;
    struct Node* next;
}Node;

// Inserting node to start of list
void append(Node** head_ref, Data data);

// Inserting node to end of list
void push(Node** head_ref, Data data);

// Inserting node to custom position
void add(Node** head_ref, Data data, int index);

// Inserting node by prise ascending
void insert(Node** head_ref, Data data);

// Deleting node at index
void deleteIndex(Node** head_ref, int index);

// Returns node with the highest amount
Node* highestAmountNode(Node** head_ref);

void printList(Node* head);

void freeList(Node* head);

int main(void)
{
    Node* head = NULL;

    /*append(&head, (Data) { .amount = 10, .price = 2.5, .name = "product1" });
    push(&head, (Data) { .amount = 31, .price = 1.3, .name = "product2" });
    append(&head, (Data) { .amount = 15, .price = 4.7, .name = "product3" });
    push(&head, (Data) { .amount = 3, .price = 30.1, .name = "product4" });

    add(&head, (Data) { .amount = 13, .price = 12.3, .name = "product5" }, 4);

    printList(head);*/
    insert(&head, (Data) { .amount = 15, .price = 12.1, .name = "product3" });
    insert(&head, (Data) { .amount = 18, .price = 4.9, .name = "product1" });
    insert(&head, (Data) { .amount = 15, .price = 7.8, .name = "product2" });
    push(&head, (Data) { .amount = 3, .price = 30.1, .name = "product4" });
    push(&head, (Data) { .amount = 2, .price = 12.3, .name = "product5" });

    // deleting node with highest amount
    Node* node = highestAmountNode(&head);
    int i = 0;
    while (head->next != NULL)
    {
        if (head == node)
        {
            break;
        }
        head = head->next;
        i++;
    }
    deleteIndex(&head, i);
    // end deleting the highest amount node 
   
    //deleteIndex(&head, 0);// now list length is 4, to delete product 4 which was 4th we have to delete 2nd element of new array!
    //deleteIndex(&head, 2);

    printList(head);
    freeList(head);
    return 0;
}

// Inserting node to start of list
void append(Node** head_ref, Data data)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node)
    {
        new_node->data = data;
        new_node->next = (*head_ref);
        (*head_ref) = new_node;
    }
    return;
}

// Inserting node to end of list
void push(Node** head_ref, Data data)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    Node* last = *head_ref;

    if (new_node)
    {
        new_node->data = data;
        new_node->next = NULL;

        if (*head_ref == NULL)
        {
            *head_ref = new_node;
            return;
        }

        while (last->next != NULL)
            last = last->next;

        last->next = new_node;
    }
    return;
}

// Inserting node to custom position
void add(Node** head_ref, Data data, int index)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    Node* current = (*head_ref);
    if (0 == index)
    {
        append(head_ref, data);
        return;
    }
    for (int i = 0; i < index-1; i++)
    {
        if (current->next)
        {
            current = current->next;
        }
        else {
            fprintf(stderr, "Index is too large!");
            return;
        }
    }

    if (new_node)
    {
        new_node->data = data;
        new_node->next = current->next;
        current->next = new_node;
    }
    return;
}

// Inserting node by prise ascending
void insert(Node** head_ref, Data data)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    if (new_node)
    {
        struct Node* current;
        if (*head_ref == NULL
            || (*head_ref)->data.price
            >= new_node->data.price) {
            new_node->next = *head_ref;
            *head_ref = new_node;
        }
        else {
            current = *head_ref;
            while (current->next != NULL
                && current->next->data.price < new_node->data.price) {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
            }
    }
    return;
}

void deleteIndex(Node** head_ref, int index)
{
    if (*head_ref == NULL)
        return;

    struct Node* temp = *head_ref;

    if (index == 0) {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    for (int i = 0;i < index - 1; i++)
    {
        if (temp->next)
        {
            temp = temp->next;
        }
        else {
            fprintf(stderr, "Index is too large!");
            return;
        }
    }
    Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
    return;
}

// Returns node with the highest amount
Node* highestAmountNode(Node** head_ref)
{
    Node* current = (*head_ref);
    Node* temp = *head_ref;
    while (temp->next != NULL)
    {
        if (temp->data.amount > current->data.amount)
        {
            current = temp;
        }
        temp = temp->next;
    }
    return current;
}

void freeList(Node* head)
{
    Node* tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void printList(Node* head)
{
    Node* current_node = head;
    while (current_node != NULL) {
        printf(" %s %.2lf %d\n", current_node->data.name, current_node->data.price, current_node->data.amount);
        current_node = current_node->next;
    }
    return;
}
