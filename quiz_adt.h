#include "quiz_struct.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100    // Maximum size of the hash table

/**
 * The above code is implementing a function called `splitList` that 
 * takes a pointer to the head of a linked list of players and two 
 * double pointers to player nodes.
 *  
 * The function splits the linked list into two halves and assigns the 
 * left half to the first double pointer and the right half to the second 
 * double pointer.
 * 
 * @param source A pointer to the head of a linked list of players.
 * @param leftRef A double pointer to a player node.
 * @param rightRef A double pointer to a player node.
 * 
 * @return void
 */
void splitList(player *source, player **leftRef, player **rightRef)
{
    player *slow = source;
    player *fast = source->next;

    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *leftRef = source;
    *rightRef = slow->next;
    slow->next = NULL;
}

/**
 * The above code is implementing a merge function for merging two 
 * linked lists of players based on their scores. It takes two player 
 * pointers as input, left and right, and recursively merges them 
 * into a single linked list based on the score of each player. 
 * 
 * The function returns a player pointer to the merged linked list.
 * 
 * @param left A pointer to a player node.
 * @param right A pointer to a player node.
 * 
 * @return player* sorted list
 */
player *merge(player *left, player *right)
{
    player *result = NULL;

    if (left == NULL)
        return right;

    if (right == NULL)
        return left;

    if (left->score >= right->score)
    {
        result = left;
        result->next = merge(left->next, right);
    }
    else
    {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
}

/**
 * The above code is implementing a function called `sort` that takes a
 * double pointer to the head of a linked list of players and sorts the
 * linked list based on the score of each player.
 * 
 * @param headRef A double pointer to the head of a linked list of players.
 * 
 * @return void
*/
void sort(player **headRef)
{
    player *head = *headRef;
    player *left;
    player *right;

    if (head == NULL || head->next == NULL)
        return;

    splitList(head, &left, &right);

    sort(&left);
    sort(&right);

    *headRef = merge(left, right);
}

/**
 * The above code defines a function named "printLeaderboards" 
 * that takes a double pointer to a "player" struct as an argument. 
 * It then initializes a pointer "current" to the head of the 
 * linked list and an integer "i" to 1.
 * 
 * The function then checks if the linked list is empty. If it is,
 * it prints "List is empty" and returns. Otherwise, it prints the
 * name and score of each player in the linked list.
 * 
 * @param head A double pointer to the head of a linked list of players.
 * @return void
 */
void printLeaderboards(player **head)
{
    player *current = *head;
    int i = 1;

    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    while (current != NULL)
    {
        // Prints each node by incrementing pointer
        printf("%d. %s - %d\n", i, current->name, current->score);
        current = current->next;
        i++;
    }
}

/**
 * The above code is a function that checks if a player with 
 * the same name as the given player already exists in a 
 * linked list. It takes a double pointer to the head of the 
 * linked list and a pointer to the player to be checked as 
 * input. It then iterates through the linked list and compares 
 * the name of each player with the name of the given player. 
 * If a player with the same name is found, it returns 1 indicating 
 * that a duplicate player exists. If the end of the linked list 
 * is reached without finding a duplicate player, it returns 0 
 * indicating that the given player is not
 * 
 * @param head A double pointer to the head of a linked list of players.
 * @param dt A pointer to a player node.
 * 
 * @return int 1 if duplicate player exists, 0 otherwise
 */
int checkDupPlayer(player **head, player *dt)
{
    player *current = *head;
    int i = 1;

    if (head == NULL)
    {
        printf("List is empty\n");
        return 0;
    }

    while (current != NULL)
    {
        // Prints each node by incrementing pointer
        if (strcmp(current->name, dt->name) == 0)
            return 1;

        current = current->next;
    }

    return 0;
}

/**
 * The above code is a function named `loadFile` that reads data 
 * from a file named "score.txt" and stores it in a linked list 
 * of player structures. The function reads the file line by 
 * line and separates the data into name and score fields. 
 * It then creates a new player node for each set of data and 
 * adds it to the linked list if it is not a duplicate. 
 * The function also handles cases where the file is not found.
 * 
 * @param node A double pointer to the head of a linked list of players.
 * @return void
 */
void loadFile(player **node)
{
    FILE *fp;
    char str[255];
    arrPlayer arr_player[100];
    int i = 0, j = 0;
    player *pl;

    fp = fopen("score.txt", "r");

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
                    strcpy(arr_player[j].name, str);
                    break;
                case 1:
                    arr_player[j].score = atoi(str);
                    break;
                }

                i++;
            }
        }

        for (int k = 0; k < j; k++)
        {
            pl = (player *)malloc(sizeof(player));
            strcpy(pl->name, arr_player[k].name);
            pl->score = arr_player[k].score;
            pl->next = NULL;

            if (!(checkDupPlayer(node, pl)))
            {
                if (*node == NULL)
                {
                    // printf("hehe");
                    *node = pl;
                }
                else
                {
                    // printf("hoho");
                    player *curr = *node;

                    while (curr->next != NULL)
                    {
                        curr = curr->next;
                    }

                    curr->next = pl;
                }
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
 * The above code defines a function named "saveFile" that 
 * takes a double pointer to a "player" struct as its parameter. 
 * The function opens a file named "score.txt" in write mode 
 * and writes the name and score of each player in the linked 
 * list to the file. It then closes the file.
 * 
 * @param node A double pointer to the head of a linked list of players.
 * @return void
 */
void saveFile(player **node)
{
    FILE *fp;
    player *current = *node;

    fp = fopen("score.txt", "w");

    if (fp != NULL)
    {
        while (current != NULL)
        {
            // Prints each node by incrementing pointer
            fprintf(fp, "%s\n%d\n\n", current->name, current->score);
            current = current->next;
        }
    }

    fclose(fp);
}

/**
 * The above code is a function that prompts the user to enter 
 * their name and creates a new player node with the entered 
 * name. It then checks if the player already exists in the 
 * linked list of players. If the player does not exist, the 
 * new player node is added to the end of the linked list. 
 * If the player already exists, the function returns the 
 * existing player node.
 * 
 * @param node A double pointer to the head of a linked list of players.
 * @return player* A pointer to the player node.
 */
player *getName(player **node)
{
    player *pl = (player *)malloc(sizeof(player));
    printf("Enter your name: ");
    scanf("%s", pl->name);

    if (!(checkDupPlayer(node, pl)))
    {
        pl->score = 0;
        pl->next = NULL;

        if (*node == NULL)
        {
            // printf("hehe");
            *node = pl;
        }
        else
        {
            // printf("hoho");
            player *curr = *node;

            while (curr->next != NULL)
            {
                curr = curr->next;
            }

            curr->next = pl;
        }

        return pl;
    }
    else
    {
        player *current = *node;

        while (current != NULL)
        {
            // Prints each node by incrementing pointer
            if (strcmp(current->name, pl->name) == 0)
                return current;

            current = current->next;
        }
    }
}

/**
 * The above code is implementing a hash function that takes 
 * a string (char array) as input and returns an integer 
 * value as the hash code. The function calculates the hash 
 * code by summing up the ASCII values of all the characters 
 * in the input string and then taking the modulo of the sum 
 * with a predefined constant MAX_SIZE. This ensures that 
 * the hash code falls within the range of 0 to MAX_SIZE-1.
 * 
 * @param key A string (char array) to be hashed.
 * @return int The hash code of the input string.
 */
int hashFunction(char *key)
{
    int sum = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        sum += key[i];
    }
    return sum % MAX_SIZE;
}

/**
 * The above code is a function that takes a pointer to a 
 * pointer of a data structure called "data" as input. 
 * It iterates through the linked list starting from the 
 * head and prints out the distinct topics found in the 
 * "topic" field of each node. It uses a hash table to 
 * keep track of the topics that have already been printed. 
 * The user is prompted to select a topic from the list 
 * or to go back to the main menu. If the user selects a 
 * topic, the function returns a dynamically allocated 
 * string containing the selected topic. If the user chooses 
 * to go back to the main menu,
 * 
 * @param head A pointer to a pointer to the head of a linked list of data.
 * @return char* A pointer to a dynamically allocated string containing the selected topic.
 */
const char *printDistinctTopics(data **head)
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
        if (hash[hashFunction(current->topic)] == 0)
        {
            strcpy(str[i], current->topic);
            printf("[%d] - %s\n", ++i, current->topic);
            hash[hashFunction(current->topic)] = 1;
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
 * The above code defines a function named "randomize" that 
 * takes two integer parameters "min" and "max". The function 
 * generates a random integer between "min" and "max" (inclusive) 
 * using the srand and rand functions from the cstdlib library 
 * and the time function from the ctime library. 
 * The generated random number is then returned by the function.
 * 
 * @param min The minimum value of the random number.
 * @param max The maximum value of the random number.
 * @return int The generated random number.
 */
int randomize(int min, int max)
{
    srand(time(0));
    int num = (rand() % (max - min + 1)) + min;

    return num;
}

/**
 * The above code is a function that takes a double pointer 
 * to a linked list of data structures and a string representing 
 * a category as input. It then iterates through the linked list 
 * and stores the question numbers of all the questions in the 
 * specified category in an array. It then generates a random 
 * number within the range of the indices of the array and returns 
 * the data structure corresponding to the randomly selected 
 * question number.
 * 
 * @param head A double pointer to the head of a linked list of data.
 * @param category A string representing the category of the question.
 * @return data* A pointer to the data structure corresponding to the randomly selected question.
 */
data *pick_question(data **head, const char *category)
{
    data *current = *head;
    data *temp = *head;

    int arr[255], i = 0;
    // variable to store the minimum
    // and maximum element
    int min = arr[0], max = arr[0];
    int size = 0, randomNum;

    while (current != NULL)
    {
        if (strcmp(current->topic, category) == 0)
        {
            arr[i] = current->qs_no;
            i++;
        }

        current = current->next;
    }

    // for (int j = 0; j < i; j++)
    // {
    //     printf("[%d] = %d\n", j, arr[j]);
    // }

    size = i;

    // printf("Size: %d\n", size);

    // printf("Min: %d\n", min);
    // printf("Max: %d\n", max);
    if (size == 1)
    {
        randomNum = arr[0];
    }
    else
    {
        randomNum = arr[randomize(1, size - 1)];
    }

    //printf("Random: %d\n", randomNum);

    while (temp != NULL)
    {
        if (strcmp(temp->topic, category) == 0 && temp->qs_no == randomNum)
        {
            return temp;
        }

        temp = temp->next;
    }
}

/**
 * The above code is a function that deletes a node from a 
 * linked list of quiz trivia data. The function takes in a 
 * double pointer to the head of the linked list, an integer 
 * representing the question number, and a string representing 
 * the category of the quiz trivia.
 * 
 * @param head A double pointer to the head of a linked list of data.
 * @param qs_no An integer representing the question number.
 * @param category A string representing the category of the question.
 * 
 * @return void
 */
void delete_quiz_trivia(data **head, int qs_no, const char *category)
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
 * The above code defines a function named "play" that takes 
 * in a double pointer to a data structure and a pointer to a 
 * player structure. The function initializes the player's 
 * score to 0 and enters a loop that continues until there are 
 * no more distinct topics left to ask questions about.
 * 
 * @param head A double pointer to the head of a linked list of data.
 * @param pl A pointer to a player structure.
 * @return void
 */
void play(data **head, player **pl)
{
    player *current = *pl;
    const char *category;
    char ans;
    int qs_no;

    current->score = 0;

    do
    {
        printf("Name: %s\n", current->name);
        printf("Score: %d\n", current->score);

        category = printDistinctTopics(head);

        if (category != NULL)
        {
            // printf("After Passing: %s\n", category);
            data *topic = pick_question(head, category);
            printf("Question: %s\n", topic->question);
            printf("[A] - %s\n", topic->choice[0]);
            printf("[B] - %s\n", topic->choice[1]);
            printf("[C] - %s\n\n", topic->choice[2]);

            printf("Enter your answer [A/B/C]: ");
            scanf(" %c", &ans);

            switch (ans)
            {
            case 'A':
            case 'a':
                if (strcmp(topic->choice[0], topic->answer) == 0)
                {
                    printf("Correct Answer!\n");
                    current->score += 1;
                    delete_quiz_trivia(&*head, topic->qs_no, topic->topic);
                }
                else
                {
                    printf("Wrong Answer!\n");
                }
                break;
            case 'B':
            case 'b':
                if (strcmp(topic->choice[1], topic->answer) == 0)
                {
                    printf("Correct Answer!\n");
                    current->score += 1;
                    delete_quiz_trivia(head, topic->qs_no, topic->topic);
                }
                else
                {
                    printf("Wrong Answer!\n");
                }
                break;
            case 'C':
            case 'c':
                if (strcmp(topic->choice[2], topic->answer) == 0)
                {
                    printf("Correct Answer!\n");
                    current->score += 1;
                    delete_quiz_trivia(&*head, topic->qs_no, topic->topic);
                }
                else
                {
                    printf("Wrong Answer!\n");
                }
                break;
            default:
                printf("Invalid Input!\n");
            }
        }
    } while (category != NULL);
}

/**
 * The above code is a function that reads data from a 
 * text file and stores it in a linked list. The text file 
 * contains trivia questions and answers. The function 
 * reads each line of the file, separates the data into 
 * different fields, and stores it in an array of structures. 
 * It then creates a new node for each structure and adds 
 * it to the end of the linked list if it is not a duplicate. 
 * Finally, it closes the file.
 * 
 * @param head A double pointer to the head of a linked list of data.
 * @param filename A string representing the name of the text file.
 * @return void.
 */
void import_txtfile(data **head, const char *filename)
{
    FILE *fp;
    char str[255];
    arr triv[100];
    int i = 0, j = 0;
    data *dt;

    fp = fopen(filename, "r");

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

                // printf("Imported Question added successfully!\n");
            }
        }
    }
    else
    {
        printf("File not found!\n");
    }

    fclose(fp);
}