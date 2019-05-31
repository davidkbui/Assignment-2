/*******************************************************************************
 * Interface - David Bui
*******************************************************************************/

/*******************************************************************************
 * This prints the school logo.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_logo(void){
  printf(
   "_______________________________________"
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
 * This changes text colors
*******************************************************************************/
void print_bold_magenta(){
  printf("\033[1;35m");
}

void print_bold_red(){
  printf("\033[0;31m");
}

void print_reset_color(){
  printf("\033[0m");
}

/*******************************************************************************
 * This prints the inital welcome prompts.
*******************************************************************************/

void intro_prompt(){
    print_bold_magenta();
    print_logo();
    printf("\n"
    "Welcome to UTS uniform order page\n"
    "1. Student\n"
    "2. Admin\n"
    "3. Exit\n"
    "Enter choice 1 - 3>\n");
    print_reset_color();
}

void item_prompt(){
    printf("\n"
    "Choose from options below\n"
    "1. Shirt-L\n"
    "2. Shirt-M\n"
    "3. Shirt-S\n"
    "4. Shorts-L\n"
    "5. Shorts-M\n"
    "6. Shorts-S\n"
    "Enter choice 1 - 6>\n");
}

void open_user_prompt(){
    printf("\n"
    "Welcome to UTS uniform order page\n"
    "1. Order uniform\n"
    "2. View your transaction\n"
    "3. View my details\n"
    "4. Update my payment details\n"
    "5. Exit\n"
    "Enter choice 1 - 5>\n");
}

void open_admin_prompt(){
    printf("\n"
    "Hello, You are in administration mode\n"
    "1. View all transactions\n"
    "2. Search for trasactions\n"
    "3. Search for student\n"
    "4. Add new student\n"
    "5. Exit\n"
    "Enter choice 1 - 5>\n");
}
