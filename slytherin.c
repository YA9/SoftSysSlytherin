/* Author: Yehya Albakri
Slytherin is an implementation of the classic snake game.

Resources used:
https://gist.github.com/mycodeschool/7429492
https://github.com/zoelabbb/conio.h

command to run: gcc slytherin.c conio/conio.c -o slytherin && ./slytherin

Notes:
- Game has three modes, the higher the difficulty, the faster the snake gets at each food consumed and the higher max speed it has. 
- In easy mode, the snake can pass through walls, whereas in medium and hard modes, the walls kill the snake.

Instructions:
- Select difficulty and press enter.
- Controls are 'w' 'a' 's' 'd'.
- Press 'P' to pause and resume the game.
- Snake starts moving in the right direction, so moving backwards kills it.
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

struct Node /* Node is defined by the next, prev and its coordinates */
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

void insertAtHead(int x, int y) /* Inserts head to the snake at 'x' and 'y' positions */
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

void pop() /* Pops snake's tail (occurs at each frame) */
{
    tail = tail->next;
    free(tail->prev); /* Frees the unused tail from memory */
    tail->prev = NULL;
}

void deleteSnake() /* Runs pop on the entire snake then clears the head and tail. Used at game over when player is given the option to restart. */
{
    struct Node *temp = head;
    while (temp->prev != NULL)
    {
        pop();
    }
    head = NULL;
    tail = NULL;
}

void print() /* Iterates through the nodes of the snake and prints at their x and y positions. */
{
    struct Node *temp = head;

    /* Following two lines change the head character of the snake. */
    // printToCoordinates(temp->x, temp->y, "+");
    // temp = temp->prev;
    while (temp != NULL)
    {
        printToCoordinates(temp->x, temp->y, "*");
        temp = temp->prev;
    }
}

void load() /* Generates Game's frame. */
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

int food_x() /* Generates a food at the x coordinate */
{
    int x = (rand() % (19 - 3 + 1)) + 3;
    return x;
}

int food_y() /* Generates a food at the y coordinate */
{
    int y = (rand() % (72 - 8 + 1)) + 8;
    return y;
}

int selfCollision() /* Returns 1 if the snake collides with itself, 0 otherwise. */
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

char gameOver() /* Provides a Game Over screen and returns 'y' or 'n'. */
{
    char choice;
    printToCoordinates(11, 37, "GAME OVER");
    printToCoordinates(13, 35, "RESTART? y / n");
    scanf("%c", &choice);
    return choice;
}

int intro() /* Intro screen, returns difficulty selected by player. */
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
    char pause;
    system("clear"); /* Clears the terminal */
    length = 0;
    difficulty = intro();
    switch (difficulty) /* Sets game difficulty by max speed and snake acceleration over score. */
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
    insertAtHead(11, 38); /* Creates starting snake. */
    insertAtHead(11, 39);
    insertAtHead(11, 40);
    insertAtHead(11, 41);
    insertAtHead(11, 42);
    printToCoordinates(foodx, foody, "+"); /* Creates starting food */
    char c;                                /* Variable storing most recently pressed key. */
    while (1)
    {
        system("clear"); /* Clears board at each frame. */
        struct Node *temp = head;
        if (difficulty == 2 || difficulty == 3) /* On difficulties 2 and 3, walls kill the snake. */
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
        else if (difficulty == 1) /* On difficlty 1, snake can pass through walls. */
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
        if (c_kbhit() != 0) /* If key is pressed, updates 'c' with the key. */
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
            case 'p':
                c = 'p';
            }
        }
        switch (c) /* Depending on the most recent direction of the snake, snake inserts head in that direction and pops the tail. This makes the snake move at each frame. */
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
        case 'p':
            printToCoordinates(0, 36, "GAME PAUSED");
            printToCoordinates(22, 24, "PRESS 'w', 'a', 's', 'd' TO RESUME");
        }

        if ((temp->x != foodx) || (temp->y != foody)) /* Prints new food at same place in each new frame. */
        {
            printToCoordinates(foodx, foody, "+");
        }
        else /* If snake eats food, adds the food as head to the snake, generates new food, and increases snake speed. */
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

            struct Node *tempFood = head;
            while (tempFood != NULL) /* Makes sure no food is generates inside the snake. */
            {
                if (tempFood->x == foodx && tempFood->y == foody)
                {
                    // usleep(100);
                    foodx = food_x();
                    foody = food_y();
                    struct Node *tempFood = head;
                }
                tempFood = tempFood->prev;
            }
            printToCoordinates(foodx, foody, "+");
        }
        if (selfCollision() == 1) /* Makes Game Over if snake collides with itself. */
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
        print(); /* Prints the current snake at each frame. */
        load();
        sprintf(score, "Score: %d", length); /* Prints the score at the bottom of the game. */
        printToCoordinates(21, 37, score);
        usleep(speed); /* Controls the time delay between frames. */
    }
}
