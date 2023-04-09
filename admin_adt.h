#include "admin_struct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100    // Maximum size of the hash table.

/**
 * The above code is implementing a function called "count" that takes a double pointer 
 * to a struct called "data" as input. It counts the number of nodes in a linked list 
 * by traversing through the list using a while loop and incrementing a counter 
 * variable "i" for each node. Finally, it returns the count of nodes in the linked list.
 * 
 * @param head A double pointer to a linked list of data structures.
 * @return  int
 */

int count(data **head_ref)
{
    data *temp = *head_ref;
    int i = 0;
    while (temp != NULL)
    {
        i++;
        temp = temp->next;
    }
    return i;
}

/**
 * hashFunctionForAdmin is a function that takes a string as input and returns an integer.
 * It calculates the sum of the ASCII values of the characters in the string and returns the remainder
 * when the sum is divided by the maximum size of the hash table.
 * 
 * @param key A string that is to be hashed.
 * @return int
*/

int hashFunctionForAdmin(char *key)
{
    int sum = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        sum += key[i];
    }
    return sum % MAX_SIZE;
}

/**
 * The above code is a function that takes a pointer to a pointer of a 
 * data structure called "head" as input. It prints a list of 
 * distinct topics from the data structure and prompts the user to 
 * select a topic. If the user selects a topic, the function returns
 * a pointer to a string containing the selected topic. 
 * If the user selects to go back to the main menu, the function returns NULL. 
 * The function uses a hash table to keep track of the distinct topics 
 * and their indices in a string array.
 * 
 * @param head A double pointer to a linked list of data structures.
 * @return char* = topic name chosen by the user or NULL
 */
const char *printDistinctTopicsForAdmin(data **head)
{
    data *current = *head;
    int hash[MAX_SIZE] = {0};
    char str[MAX_SIZE][30];
    char *name = malloc(255 * sizeof(char));
    int i = 0, choice;

    printf("---------------------------------------\n");
    printf("                 TOPICS\n");
    printf("---------------------------------------\n");

    while (current != NULL)
    {
        if (hash[hashFunctionForAdmin(current->topic)] == 0)
        {
            strcpy(str[i], current->topic);
            printf("[%d] - %s\n", ++i, current->topic);
            hash[hashFunctionForAdmin(current->topic)] = 1;
        }
        current = current->next;
    }

    printf("[%d] - Back to main menu\n", ++i);

    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == i)
        return NULL;
    else
    {
        strcpy(name, str[choice - 1]);
        return name;
    }
}

/**
 * The print_questions is a function that takes a double pointer to a linked list of data structures and a string as input.
 * It prints all the questions in the linked list that match the given category and prompts the user to select a
 * question by entering a number.
 *
 * @param head A double pointer to a linked list of data structures.
 * @param category A string that represents the category of the questions to be printed.
 *
 * @return It returns the question number of the selected question or -1 if the user chooses to go back.
 */

int print_questions(data **head, const char *category)
{
    int i = 0;
    int ch;
    int ctr = count(head);
    int qs_no[ctr];
    data *current = *head;

    if (head == NULL)
    {
        printf("List is empty\n");
        return -1;
    }

    printf("---------------------------------------\n");
    printf("                QUESTIONS\n");
    printf("---------------------------------------\n");

    while (current != NULL)
    {
        // Prints each node by incrementing pointer
        if (strcmp(current->topic, category) == 0)
        {
            qs_no[i] = current->qs_no;
            printf("[%d] = Q[%d]: %s\n", ++i, current->qs_no, current->question);
        }
        current = current->next;
    }

    printf("[%d] - Back\n", ++i);
    printf("\nEnter choice: ");
    scanf("%d", &ch);

    // printf("Before Passing: %d\n", i);
    // printf("Before Passing: %d\n", qs_no[ch - 1]);

    if (ch == i)
        return -1;
    else
        return qs_no[ch - 1];
}

/**
 * The update_trivia is a function that takes a double pointer to a linked list of data structures and an integer as input.
 * It prints the trivia question with the given question number and prompts the user to select a field to update.
 * It then prompts the user to enter the new value for the selected field.
 * It then prints the new value of the selected field.
 * If the user chooses to go back, it prints a message and returns.
 * If the user enters an invalid choice, it prints a message and returns.
 * If the user enters an invalid question number, it prints a message and returns.
 * If the linked list is empty, it prints a message and returns.
 *
 * @param head A double pointer to a linked list of data structures.
 * @param qs_no An integer that represents the question number of the trivia question to be updated.
 *
 * @return It returns nothing.
 */

