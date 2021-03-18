#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "conio/conio.h"

void printToCoordinates(int y, int x, char text[])
{
    printf("\033[%d;%dH%s\n", y, x, text);
}

struct Node
{
    int x;
    int y;
    struct Node *next;
    struct Node *prev;
};
struct Node *head; /* Global variable - pointer to head node */
struct Node *tail; /* Global variable - pointer to tail node */

struct Node *getNewNode(int x, int y)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    (*newNode).x = x;
    (*newNode).y = y;
    (*newNode).prev = NULL;
    (*newNode).next = NULL;
    return newNode;
}

void insertAtHead(int x, int y)
{
    struct Node *newNode = getNewNode(x, y);
    if (head == NULL && tail == NULL)
    {
        head = newNode;
        tail = newNode;
        return;
    }
    head->next = newNode;
    (*newNode).prev = head;
    head = newNode;
    (*newNode).x = x;
    (*newNode).y = y;
}

void pop()
{
    tail = tail->next;
    free(tail->prev);
    tail->prev = NULL;
}

void print()
{
    struct Node *temp = tail;
    while (temp != NULL)
    {
        printToCoordinates(temp->x, temp->y, "*");
        temp = temp->next;
    }
}

void load()
{
    for (int i = 7; i < 75; i++)
    {
        printToCoordinates(2, i, "=");
    }
    for (int i = 3; i < 20; i++)
    {
        printToCoordinates(i, 74, "|");
    }
    for (int i = 3; i < 20; i++)
    {
        printToCoordinates(i, 7, "|");
    }
    for (int i = 7; i < 75; i++)
    {
        printToCoordinates(20, i, "=");
    }
    printf("\n");
}

int food_x()
{
    int x = (rand() % (19 - 3 + 1)) + 3;
    return x;
}

int food_y()
{
    int y = (rand() % (72 - 8 + 1)) + 8;
    return y;
}

int main()
{
    srand(time(NULL));
    int length;
    int speed = 200000;
    int foodx = food_x();
    int foody = food_y();
    char score[20];
    system("clear"); /* Clears the terminal */
    length = 0;
    insertAtHead(10, 25);
    insertAtHead(10, 26);
    insertAtHead(10, 27);
    insertAtHead(10, 28);
    insertAtHead(10, 29);
    insertAtHead(10, 30);
    printToCoordinates(foodx, foody, "+");
    char c;
    while (1)
    {
        system("clear");
        struct Node *temp = head;
        if (c_kbhit() != 0)
        {
            switch (c_getch())
            {
            case 'w':
                c = 'w';
                break;
            case 'a':
                c = 'a';
                break;
            case 's':
                c = 's';
                break;
            case 'd':
                c = 'd';
                break;
            }
        }
        switch (c)
        {
        case 'w':
            insertAtHead(temp->x - 1, temp->y);
            pop();
            break;
        case 'a':
            insertAtHead(temp->x, temp->y - 1);
            pop();
            break;
        case 's':
            insertAtHead(temp->x + 1, temp->y);
            pop();
            break;
        case 'd':
            insertAtHead(temp->x, temp->y + 1);
            pop();
            break;
        }

        if ((temp->x != foodx) || (temp->y != foody))
        {
            printToCoordinates(foodx, foody, "+");
        }
        else
        {
            if (speed > 25000)
            {
                speed -= 10000; /* Increases snake speed at each bite */
            }
            length += 1;
            switch (c)
            {
            case 'w':
                insertAtHead(temp->x - 1, temp->y);
                break;
            case 'a':
                insertAtHead(temp->x, temp->y - 1);
                break;
            case 's':
                insertAtHead(temp->x + 1, temp->y);
                break;
            case 'd':
                insertAtHead(temp->x, temp->y + 1);
                break;
            }
            foodx = food_x();
            foody = food_y();
            printToCoordinates(foodx, foody, "+");
        }

        print();
        load();
        sprintf(score, "Score: %d", length);
        // sprintf(score, "x: %d, y: %d", foodx, foody);
        printToCoordinates(21, 37, score);
        usleep(speed);
    }
}
