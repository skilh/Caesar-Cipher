//-----------------------------------------------------------------------------
// ass2.c
//
//
//Small program description:
//This program takes input from user from standard input.
//
//It accpets only small letters of english alphabet on input, spaces and maximum one newline!
//
//If input has been successfully read, programm process input and depending on
//number of encountered letters it encyripts input with key.
//Key is calculated as follows:
//       number of letters = x,
//       key = k,
//       k = 256 mod x.
//
//Key represents number of places for which one letter should be rotated within alphabet. 
//This process is also known as "Caesar cipher" 
//
//
// Authors: Ilhan Skender 1531567
//          Haris Hadzimahmutovic 01634756
// 
//-----------------------------------------------------------------------------
//
//Some definitions for readers and users of this code:
//
//@return -1
//If input is bigger than 255 than program returns -1,
//which means that too many characters are entered.
//It also prints an error message: "[ERR] too many characters\n"t.
//After that program ends.
//
//@return -2
//Program will return -2 if at least one uppercase character, number or other symbol
//is entered and prints an error message: "[ERR] invalid characters\n".
//After that program ends.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// defines size of array plain_text
#define MAX_STRING_SIZE 258    

//-----------------------------------------------------------------------------
///
/// They checks if input is consisted only of space characters. 
/// If input is consisted only out of spaces than variable "space_bool" 
///    will have value 1. Otherwise is stays 0. 
///
/// @param input_array[] place where we previously saved users's input
/// @param counter is number which holds lenght of input 
/// @param space_bool is used in function and it evalutes input as follows:
///         has value 0  -> input has at least one symbol different from ' '
///         has value 1  -> only ' ' (spaces) are in input. 
/// 
///@return int space_bool of evaluation
// 
int checkForSpaceInput(char input_array[], int counter)
{
  int space_bool = 0;
  for (int loop_counter = 0; loop_counter < counter; loop_counter++)
  {
    if ((int)input_array[0] == 32 && (int)input_array[loop_counter] ==  32)
      space_bool = 1;
    else
    {
      space_bool = 0;
      break;
    }
  }
  return space_bool;
}


int main()
{
  
  char plain_text[MAX_STRING_SIZE];
  char encrypted_text[256];

  long unsigned text_lenght;
  int shift;
  int space_counter = 0;
  int is_space_bool = 0;
  int position;
  int final_size_of_new_array;

// take user's input
  printf("plain text: ");

// store input from user
  fgets(plain_text, 258, stdin);
  text_lenght = strlen(plain_text) - 1;

// with if condition check if '\n' is the only character in user input
  if (text_lenght == 0 && (int)plain_text[0] == 10 )
  {
    printf("encrypted text: \n");
    return 0;
  }

// checks if the input from user was too big
  if (text_lenght > 255)
  {
    printf("[ERR] too many characters\n");
    return -1;
  }

// This part of code will evaluate if input is valid
// Note: Definition and meanings of errors and return values 
//       could be found at the very beggining of this file.
  for (int position = 0; position < text_lenght; position++)
  {
    if ((int)plain_text[position] < 97 && (int)plain_text[position] > 32)
    {
      printf("[ERR] invalid characters\n");
      return -2;
    }
    else if ((int)plain_text[position] < 32)
    {
      printf("[ERR] invalid characters\n");
      return -2;
    }
    else if ((int)plain_text[position] > 122)
    {
      printf("[ERR] invalid characters\n");
      return -2;
    }
  }

  is_space_bool = checkForSpaceInput(plain_text, text_lenght);
  if (is_space_bool == 1)
  {
    for (int loop_counter = 0; loop_counter < text_lenght; loop_counter++)
    {
      encrypted_text[loop_counter] = ' ';
    }
    encrypted_text[text_lenght] = '\0';
    printf("encrypted text: %s\n", encrypted_text);
    return 0;
  }

//checks for spaces in user input
  for (int position = 0; position < text_lenght; position++)
  {
    if ((int)plain_text[position] == 32)
      space_counter++;
  }

  text_lenght = text_lenght - space_counter;
  final_size_of_new_array = text_lenght + space_counter + 1;
  shift = 256 % text_lenght;

//checks if the shift(key) is equal to 0 and invert the text if that is the case
  if (shift == 0)
  {
    int reverse = 0;
    for (position = (text_lenght + space_counter); position >= 0; position--)
    {
      encrypted_text[reverse] = plain_text[position - 1];
      reverse++;
    }
  }
// if space was pressed in user input the program evens that place 
// where space was pressed in plain text with encrypted text    
// if any other valid character was pressed evens the character of encrypted text with our formula 
  else
  {
    for (position = 0; position < (text_lenght + space_counter); position++)
    {
      if ((int)plain_text[position] == 32)
      {
        encrypted_text[position] = plain_text[position];
      }
      else
      {
        encrypted_text[position] = (((int)plain_text[position] - 97 + shift)
                                                                  % 26) + 97;
      }
    } 
    encrypted_text[final_size_of_new_array - 1] = '\0';
  }
  printf("encrypted text: %s\n", encrypted_text);
  return 0;
}
