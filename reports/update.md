# Slytherin

Students: Yehya Albakri

The goal for my project is to write a game of snake. The lower bound is just having a snake that can move around, eating randomly generated food that regenerates when the snake eats it, making the snake longer each time. As an upper bound, there are many features that I could add. Some of these features include a splashscreen, score, different difficulty settings, prompt to restart after game over, pause resume, making food generation avoid snake tail, and looping through walls.

Some of my main learning goals include getting a better understanding of how pointers work as I still do not completely understand them. I also want to get better at efficient programming, so I would like to implement an efficient model for this game. The great part about snake is that it is not difficult to add features to the game. My final goal is understanding what it takes to write a program from scratch and to defragment my understanding of c.

So far, I have completed the minimum viable product for the game with some additional features. The game includes an introductory splash screen with difficulty setting selection and a game over screen. Within the easy mode, the snake can loop through the walls, but in medium and hard mode it can’t. Additionally, the snake gets faster the longer it gets, varying by game difficulty. In game over, the game also prompts you to restart, resetting the snake and the score. I believe I have all the resources I need from now until the end of the project. I have mostly been using Stack Overflow and the CA (Manu). The only implementation reference I am using is an implementation of a doubly linked list (cited at the top of my implementation). Otherwise, everything is written from scratch.

Currently, I am working on adding a play / pause feature to the game. In the game, it is also possible to move backward, but since the snake would go inside itself, it dies. I would like to make the snake unable to go backward on itself. I would also like to add a distinction between the head and the tail of the snake because in playing the first time, the player has no idea what direction the snake starts in. The definition of done is presenting each of these tasks in the final product.

Trello: https://trello.com/b/mGpR0Gtn/slytherin
GitHub: https://github.com/YA9/SoftSysSlytherin