void update_trivia(data **head, int qs_no, const char *category)
{
    int ch;
    data *current = *head;

    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    printf("---------------------------------------\n");
    printf("             TRIVIA QUESTION\n");
    printf("---------------------------------------\n");

    while (current != NULL)
    {
        // Prints each node by incrementing pointer
        if (current->qs_no == qs_no && strcmp(current->topic, category) == 0)
        {
            printf("[1] - TOPIC: %s\n", current->topic);
            printf("[2] - QUESTION: %s\n", current->question);
            printf("[3] - CHOICE 1: %s\n", current->choice[0]);
            printf("[4] - CHOICE 2: %s\n", current->choice[1]);
            printf("[5] - CHOICE 3: %s\n", current->choice[2]);
            printf("[6] - ANSWER: %s\n", current->answer);
            printf("[7] - BACK \n");

            printf("\nEnter choice: ");
            scanf("%d", &ch);

            switch (ch)
            {
            case 1:
                printf("Enter new topic: ");
                fflush(stdin);
                gets(current->topic);
                printf("NEW TOPIC: %s\n\n", current->topic);
                break;
            case 2:
                printf("Enter new question: ");
                fflush(stdin);
                gets(current->question);
                printf("NEW QUESTION: %s\n\n", current->question);
                break;
            case 3:
                printf("Enter new choice 1: ");
                fflush(stdin);
                gets(current->choice[0]);
                printf("NEW CHOICE 1: %s\n\n", current->choice[0]);
                break;
            case 4:
                printf("Enter new choice 2: ");
                fflush(stdin);
                gets(current->choice[1]);
                printf("NEW CHOICE 2: %s\n\n", current->choice[1]);
                break;
            case 5:
                printf("Enter new choice 3: ");
                fflush(stdin);
                gets(current->choice[2]);
                printf("NEW CHOICE 3: %s\n\n", current->choice[2]);
                break;
            case 6:
                printf("Enter new answer: ");
                fflush(stdin);
                gets(current->answer);
                printf("NEW ANSWER: %s\n\n", current->answer);
                break;
            case 7:
                break;
            default:
                printf("Invalid input! Try again!\n");

                *head = current;
            }
        }
        current = current->next;
    }
}

/**
 * The delete_trivia is a function that takes a double pointer to a linked list of data structures and an integer as input.
 * It deletes the trivia question with the given question number from the linked list.
 * If the user enters an invalid question number, it prints a message and returns.
 * If the linked list is empty, it prints a message and returns.
 *
 * @param head A double pointer to a linked list of data structures.
 * @param qs_no An integer that represents the question number of the trivia question to be deleted.
 *
 * @return It returns nothing.
 */

void delete_trivia(data **head, int qs_no, const char *category)
{
    data *temp = *head;

    if (temp != NULL && temp->qs_no == qs_no && strcmp(temp->topic, category) == 0)
    {
        *head = temp->next; // Changed head
        free(temp);         // free old head
    }
    else
    {
        data *current = *head;

        // Search for the key to be deleted, keep track of the
        // previous node as we need to change 'prev->next'
        while (current != NULL)
        {
            if (current->next->qs_no == qs_no && strcmp(current->next->topic, category) == 0)
            {
                temp = current->next;
                current->next = current->next->next;
                free(temp);
                return;
            }

            current = current->next;
        }
    }
}

/**
 * The display is a function that takes a double pointer to a linked list of data structures as input.
 * It prints the trivia questions in the linked list.
 * If the linked list is empty, it prints a message and returns.
 *
 * @param head A double pointer to a linked list of data structures.
 *
 * @return It returns nothing.
 */

