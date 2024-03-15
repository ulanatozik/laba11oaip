//
//  main.c
//  lab11oaip
//
//  Created by Ульяна Тозик on 14.03.24.
//

 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


struct list
{
int book;
struct list *next;
};

typedef struct list ListNode;
typedef ListNode *ListNodePtr;
void insert (ListNodePtr*, int);
char del (ListNodePtr*, int);
int IsEmpty (ListNodePtr);
void printList (ListNodePtr);
void instructions (void);
char FindMax(ListNodePtr s);
char FindMin(ListNodePtr s);
void CountNegative (ListNodePtr , int*, int*);
float FindAverage(ListNodePtr s);
int ContainValue (ListNodePtr s, int);


int main (void)
{
    ListNodePtr start = NULL;
    int choice;
    int value;
    int elem;
    int max;
    int min;
    int count1=0;
    int sum1=0;
     
    
    do
    {
        instructions();
        printf("?\n");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
            {
                printf("Введите элемент: ");
                scanf("\n%d", &elem);
                insert(&start, elem);
                printList(start);
                break;
            }
                
            case 2:
            {
                if (!IsEmpty(start))
                {
                    printf("Введите элемент, который хотите удалить:");
                    scanf("\n%d", &elem);
                    if (del(&start,elem))
                    {
                        printf("Элемент %d удален.\n", elem);
                        printList(start);
                    }
                    else
                        printf("Элемент %d не найден.\n", elem);
                }
                else
                    printf("Список пуст.\n");
                break;
            }
                
            case 3:
            {
                if(!IsEmpty(start)){
                    max=FindMax(start);
                    printf("Максимальный элемент в списке: %d\n", max);
                    
                }
                else{
                    printf("Список пуст.\n");
                }
                break;
            }
                
            case 4:
            {
                if(!IsEmpty(start)){
                    min=FindMin(start);
                    printf("Минимальный элемент в списке: %d\n", min);
                    
                }
                else{
                    printf("Список пуст.\n");
                }
                break;
            }
                
            case 5:
            {
                CountNegative(start, &count1, &sum1);
                break;
            }
                
            case 6:
            {
                if(!IsEmpty(start))
                {
                    float average=FindAverage(start);
                    printf("Среднее значение всех элементов списка : %.2f", average);
                }
                else
                {
                    printf("Список пуст.\n");
                }
                break;
            }
            
            case 7:
            {
                if(!IsEmpty(start))
                {
                    printf("Введите элемент, наличие которого хотите проверить: \n");
                    scanf("%d", &value);
                    if(ContainValue(start, value))
                    {
                        printf("Элемент %d есть в списке\n", value);
                    }
                    else
                    {
                        printf("Элемента %d нет в списке\n", value);
                    }
                }
                break;
            }
                
            case 8:{
                printf("Конец программы.\n");
                return 0;
                
            }
                
            default:
            {
                printf ("Неверное значение. Повторите попытку\n");
                instructions();
                break;
            }
                
                
        }
         
    }while(choice!=8);
}
    
 
void instructions(void)
{
        printf("\nМеню:\n"
               "1.  Добавить элемент в список.\n"
               "2.  Удалить элемент из списка.\n"
               "3.  Найти максимальный элемент в списке\n"
               "4.  Найти минимальный элемент в списке\n"
               "5.  Найти количество и сумму отрицательных элементов\n"
               "6.  Найти среднее значение всех элементов списка\n"
               "7.  Проверить наличие заданного элемента в списке\n"
               "8.  Завершить программу.\n");
}
    
    
void insert (ListNodePtr *s, int value)
{
        ListNodePtr newP, previous, current;
        newP = (ListNodePtr) malloc (sizeof(ListNode));
        if (newP!=NULL)
        {
            newP->book =value;
            newP->next=NULL;
            previous=NULL;
            current=*s;
            while (current!=NULL && value>current->book)
            {
                previous=current;
                current=current->next;
            }
            if(previous==NULL)
            {
                newP->next=*s;
                *s=newP;
            }
            else
            {
                previous->next = newP;
                newP->next = current;
            }
        }
        else
            printf("Элемент %d не вставлен. Недостаточно памяти\n", value);
}

  
char del (ListNodePtr *s, int value)
{
        ListNodePtr previous, current, temp;
        if (value == (*s)->book)
        {
            temp=*s;
            *s=(*s)->next;
            free(temp);
            return value;
        }
        else
        {
            previous=*s;
            current=(*s)->next;
            while (current!=NULL && current->book!= value)
            {
                previous=current;
                current=current->next;
            }
            if (current!=NULL)
            {
                temp=current;
                previous->next=current->next;
                free(temp);
                return value;
            }
        }
        return '\0';
    }

     
int IsEmpty(ListNodePtr s)
{
        return s==NULL;
}

char FindMax(ListNodePtr s)
{
    char max= s->book;
    ListNodePtr current= s->next;
    
    while(current!=NULL)
    {
        if(current->book>max)
        {
            max=current->book;
        }
        current=current->next;
    }
    return max;
}

char FindMin(ListNodePtr s)
{
    char min= s->book;
    ListNodePtr current= s->next;
    
    while(current!=NULL)
    {
        if(current->book<min)
        {
            min=current->book;
        }
        current=current->next;
    }
    return min;
}

void CountNegative (ListNodePtr s, int *count, int *sum)
{
    *count = 0;
    *sum = 0;

    ListNodePtr current = s;
    while (current != NULL)
    {
        if (current->book < 0)
        {
            (*count)++;
            *sum += current->book;
        }
            current = current->next;
    }
    if(*count==0)
    {
        printf("В списке нет отрицательных элементов\n");
    }
    else
    {
        printf("Количество отрицательных элементов в списке: %d\n", *count);
        printf("Сумма отрицательных элементов в списке: %d\n", *sum);
    }
}

float FindAverage(ListNodePtr s)
{
    float sum=0;
    int count=0;
    ListNodePtr current=s;
    while(current!=NULL)
    {
        sum+=current->book;
        count++;
        current=current->next;
    }
    if(count==0)
    {
        return 0;
    }
    return sum/count;
}

int ContainValue(ListNodePtr s, int value)
{
    ListNodePtr current=s;
    while(current!=NULL)
    {
        if(current->book==value)
        {
            return 1;
        }
        current=current->next;
    }
    return 0;
}


 
void printList (ListNodePtr current)
{
        if (current==NULL)
            printf("Список пустой.\n");
        else
        {
            printf("Список :\n");
            while (current!=NULL)
            {
                printf("%d-->",current->book);
                current=current->next;
            }
            printf("NULL\n");
        }
}


