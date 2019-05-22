
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAX_NO_ITEMS 9
#define MAX_NO_FIRSTNAME 20
#define MAX_NO_LASTNAME 20
#define MAX_NO_FULLNAME 40
#define MAX_NO_CARDNUMBER 20
#define MAX_NO_STUDENT_ID 8
#define MAX_NO_USERS 5
#define MAX_NO_PASSWORD 10
#define MAX_NO_ITEM_NAME 10
#define DB_NAME "student_database"
#define STUDENT_DB_NAME "students"
#define TRANSACTION_DB_NAME "transactions"


/*******************************************************************************
 * Structs Defined Here
*******************************************************************************/

struct payment{
    char student_id[MAX_NO_STUDENT_ID];
    int card_number;
    char cardholder[MAX_NO_FULLNAME];
    int expiry;
    int CVC;
};
typedef struct payment payment_t;

struct date{
    int day;
    int month;
    int year;
};
typedef struct date date_t;

struct user{
    char first_name[MAX_NO_FIRSTNAME];
    char last_name[MAX_NO_LASTNAME];
    char user_id[MAX_NO_STUDENT_ID + 1];
    date_t birthdate;
    char password[MAX_NO_PASSWORD];
    int payment_valid;
    int is_admin;
};

typedef struct user user_t;

typedef struct admin admin_t;

struct transaction{
    int student_id;
    int transaction_id;
    date_t transaction_date;
};
typedef struct trasaction trasaction_t;

struct item{
    int item_id;
    char item_name[MAX_NO_ITEM_NAME];
    double item_price;
    char item_size;
};
typedef struct item item_t;







/*******************************************************************************
 * Function prototypes
*******************************************************************************/

void print_logo(void);
void intro_prompt(void);
void print_bold_magenta();
void print_magenta();
void print_reset_color();
void adminMenu();
void userMenu();
void inputCas();
int getChoice();
int matchID(char ID[10]);


void student_menu();
void check_my_details();
void update_my_details();
void view_my_transactions();
void inputCases (int selection);

void open_admin_prompt();
void search_for_student();
void stu_db_add(user_t users[]);
void print_transactions();
void edit_details();
int add_student();
int getChoiceAdmin();
void inputCasesAdmin (int input);
int valid_date(int month, int day, int year);
int valid_first_name(char first_name[]);
int valid_last_name(char last_name[]);
int is_digit(char user_id[]);

/*******************************************************************************
 * Main
 * Authors: Everyone
*******************************************************************************/
int month, day, year;
user_t user, users[MAX_NO_USERS];
int num_students = 0;
int main (void)
{
    intro_prompt();

    int selection = getChoice();

    if(selection == -1) {                 /*If invalid selection, back to menu*/
      main();
    }

    inputCas(selection);           /*Goes through the options based on input*/
    return 0;
}


/*******************************************************************************
 * Interface - David Bui
*******************************************************************************/

/*******************************************************************************
 * This prints the school logo.
*******************************************************************************/



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
    "1. Student\n"
    "2. Admin\n"
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

int matchID(char ID[10]) {
  int i; 
  int validFlag, p;
  p = strlen(ID);
  for (i=0; i<p; i++)
    {
      if (ID[i] >= '0' && ID[i] <= '9')
        {
          validFlag = 1;
        }
      else {
            printf("Invalid ID, try again\n");
            scanf("%s", ID);
            validFlag = 0;
      }
    }
  return validFlag;
  }

void adminMenu (void) {
  open_admin_prompt();
    int selection = getChoice();
    if(selection == -1)
    {
        adminMenu();
    }
    inputCasesAdmin(selection);
}

void studentMenu (void) {
  printf("-----------------");
    student_menu();
    int select;
    scanf("%d", &select);
    inputCases(select);
}

void inputCas (int input)
{
    switch(input) {                                   /*choose function to run*/
      case 1: studentMenu(); break;
      case 2: adminMenu(); break;
      case 3: exit(0); break;
    }
}



void student_menu()
{
    printf("\n"
    "Select an option\n"
    "1. Check My Details\n"
    "2. Update My payment details\n"
    "3. Coming Soon *View My Transactions*\n"
    "5. Exit\n"
    "Enter choice 1 - 4>\n");
}

/*******************************************************************************
 * This function reads the choice of the user and runs the case that corresponds
 to the user input.
 * outputs:
 * - cases
*******************************************************************************/
void inputCases (int selection)
{
    switch(selection) 
    {
      case 1: check_my_details(); break;
      case 2: update_my_details(); break;
      case 3: view_my_transactions(); break;
      case 4: exit(0); break;
    }
}

/*******************************************************************************
 * This function allows the user to edit and then update their details
 * in the database 
*******************************************************************************/
void check_my_details()
{
    FILE * fPtr;
    fPtr  = fopen(DB_NAME, "r");
    char ans[6];
    char line[20];
    int linenum =0;
    int foundline =(linenum) ;
    int lineStop = (foundline+5);

    /* return NULL if unable to open file. */
    if (fPtr == NULL)
    {
        printf("\nUnable to open file.\n");
        exit(EXIT_SUCCESS);
    }

    printf("Enter ID>\n");
    scanf ("%s", ans);
    while (fgets(line, sizeof line, fPtr) != NULL) 
    {   
          
        linenum++;
        if (strncmp(ans, line,5) ==0)
        {
            /*printf("Details found\n" );*/
            break;
        }
    
        }

   /* printf("User: %s \n",ans); */

    char student_details[256]; 
    while (fgets( student_details, sizeof  student_details, fPtr) != NULL) 
        {   
            if (foundline <= lineStop)
            {  
                printf("%s",  student_details);
                foundline++;
            }
            else
            {
                foundline++;
            }
        }

    /* Close file*/
    fclose(fPtr);

    studentMenu ();
}


