#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct node
{
    char inf[256];     
    struct node* next;  //ссылка на следующий
};

struct node* head = NULL; //вершина стека

//cброс остатка строки из буфера
static void drop_tail(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

//создание нового узла
struct node* get_struct(void)
{
    struct node* p = (struct node*)malloc(sizeof(struct node));
    if (p == NULL)
    {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    // читаем строку с пробелами до 255 симв
    if (scanf_s(" %255[^\n]", p->inf, (unsigned)sizeof(p->inf)) != 1)
    {
        p->inf[0] = '\0';
    }
    drop_tail();

    p->next = NULL;
    return p;
}

//добавление объекта на вершину стека
void push(void)
{
    struct node* p = get_struct();
    //работа стека
    p->next = head; 
    head = p;       
}

//снятие объекта с верха
void pop(void)
{
    if (head == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    struct node* temp = head;
    head = head->next; //вершиной становится нижележащий 

    printf("Извлечен объект: %s\n", temp->inf);
    free(temp);
}

//просмотр стека от вершины к основанию
void review(void)
{
    struct node* struc = head;

    if (head == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    while (struc != NULL)
    {
        if (struc == head)
            printf("Объект: %s  <-- вершина\n", struc->inf);
        else
            printf("Объект: %s\n", struc->inf);

        struc = struc->next;
    }
}

//освобождение памяти
void clear_list(void)
{
    struct node* temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    do {
        printf("\n--- СТЕК (LIFO) ---\n");
        printf("1. Добавить объект (на вершину)\n");
        printf("2. Извлечь объект (с вершины)\n");
        printf("3. Просмотр стека\n");
        printf("0. Выход\n");
        printf("Выбор: ");

        if (scanf_s("%d", &choice) != 1)
        {
            drop_tail();
            printf("Неверный ввод! Введите число.\n");
            choice = -1;
            continue;
        }
        drop_tail();

        switch (choice) {
        case 1: push();       break;
        case 2: pop();        break;
        case 3: review();     break;
        case 0: clear_list(); break;
        default: printf("Неверный ввод!\n");
        }
    } while (choice != 0);

    return 0;
}
 