void display(data **head)
{
    // Node current will point to head
    data *current = *head;

    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    printf("Nodes of singly linked list: \n");
    while (current != NULL)
    {
        // Prints each node by incrementing pointer
        printf("Topic: %s\n", current->topic);
        printf("Question Number: %d\n", current->qs_no);
        printf("Question: %s\n", current->question);
        printf("Choice 1: %s\n", current->choice[0]);
        printf("Choice 2: %s\n", current->choice[1]);
        printf("Choice 3: %s\n", current->choice[2]);
        printf("Answer: %s\n", current->answer);
        current = current->next;
    }
    printf("\n");
}

/**
 * The function "checkQNum" purpose is takes a double pointer to a struct called "data" and a pointer to a
 * character array called "topic" as input parameters. It checks the number of nodes in the linked list
 * that have the same topic as the input "topic" and returns the count.
 * If the linked list is empty, it prints a message "List is empty" and returns 1.
 *
 * @param head A double pointer to a linked list of data structures.
 * @param topic A pointer to a character array that represents the topic of the trivia question.
 *
 * @return It returns an integer that represents the number of nodes in the linked list that have the same topic as the input "topic".
 */

int checkQNum(data **head, char *topic)
{
    data *current = *head;
    int i = 1;

    if (head == NULL)
    {
        printf("List is empty\n");
        return 1;
    }

    while (current != NULL)
    {
        // Prints each node by incrementing pointer
        if (strcmp(current->topic, topic) == 0)
            i++;

        current = current->next;
    }

    return i;
}

/**
 * The function "checkDuplicate" purpose is takes a double pointer to a struct called "data" and a pointer to a
 * struct called "dt" as input parameters. It checks the linked list for duplicate trivia questions and returns 1 if there is a duplicate.
 * If the linked list is empty, it prints a message "List is empty" and returns 0.
 *
 * @param head A double pointer to a linked list of data structures.
 * @param dt A pointer to a struct called "dt".
 *
 * @return It returns an integer that represents 1 if there is a duplicate and 0 if there is no duplicate.
 */

int checkDuplicate(data **head, data *dt)
{
    data *current = *head;
    int i = 1;

    if (head == NULL)
    {
        printf("List is empty\n");
        return 0;
    }

    while (current != NULL)
    {
        // Prints each node by incrementing pointer
        if (strcmp(current->question, dt->question) == 0 && strcmp(current->answer, dt->answer) == 0 && strcmp(current->topic, dt->topic) == 0)
            return 1;

        current = current->next;
    }

    return 0;
}

/**
 * The function "add" purpose is takes a double pointer to a struct called "data" as input parameters. It adds a new trivia question to the linked list.
 * If the linked list is empty, it prints a message "List is empty" and returns 0.
 *
 * @param head A double pointer to a linked list of data structures.
 *
 * @return It returns nothing.
 */

void add(data **head)
{
    data *dt = (data *)malloc(sizeof(data));

    fflush(stdin);

    printf("Enter topic: ");
    gets(dt->topic);

    fflush(stdin);

    dt->qs_no = checkQNum(head, dt->topic);

    fflush(stdin);

    printf("Enter question: ");
    gets(dt->question);

    fflush(stdin);

    printf("Choice 1: ");
    gets(dt->choice[0]);

    fflush(stdin);

    printf("Choice 2: ");
    gets(dt->choice[1]);

    fflush(stdin);

    printf("Choice 3: ");
    gets(dt->choice[2]);

    fflush(stdin);

    printf("Answer: ");
    gets(dt->answer);

    dt->next = NULL;

    if (!(checkDuplicate(head, dt)))
    {
        if (*head == NULL)
        {
            // printf("hehe");
            *head = dt;
        }
        else
        {
            // printf("hoho");
            data *curr = *head;

            while (curr->next != NULL)
            {
                curr = curr->next;
            }

            curr->next = dt;
        }

        printf("Question added successfully!\n");
    }
    else
    {
        printf("Duplicate question detected! Please try again!\n");
    }
}

/**
 * The above code is a function named "import" that reads data from a text file and creates a linked list of "data" structures.
 * The function prompts the user to enter a filename, opens the file, and reads the contents line by line.
 * It then stores the data in an array of "arr" structures.
 * The "arr" structure contains fields for topic, question number, question, three choices, and answer.
 * The function then creates a "data" structure for each set of data in the array and adds it to the linked list if it is not a duplicate.
 *
 * @param head A double pointer to a linked list of data structures.
 *
 * @return It returns nothing.
 */