/*******************************************************************************
 * This function allows the user to edit and then update their details
 * in the database 
*******************************************************************************/
void update_my_details(){

    printf("Needs Debugging\n");
    studentMenu ();


}


/*******************************************************************************
 * Function prints the history for either the day, month or year of previous 
 * transactions, depending on what the user has selected.
*******************************************************************************/

void view_my_transactions(){

       printf("Coming Soon>\n");
       studentMenu ();
    
}

int getChoiceAdmin(){
    int choice = 0;
    if (scanf("%d", &choice) == 1)
    {
        if(choice < 1 || choice > 6) {
        printf("Invalid choice\n");
          return -1;
        }

        else {
          return choice;
        }
      }

      else return -1;
}

void inputCasesAdmin (int input)
{
    switch(input) {
      case 1:   break;
      case 2:   break;
      case 3:   add_student(); 
                adminMenu();
                break;
      case 4:   break;
      case 5:   exit(0); break;
      case 6:   stu_db_add(users); break;
    }
}

/*******************************************************************************
 * This function prints the available options for the admin to chose from.
 * Author: Tom Harris
*******************************************************************************/

void open_admin_prompt(){
    printf("\n"
    "Hello, You are in administration mode\n"
    "1. View all transactions\n"
    "2. Search for transactions\n"
    "3. Add a new student\n"
    "4. Search for student\n"
    "5. Exit\n"
    "6. Save to database\n"
    "Enter choice 1 - 6>\n");   
}


/*******************************************************************************
 * This function adds a new student to the student database
 * Author: Tom Harris
*******************************************************************************/

int add_student(){
    printf("%d\n", num_students);


    if(num_students < MAX_NO_USERS)
    {
        int validFlag = 0;

        while(validFlag == 0) {
            printf("Enter your first name\n");
            scanf("%s", user.first_name);
            validFlag = valid_first_name(user.first_name);
        }
        validFlag = 0;
        while(validFlag == 0) {
            printf("Enter your last name\n");
            scanf("%s", user.last_name);
            validFlag = valid_last_name(user.last_name);
        }
        validFlag = 0;
        while(validFlag == 0) {
            printf("Enter your student ID\n");
            scanf("%s", user.user_id);
            validFlag = is_digit(user.user_id);
        }
        validFlag = 0;
        while(validFlag == 0){
            printf("Enter your birthdate in the format: DD MM YYYY (separated by spaces)\n");
            scanf("%02d %02d %04d", &day, &month, &year);
            validFlag = valid_date(day, month, year);

            user.birthdate.day = day;
            user.birthdate.month = month;
            user.birthdate.year = year;
            }
        printf("Enter a new password\n");
        scanf("%s", user.password);


        users[num_students] = user;

        num_students = num_students + 1;
        printf("%d\n", num_students);

    }else 
    {
      printf("Cannot add more students - memory full\n");
    }
    adminMenu();
}


int valid_date(int month, int day, int year){
  if(month < 1 || month > 12 || day < 1 || day > 31 ||
    year < 1900 || year > 2019) {
    printf("Invalid input\n");
    return 0;
  }
  return 1;
}

int valid_first_name(char first_name[]){
    if (strlen(user.first_name) < 2 || !(user.first_name[0] >= 'A' && user.first_name[0] <= 'Z')){
        printf("Invalid input\n");
        return 0;
    }
    return 1;
}

int valid_last_name(char last_name[]){
    if (strlen(user.last_name) < 2 || !(user.last_name[0] >= 'A' && user.last_name[0] <= 'Z')){
        printf("Invalid input\n");
        return 0;
    }
    return 1;
}

int is_digit(char user_id[]){
    int i;
    for (i = 0; i < strlen(user.user_id); i++){
        if((user.user_id[i] < '0' || user.user_id[i] > '9'))
        {
            printf("Invalid input\n");
            return 0;
        }
    }
    return 1;
}
/*******************************************************************************
 * Function prints new user information to a database text file
 * Author: Tom Harris
******************************************************************************/

void stu_db_add(user_t users[]){
    int i = 0;
    FILE *fp;
    fp = fopen(STUDENT_DB_NAME, "w");

     if(fp == NULL){
        printf("Write error\n");
    } 

    for(i = 0; i < MAX_NO_USERS; i++){
        fprintf(fp, "%s\n%s\n%s\n%02d\n%02d\n%04d\n%s\n",
               users[i].first_name, 
               users[i].last_name, 
               users[i].user_id,
               users[i].birthdate.day, 
               users[i].birthdate.month, 
               users[i].birthdate.year, 
               users[i].password);

    fclose(fp);
    }
    adminMenu();
}

