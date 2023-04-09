/**
 * This code is defining a struct named `Data` which contains fields for a
 * topic (a string of up to 20 characters),
 * a question number (an integer),
 * a question (a string of up to 150 characters),
 * three choices (each a string of up to 30 characters),
 * and an answer (a string of up to 30 characters).
 *
 * It also contains a pointer to another `Data` struct named `next`.
 * Therefore, it is a linked list data structure.
 */
typedef struct Data
{
    char topic[20];
    int qs_no;
    char question[150];
    char choice[3][30];
    char answer[30];

    struct Data *next;
} data;

/**
 * This code is defining a struct named `Arr` which contains fields for a
 * topic (a string of up to 20 characters),
 * a question number (an integer),
 * a question (a string of up to 150 characters),
 * three choices (each a string of up to 30 characters),
 * and an answer (a string of up to 30 characters).
 *
 * However, unlike the `Data` struct, it does not contain a pointer to another `Arr` struct.
 * Additionally, it is using `typedef` to create an alias for the `struct Arr` as `arr`..
 */
typedef struct Arr
{
    char topic[20];
    int qs_no;
    char question[150];
    char choice[3][30];
    char answer[30];
} arr;
