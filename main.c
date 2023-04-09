/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying
the concepts learned. I have constructed the functions and their respective algorithms and corresponding
code by myself. The program was run, tested, and debugged by my own efforts. I further certify that I have
not copied in part or whole or otherwise plagiarized the work of other students and/or persons.

                                                                       <your full name>, Your ID# <number>
*********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "quiz.h"

/**
 * The function displays a menu for a trivia quiz and returns the user's choice.
 *
 * @return a character, which is the user's choice from the menu options..
 */
char menu()
{
    char ch;

    printf("         TRIVIA QUIZ\n");
    printf("-----------------------------\n");
    printf("      [M] - Manage Data\n");
    printf("      [P] - Play\n");
    printf("      [E] - Exit\n");
    printf("-----------------------------\n");
    printf("\nEnter your choice: ");
    scanf(" %c", &ch);

    return ch;
}

/**
 * The function "choice" presents a menu of options and executes corresponding actions based on user
 * input.
 */
void choice()
{
    data *head = NULL;
    player *node = NULL;
    const char *filename;

    int valid = 1;
    char choice;

    do
    {
        choice = menu();
        switch (choice)
        {
        case 'M':
        case 'm':
            if (chances())
            {
                filename = admin_choice(&head);
                free(head);
            }
            break;
        case 'P':
        case 'p':
            trivia_choice(&node, filename);
            break;
        case 'E':
        case 'e':
            valid = 0;
            break;
        }
    } while (valid);
}

/**
 * The main function calls the choice function.
 *
 * @return The function `main()` is returning an integer value of 0.
 */
int main()
{
    choice();

    return 0;
}