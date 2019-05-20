/*******************************************************************************
 * Interface - David Bui
*******************************************************************************/

/*******************************************************************************
 * This prints the school logo.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

void print_logo(void){
  printf("_______________________________________"
"\n|            _ _.-^-._ _               |"
"\n|            ;.'________'.;            |"
"\n|_________n.[____________].n_________  |"
"\n||::_::_::_::||==||==||==||::_::_::_::]|"
"\n||:::::::::::||..||..||..||:::::::::::||"
"\n||=|= =|= =|=||==||==||==||=|= =|= =|=||"
"\n||.. .. .. ..||..||..||..||.. .. .. ..||"
"\n||** - **||::|LI=| __ |=LI|** - **||::||"
"\n|______________________________________|"
"\n           **UTS UNIFORM SHOP**"
"\n     -------------------------------\n");
}

/*******************************************************************************
 * This prints the inital welcome prompt.
*******************************************************************************/
void print_bold_magenta(){
  printf("\033[1;35m");
}

/*******************************************************************************
 * This prints the inital welcome prompt.
*******************************************************************************/
void print_magenta(){
  printf("\033[0;35m");
}

/*******************************************************************************
 * This prints the inital welcome prompt.
*******************************************************************************/
void print_reset_color(){
  printf("\033[0m");
}

/*******************************************************************************
 * This prints the inital welcome prompt.
*******************************************************************************/
void intro_prompt(void){
    print_bold_magenta();
    print_logo();
    printf("\n"
    "Welcome to UTS uniform order page\n"
    "1. Existing user\n"
    "2. New user\n"
    "3. Exit\n"
    "Enter choice 1 - 3>\n");
    print_reset_color();
}

/*******************************************************************************
 * Function Description
*******************************************************************************/
int getChoice(){
  int choice = 0;

  if (scanf("%d", &choice) == 1)                         /*if input is scanned*/
  {
    if(choice < 1 || choice > 3) {
      printf("Invalid choice\n");
      return -1;
    }

    else {
      return choice;                                      /*1-6 returns choice*/
    }
  }
  else return -1;                                   /*Logic for resetting main*/
}

void adminMenu (void) {
  printf("Admin Menu");
}

void userMenu (void) {
  printf("User Menu");
}

void inputCases (int input)
{
    switch(input) {                                   /*choose function to run*/
      case 1: adminMenu(); break;
      case 2: userMenu(); break;
      case 3: exit(0); break;
    }
}
