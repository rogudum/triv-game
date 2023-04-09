#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include "admin_adt.h"

/**
 * `admin_menu()` is a function that displays a menu of options for managing data and prompts the user to enter a choice.
 * It returns the character entered by the user representing their choice.
 * The options include adding a record, editing a record, deleting a record, importing data, exporting data, and going back to the previous menu.
 *
 * @return char
 */

char admin_menu()
{
  char ch;

  printf("\n         MANAGE DATA\n");
  printf("-----------------------------\n");
  printf("      [A] - Add Record\n");
  printf("      [E] - Edit Record\n");
  printf("      [D] - Delete Record\n");
  printf("      [S] - Show Record\n");
  printf("      [I] - Import Data\n");
  printf("      [X] - Export Data\n");
  printf("      [B] - Back\n");
  printf("-----------------------------\n");
  printf("\nEnter your choice: ");
  scanf(" %c", &ch);

  return ch;
}

/**
 * `admin_choice()` is a function that takes a double pointer to a `data` struct as its parameter.
 * It displays a menu of options for managing data and prompts the user to enter a choice.
 * It then performs the corresponding action based on the user's choice.
 *
 * @param head A double pointer to a linked list of data structures.
 *
 * @return filename
 */

const char *admin_choice(data **head)
{
  int valid = 1;
  char choice;
  char YN, YN1;
  const char *category, *category1, *filename;
  int qs_no, res_delete = 0;

  do
  {
    choice = admin_menu();
    switch (choice)
    {
    case 'A':
    case 'a':
      add(&*head);
      break;
    case 'E':
    case 'e':
      do
      {
        category = printDistinctTopicsForAdmin(head);
        // printf("After Passing: %s\n", category);

        if (category != NULL)
        {
          // printf("After Passing: %s\n", category);

          qs_no = print_questions(head, category);
          //printf("After Passing: %d\n", qs_no);

          if (qs_no != -1)
            update_trivia(head, qs_no, category);
        }
      } while (category != NULL);
      break;
    case 'D':
    case 'd':
      do
      {
        YN = YN1 = 'N';
        category1 = printDistinctTopicsForAdmin(head);
        // printf("After Passing: %s\n", category);

        if (category1 != NULL)
        {
          // printf("After Passing: %s\n", category);

          qs_no = print_questions(head, category1);

          if (qs_no != -1)
          {
            //printf("After Passing: %d\n", qs_no);
            printf("Are you sure you want to delete Question # %d [Y/N]: ", qs_no);
            scanf(" %c", &YN);

            if (YN == 'Y' || YN == 'y')
            {
              delete_trivia(&*head, qs_no, category1);

              printf("Want to delete again? [Y/N]: ");
              scanf(" %c", &YN1);
            }
          }
        }
      } while (category1 != NULL && YN1 == 'Y' || YN1 == 'y');
      break;
    case 'S':
    case 's':
      display(head);
      break;
    case 'I':
    case 'i':
      import(&*head);
      break;
    case 'X':
    case 'x':
      filename = export(head);
      break;
    case 'B':
    case 'b':
      valid = 0;
      break;
    }
  } while (valid);

  return filename;
}

/**
 * `int password()` is a function that prompts the user to enter a password and hides the characters entered by printing asterisks instead.
 * It compares the entered password with a pre-defined password "password" and returns 1 if they match, indicating that the user has entered the correct password.
 * If the entered password does not match, the function returns 0, indicating that the user has entered the wrong password.
 * The function also limits the number of attempts to enter the correct password to three.
 *
 * @return boolean if password is correct or not.
 */

int password()
{
  int i = 0;                         // chances are up to 3; i is for iterator.
  char a, checkPin[10] = "password"; // a stores the character entered by the user, checkPin stores the user's pinNum
  char pin[10] = "\0";               // string is NULL.

  printf("Enter your password: ");

  while (1)
  {
    a = getch(); // catching the character and store in a
    if (a == 8 && i > 0)
    {                  // if user's entered input is backspace (8 as the ASCII Hex Value) and i is less than 0
      printf("\b \b"); // backspace character transfers the cursor one character back with or without deleting on different compilers.
      pin[i] = ' ';    // index position of i in pin stores the whitespace
      i--;             // i is decrement
    }
    if (a != '\r' && a != 8 && i < 10)
    {              // if a is not carriage return character (\r) and a is not a backspace character and i is less than 6.
      pin[i] = a;  // a is passed to pin with index i
      ++i;         // Pre-increment i.
      printf("*"); // Then, print asterisk in the console to make it hide.
    }
    if (a == '\r' || i == 10)
    {                // if a is equal to carriage return character (\r) or i is equal to 6 (as the limit of 6-DIGIT PIN)
      pin[i] = '\0'; // Last position of index[i] in pin is set as NULL character.
      if (strcmp(pin, checkPin) == 0)
      {           // comparing the strings of pin and checkpin (if it is same)
        return 1; // return 1 as the true value.
      }
      else
      { // if it is not same of string compare
        printf("\nWrong password! Try again!\n");
        return 0; // increment chance.
      }
    }
  }

  return 0;
}

/**
 * `int chances()` is a function that calls the `password()` function three times.
 * If the user enters the correct password, the function returns 1.
 * If the user enters the wrong password three times, the function returns 0.
 *
 * @return boolean if password is correct or not.
 */

int chances()
{
  int valid = 0, chance = 0;

  do
  {
    valid = password();

    if (valid)
      return 1;
    else
      ++chance;
  } while (chance != 3);

  return 0;
}
