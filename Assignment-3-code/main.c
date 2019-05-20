/*******************************************************************************
 * MASTER
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "interface.h"

#define MAX_NO_ITEMS 9
#define MAX_NO_FIRSTNAME 20
#define MAX_NO_LASTNAME 20
#define MAX_NO_FULLNAME 40
#define MAX_NO_CARDNUMBER 20
#define MAX_NO_STUDENT_ID 8
#define MAX_NO_USERS 5
#define MAX_NO_PASSWORD 10
#define MAX_NO_ITEM_NAME 10
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


/*******************************************************************************
 * Main
 * Authors: Everyone
*******************************************************************************/
int main (void)
{
    intro_prompt();

    int selection = getChoice();

    if(selection == -1) {                 /*If invalid selection, back to menu*/
      main();
    }

    inputCases(selection);           /*Goes through the options based on input*/
    return 0;
}
