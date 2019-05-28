/*******************************************************************************
 * ADMIN - AUTHOR - TOM HARRIS
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_NO_FIRSTNAME 20
#define MAX_NO_LASTNAME 20
#define MAX_NO_FULLNAME 40
#define MAX_NO_STUDENT_ID 8
#define MAX_NO_USERS 5
#define MAX_NO_PASSWORD 10
#define STUDENT_DB_NAME "students"
#define TRANSACTION_DB_NAME "transactions"


void open_admin_prompt();
void search_for_student();
void stu_db_add(user_t users[]);
void print_transactions();
void edit_details();
int add_student();
int getChoice();
void inputCases (int input);
int valid_date(int month, int day, int year);
int valid_first_name(char first_name[]);
int valid_last_name(char last_name[]);
int is_digit(char user_id[]);
int admin_main(void);

int month, day, year;
user_t user, users[MAX_NO_USERS];
int num_students = 0;

int admin_main(void){
    open_admin_prompt();
    int selection = getChoice();
    if(selection == -1)
    {
        admin_main();
    }
    inputCases(selection);

    return 0;
}

int getChoice(){
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

void inputCases (int input)
{
    switch(input) {
      case 1:   break;
      case 2:   break;
      case 3:   add_student(); 
                admin_main();
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
            scanf("%d %d %d", &day, &month, &year);
            validFlag = valid_date(day, month, year);

            user.birthdate.day = day;
            user.birthdate.month = month;
            user.birthdate.year = year;
            }
        printf("Enter a new password\n");
        scanf("%s", user.password);


        users[num_students] = user;

        num_students = num_students + 1;

    }else 
    {
      printf("Cannot add more students - memory full\n");
    }
    admin_main();
}


int valid_date(int day, int month, int year){
  if(day < 1 || day > 31 ||month < 1 || month > 12 ||
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
    int i 	= 0;
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
    admin_main();
}
