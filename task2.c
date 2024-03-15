//
//  task2.c
//  lab11oaip
//
//  Created by Ульяна Тозик on 15.03.24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person{
    char name [50];
    int age;
} Person;

typedef struct Node {
    Person data;
    struct Node *next;
} Node;

Node *head=NULL;

void insert(Person newData){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data=newData;
    newNode->next=NULL;
    
    if(head==NULL || strcmp(newData.name, head->data.name)<0)
    {
        newNode->next=head;
        head=newNode;
    }
    else{
        Node *current=head;
        while(current->next!=NULL && strcmp(newData.name, current->next->data.name)>0){
            
            current=current->next;
        }
        newNode->next=current->next;
        current->next=newNode;
    }
}

void deleteNode(char nameToDelete[]){
    Node *current=head;
    Node *prev=NULL;
    
    while(current!=NULL && strcmp(nameToDelete, current->data.name)!=0){
        prev=current;
        current=current->next;
    }
    
    if(current==NULL){
        printf("Элемент не найден.\n");
        return;
    }
    
    if(prev==NULL){
        head=current->next;
    }
    else{
        prev->next=current->next;
    }
    
    free(current);
}

void displayList(void){
    Node *current=head;
    
    if(current==NULL){
        printf("Список пустой.\n");
        return;
    }
    
    printf("Список:\n");
    while(current!=NULL){
        printf("%s (%d)-> ", current->data.name, current->data.age);
        current=current->next;
    }
    printf("NULL\n");
}

void freeList(void){
    Node *current=head;
    Node *temp;
    
    while(current!=NULL){
        temp=current;
        current=current->next;
        free(temp);
    }
    
    head=NULL;
    
}

int main(void){
    Person input;
    int choice;
    
    while(1){
        printf("\n1. Добавить человека\n2. Удалить человека\n3.Выход\nВаш выбор?\n");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
            {printf("Введите имя:\n");
                scanf("%s", input.name);
                printf("Введите возраст:\n");
                scanf("%d", &input.age);
                insert(input);
                break;}
            case 2: 
            {printf("Введите имя человека для удаления:\n");
                scanf("%s", input.name);
                deleteNode(input.name);
                break;}
            case 3:{displayList();
                break;}
            case 4: {freeList();
                exit(0);}
            default: printf("Неверный выбор.\n");
        }
    }
    return 0;
}