void import(data **head)
{
    FILE *fp;
    char str[255];
    arr triv[100];
    int i = 0, j = 0;
    data *dt;
    char filename[255];

    printf("Enter filename: ");
    fflush(stdin);
    gets(filename);

    fp = fopen(strcat(filename, ".txt"), "r");

    if (fp != NULL)
    {
        while (fgets(str, 255, fp) != NULL)
        {
            str[strcspn(str, "\n")] = 0;
            if (strcmp(str, "") == 0)
            {
                i = 0;
                j++;
            }
            else
            {
                // printf("%s\n", str);
                switch (i)
                {
                case 0:
                    strcpy(triv[j].topic, str);
                    break;
                case 1:
                    triv[j].qs_no = atoi(str);
                    break;
                case 2:
                    strcpy(triv[j].question, str);
                    break;
                case 3:
                    strcpy(triv[j].choice[0], str);
                    break;
                case 4:
                    strcpy(triv[j].choice[1], str);
                    break;
                case 5:
                    strcpy(triv[j].choice[2], str);
                    break;
                case 6:
                    strcpy(triv[j].answer, str);
                    break;
                }

                i++;
            }
        }

        // for(int k = 0; k < j; k++){
        //     printf("Topic: %s\n", triv[k].topic);
        //     printf("Question Number: %d\n", triv[k].qs_no);
        //     printf("Question: %s\n", triv[k].question);
        //     printf("Choice 1: %s\n", triv[k].choice[0]);
        //     printf("Choice 2: %s\n", triv[k].choice[1]);
        //     printf("Choice 3: %s\n", triv[k].choice[2]);
        //     printf("Answer: %s\n", triv[k].answer);
        // }

        for (int k = 0; k < j; k++)
        {
            dt = (data *)malloc(sizeof(data));
            strcpy(dt->topic, triv[k].topic);
            dt->qs_no = triv[k].qs_no;
            strcpy(dt->question, triv[k].question);
            strcpy(dt->choice[0], triv[k].choice[0]);
            strcpy(dt->choice[1], triv[k].choice[1]);
            strcpy(dt->choice[2], triv[k].choice[2]);
            strcpy(dt->answer, triv[k].answer);
            dt->next = NULL;

            if (!(checkDuplicate(head, dt)))
            {
                if (*head == NULL)
                {
                    // printf("hehe");
                    *head = dt;
                }
                else
                {
                    // printf("hoho");
                    data *curr = *head;

                    while (curr->next != NULL)
                    {
                        curr = curr->next;
                    }

                    curr->next = dt;
                }

                printf("Imported Question added successfully!\n");
            }
            else
            {
                printf("Duplicate question detected! Please try again!\n");
            }
        }
    }
    else
    {
        printf("File not found!\n");
    }

    fclose(fp);
}

/**
 * The above code is a function named "export" that writes data from a linked list of "data" structures to a text file.
 * The function prompts the user to enter a filename, opens the file, and writes the contents line by line.
 * It then stores the data in an array of "arr" structures.
 * The "arr" structure contains fields for topic, question number, question, three choices, and answer.
 * The function then creates a "data" structure for each set of data in the array and adds it to the linked list if it is not a duplicate.
 *
 * @param head A double pointer to a linked list of data structures.
 *
 * @return filename.
 */

const char *export(data **head)
{
    FILE *fp;
    data *curr = *head;
    char *filename = malloc(30 * sizeof(char));

    do
    {
        printf("Enter filename: ");
        fflush(stdin);
        gets(filename);

        if (strlen(filename) > 26)
        {
            printf("Filename too long!\n");
        }
        else
        {
            printf("Filename: %s\n", filename);
            fp = fopen(strcat(filename, ".txt"), "w");

            if (curr != NULL)
            {
                while (curr != NULL)
                {
                    fprintf(fp, "%s\n%d\n%s\n%s\n%s\n%s\n%s\n\n", curr->topic, curr->qs_no, curr->question, curr->choice[0], curr->choice[1], curr->choice[2], curr->answer);
                    curr = curr->next;
                }

                printf("Exported Data successfully!\n");
            }
            else
            {
                printf("Data is empty! Add trivia first before it exports!\n");
            }

            fclose(fp);
        }
    } while (strlen(filename) > 26);

    return filename;
}