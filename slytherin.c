/* Author: Yehya Albakri
Slytherin is an implementation of the classic snake game.

Resources used:
https://gist.github.com/mycodeschool/7429492
https://github.com/zoelabbb/conio.h

command to run: gcc slytherin.c conio/conio.c -o slytherin && ./slytherin

Notes:
- Game has three modes, the higher the difficulty, the faster the snake gets at each food consumed and the higher max speed it has. 
- In easy mode, the snake can pass through walls, whereas in medium and hard modes, the walls kill the snake.
*/

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

void deleteSnake()
{
    struct Node *temp = head;
    while (temp->prev != NULL)
    {
        pop();
    }
    head = NULL;
    tail = NULL;
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
    struct Node *tempx = head;
    while (tempx != NULL)
    {
        if (tempx->x == x)
        {
            // usleep(100);
            int x = (rand() % (19 - 3 + 1)) + 3;
            struct Node *tempx = head;
        }
        tempx = tempx->prev;
    }
    return x;
}

int food_y()
{
    int y = (rand() % (72 - 8 + 1)) + 8;
    struct Node *tempy = head;
    while (tempy != NULL)
    {
        if (tempy->y == y)
        {
            // usleep(100);
            int y = (rand() % (19 - 3 + 1)) + 3;
            struct Node *tempy = head;
        }
        tempy = tempy->prev;
    }
    return y;
}

int selfCollision()
{
    struct Node *temp = head;
    int x = temp->x;
    int y = temp->y;
    while (temp->prev != NULL)
    {
        temp = temp->prev;
        if (temp->x == x && temp->y == y)
        {
            return 1;
        }
    }
    return 0;
}

char gameOver()
{
    char choice;
    printToCoordinates(11, 37, "GAME OVER");
    printToCoordinates(13, 35, "RESTART? y / n");
    scanf("%c", &choice);
    return choice;
}

int intro()
{
    printToCoordinates(7, 36, "SLYTHERIN");
    printToCoordinates(9, 32, "SELECT DIFFICULTY");
    printToCoordinates(11, 36, "1 - EASY");
    printToCoordinates(13, 36, "2 - MEDIUM");
    printToCoordinates(15, 36, "3 - HARD");
    int difficulty;
    load();
    scanf("%d", &difficulty);
    return difficulty;
}

int main()
{
    srand(time(NULL));
    int length;
    int difficulty;
    int speed = 200000;
    int speed_decrement;
    int max_speed_delay;
    int foodx = food_x();
    int foody = food_y();
    char score[20];
    system("clear"); /* Clears the terminal */
    length = 0;
    difficulty = intro();
    switch (difficulty)
    {
    case 1:
        speed_decrement = 100;
        max_speed_delay = 150000;
        break;
    case 2:
        speed_decrement = 1000;
        max_speed_delay = 75000;
        break;
    case 3:
        speed_decrement = 1000;
        max_speed_delay = 25000;
    }
    insertAtHead(11, 38);
    insertAtHead(11, 39);
    insertAtHead(11, 40);
    insertAtHead(11, 41);
    insertAtHead(11, 42);
    printToCoordinates(foodx, foody, "+");
    char c;
    while (1)
    {
        system("clear");
        struct Node *temp = head;
        if (difficulty == 2 || difficulty == 3)
        {
            if (temp->x < 3 || temp->x > 19 || temp->y > 72 || temp->y < 8)
            {
                print();
                printToCoordinates(21, 37, score);
                load();
                if (gameOver() == 'y')
                {
                    deleteSnake();
                    main();
                }
                printToCoordinates(21, 37, score);
                break;
            }
        }
        else if (difficulty == 1)
        {
            if (temp->x < 3)
            {
                temp->x = 19;
            }
            else if (temp->x > 19)
            {
                temp->x = 3;
            }
            else if (temp->y < 8)
            {
                temp->y = 72;
            }
            else if (temp->y > 72)
            {
                temp->y = 8;
            }
        }
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
            if (speed > max_speed_delay)
            {
                speed -= speed_decrement; /* Increases snake speed at each bite */
            }
            length += 1;
            switch (c)
            {
            case 'w':
                insertAtHead(temp->x - 2, temp->y);
                break;
            case 'a':
                insertAtHead(temp->x, temp->y - 2);
                break;
            case 's':
                insertAtHead(temp->x + 2, temp->y);
                break;
            case 'd':
                insertAtHead(temp->x, temp->y + 2);
                break;
            }
            foodx = food_x();
            foody = food_y();
            printToCoordinates(foodx, foody, "+");
        }
        if (selfCollision() == 1)
        {
            print();
            printToCoordinates(21, 37, score);
            load();
            if (gameOver() == 'y')
            {
                deleteSnake();
                main();
            }

            printToCoordinates(21, 37, score);
            break;
        }
        print();
        load();
        sprintf(score, "Score: %d", length);
        printToCoordinates(21, 37, score);
        usleep(speed);
    }
}
