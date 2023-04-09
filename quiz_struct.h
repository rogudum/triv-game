/**
 * This code is defining a struct named `Player` which contains fields for a
 * name (a string of up to 20 characters),
 * a score (an integer),
 * and a pointer to another `Player` struct named `next`.
 * Therefore, it is a linked list data structure..
 */
typedef struct Player
{
    char name[20];
    int score;

    struct Player *next;
} player;

/**
 * This code is defining a struct named `ArrPlayer` which contains fields for a
 * name (a string of up to 20 characters),
 * and a score (an integer).
*/
typedef struct ArrPlayer{
    char name[20];
    int score;
} arrPlayer;