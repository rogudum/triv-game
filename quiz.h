#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include "quiz_adt.h"

/**
 * `trivia_menu()` is a function that displays a menu of options for
 * playing the trivia game and prompts the user to enter a choice.
 * It returns the character entered by the user representing their choice.
 * The options include playing the game, viewing the leaderboard, and exiting the game..
 *
 * @return char
 */
char trivia_menu()
{
  char ch;

  printf("\n         TRIVIA GAME\n");
  printf("-----------------------------\n");
  printf("      [P] - Play\n");
  printf("      [V] - View Scores\n");
  printf("      [E] - Exit\n");
  printf("-----------------------------\n");
  printf("\nEnter your choice: ");
  scanf(" %c", &ch);

  return ch;
}

/**
 * `trivia_choice()` is a function that allows the user to choose between playing
 * the trivia game, viewing the leaderboard, or exiting the game. It takes in a
 * double pointer to a player struct and a pointer to a constant character string
 * representing the filename.
 *
 * @param node A double pointer to a linked list of player structures.
 * @param filename A pointer to a constant character string representing the filename.
 *
 * @return void
 */
void trivia_choice(player **node, const char *filename)
{
  int valid = 1;
  char choice;

  // printf("Filename: %s\n", filename);
  data *head = NULL;
  loadFile(&*node);

  do
  {
    import_txtfile(&head, filename);
    sort(&*node);

    choice = trivia_menu();
    switch (choice)
    {
    case 'P':
    case 'p':
      player *pl = getName(&*node);
      play(&head, &pl);
      break;
    case 'V':
    case 'v':
      printLeaderboards(node);
      break;
    case 'E':
    case 'e':
      saveFile(node);
      free(*node);
      valid = 0;
      break;
    }

  } while (valid);
}
