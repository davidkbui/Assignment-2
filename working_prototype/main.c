
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "compression.c"
#include "encryption.h"
#include "interface.h"

#define MAX_NO_ITEMS 6
#define MAX_NO_FIRSTNAME 15
#define MAX_NO_LASTNAME 15
#define MAX_NO_CARDNUMBER 20
#define MAX_NUM_TRANSACTIONS 20
#define MAX_NO_STUDENT_ID 8
#define MAX_NO_USERS 20
#define MAX_NO_PASSWORD 20
#define MAX_NO_ITEM_NAME 10
#define MAX_NO_CARD 16
#define MAX_NO_CVC 3
#define MAX_NO_PHONE 10
#define STUDENT_DB_NAME "student_database"

/*Insert structs here*/
struct payment{
    char card_number[MAX_NO_CARD+1];
    int month;
    int year;
    char cvc[MAX_NO_CVC+1];
};
typedef struct payment payment_t;

struct user{
    char first_name[MAX_NO_FIRSTNAME];
    char last_name[MAX_NO_LASTNAME];
    int user_id;
    char password[MAX_NO_PASSWORD];
    char phone[MAX_NO_PHONE+1];
    payment_t payment;
};
typedef struct user user_t;

/*functions*/
void login(user_t * users, int * no_of_user);
void login_as_admin(user_t *users, int * no_of_user);
int load_user(user_t *users_p, int * no_of_user);
void open_user_console(user_t user, user_t * users, int index, int * no_of_user);
void open_admin_console(user_t *users, int * no_of_user);
void order_uniform(user_t user);
void view_my_transaction(user_t user);
void view_transactions();
void search_transaction();
void search_student(user_t *users);
void update_prompt();
int load_payments(payment_t * payments);
int has_transaction(user_t user);
int check_user_input(const char *entered_id, int * login_id);
int is_right_format_number(char c);
int existing_student(int id, user_t * users);
int check_user_name(char * user_input, char * name);
void add_student(user_t *users, int * no_of_user);
int no_of_lines();
int save_student_db(const user_t *users_p, int * no_of_user);
void update_payment(user_t * users, int index, int * no_of_user);
void view_my_details(user_t * users, int index);
void center(char * s, int length, int width);
void expiry(char * expiry, int month, int year);
int check_card_number(char * user_input, char * card_number);
int check_year(char * user_input, int * year);
int check_month(char * user_input, int * month, int year);
int check_cvc(char * user_input, char * cvc);
void init_menu();

int main (void)
{
	init_menu();
    return 0;
}

int check_user_id_input(const char *entered_id, int * login_id){
    /* if user input is too long, format test fails */
    if(strlen(entered_id) > MAX_NO_STUDENT_ID + 1){
        return 0;
    }
    int i;
    char temp[MAX_NO_STUDENT_ID + 1];
    for(i = 0; i < MAX_NO_STUDENT_ID + 1; i++){
        temp[i] = entered_id[i];
    }
    for(i = 0; i < MAX_NO_STUDENT_ID ; i++){
        if(!is_right_format_number(temp[i])){
            return 0;
        }
    }
    sscanf(temp, "%d", login_id);
    return 1;
}

int is_right_format_number(char c){
    if((c >= '0' && c <= '9')){
       return 1;
    }
    return 0;
}

/*Insert function protoypes here*/
void login_as_admin(user_t *users, int *no_of_user) {
    char login_id[5];
    char password[MAX_NO_PASSWORD];
    int is_admin = 1;

    while(is_admin){
        printf("Enter your id \n");
        printf("(or enter EXIT to return back to Main Menu ) \n");

        scanf("%s", login_id);
        if(!strcmp(login_id, "admin")) { is_admin = 0; }
        else if (strcmp(login_id, "EXIT")==0) { return; }
        else { printf("Invalid admin username. Please check again! \n"); }
    }
    int right_password = 1;
    while(right_password){
        printf("Enter your password \n"
	"(or enter EXIT to return back to Main Menu )\n" );
        scanf("%s", password);
        if(!strcmp(password, "admin")){
            printf("Welcome, %s \n", "ADMIN");
            open_admin_console(users, no_of_user);
            right_password = 0;
        }
	else if (strcmp(password,"EXIT")){
		return;
	} else {
            printf("Invalid password. Please check again! \n");
        }
    }
}

void login(user_t * users, int * no_of_user) {
    char user_input[1000] = {};
    int login_id, i;
    char password[MAX_NO_PASSWORD];
    int existing_user = 1;
    user_t user;
    int index = 0;

    while ((getchar()) != '\n');
    while(existing_user){
        printf("Enter your id: \n");
        printf("(or enter EXIT to return back to Main Menu ) \n");

        fgets(user_input, 10000 ,stdin);

        if (strcmp(user_input, "EXIT")==10){
            return;
        }
        if(check_user_id_input(user_input, &login_id) == 1){
            for(i = 0; i < MAX_NO_USERS; i++){
                if(login_id == users[i].user_id){
                    user = users[i];
                    index = i;
                    existing_user = 0;
                }
            }
            if(user.user_id == '\0') {
                printf("Invalid user! \n");
            }
        } else {
            printf("Invalid ID\n");
        }
    }
    int right_password = 1;
    while(right_password){
        printf("Enter your password \n");
        scanf("%s", password);
        if(!strcmp(password, user.password)){
            printf("Welcome, %s \n", user.first_name);
            open_user_console(user, users, index, no_of_user);
            right_password = 0;
        } else {
            printf("Invalid password. Please check again! \n");
        }
    }
}



void open_user_console(user_t user, user_t * users, int index, int * no_of_user){
    int choice = 0;
    while(choice != 5){
        open_user_prompt();    /* print login prompt */
        if(scanf("%d", &choice) != 1){     /* if user input is NOT digit */
            while ((getchar()) != '\n');      /* flush input buffer */
            printf("Invalid choice \n");      /* prints error message */
        } else {     /* if user input is digit */
            switch(choice){
                case 1:
                    order_uniform(user);
                    break;
                case 2:
                    view_my_transaction(user);
                    break;
                case 3:
                    view_my_details(users, index);
                    break;
                case 4:
                    update_payment(users, index, no_of_user);
                    break;
                case 5:
                    break;
                default:      /* when user input is digit but not 1-5 */
                    printf("Invalid choice \n");
                    break;
            }
        }
    }
}

void open_admin_console(user_t *users, int *no_of_user){
    int choice = 0;
    while(choice != 5){
        open_admin_prompt();    /* print login prompt */
        if(scanf("%d", &choice) != 1){     /* if user input is NOT digit */
            while ((getchar()) != '\n');      /* flush input buffer */
            printf("Invalid choice \n");      /* prints error message */
        } else {     /* if user input is digit */
            switch(choice){
                case 1:
                    view_transactions();
                    break;
                case 2:
                    search_transaction();
                    break;
                case 3:
                    search_student(users);
                    break;
                case 4:
                    add_student(users, no_of_user);
                    break;
                case 5:
                    break;
                default:      /* when user input is digit but not 1-5 */
                    printf("Invalid choice \n");
                    break;
            }
        }
    }
}


int save_student_db(const user_t *users_p, int * no_of_user){
     /* Pointer to the file */
    FILE *fp;

     /* Opening a file in w mode*/
    fp = open_db();

    /* If there is issue opening file, print error message and finish */
    if(fp == NULL){
        printf("Write error\n");
        return 1;
    }

    /* int variable for for loop */
    int i;

    /* loop the number of flights and write to file in certain format,
        changing line with each flight  */
    for(i = 0; i < * no_of_user; i++){
        fprintf(fp, "%s %s %d %s %s %s %d %d %s\n",
               users_p[i].first_name, users_p[i].last_name, users_p[i].user_id,
               users_p[i].password, users_p[i].phone, users_p[i].payment.card_number, users_p[i].payment.month,
               users_p[i].payment.year, users_p[i].payment.cvc);
    }

    /* close file */
    fclose(fp);
    return 0;
}
/*****************************************************************************/
int load_user(user_t *users_p, int * no_of_user){
     /* Pointer to the file */
    FILE *fp;

     /* Opening a file in r mode */
	fp=open_db();

    /* If fp is NULL, print error message and finish */
    if(fp == NULL){
        printf("Students not loaded. Is database in right folder? \n");
        return 1;
    }

    /* variable for while loop */
    int i = 0;

    /* while incrementing i is not equal to no_of_lines which
        stores the number of new lines (=flights) in text file,	
        read from file and store that into flights array */
    while(i != no_of_lines()){
        fscanf(fp, "%s %s %d %s %s %s %d %d %s",
               users_p[i].first_name, users_p[i].last_name, &users_p[i].user_id, users_p[i].password, users_p[i].phone,
               users_p[i].payment.card_number, &users_p[i].payment.month, &users_p[i].payment.year,
               users_p[i].payment.cvc);
        i++;
    }
    *no_of_user = i;
    /* close file */
    open_db(open_db);
    return 0;
}

int no_of_lines(){
     /* Pointer to the file */
    FILE *fp;

     /* Opening a file in r mode */
    fp = fopen(STUDENT_DB_NAME, "r");

    /* If no file is found, return 0 */
    if(fp == NULL){
        return 0;
    }

    /* int variable to count number of lines in textfile */
    int count_lines = 0;

    /* char variable to store char from file */
    char chr = getc(fp);

   /* while chr variable is not at end of file, count all new line by
       counting '\n' and increment int variable count_lines by 1
       and reassign chr with next char */
    while (chr != EOF){
        if (chr == '\n'){
            count_lines++;
        }
        chr = getc(fp);
    }

    return count_lines;
}

void order_uniform(user_t user){
    if(has_transaction(user)){
        printf("Cannot make another transaction. You already made one transaction.\n");
        return;
    }
    char * item_name;
    int choice = 0;
    item_prompt();
    scanf("%d", &choice);
    switch(choice){
        case 1:
            item_name = (char*)malloc(sizeof(char) * 7);
            strcpy(item_name, "Shirt-L");
            break;
        case 2:
            item_name = (char*)malloc(sizeof(char) * 7);
            strcpy(item_name, "Shirt-M");
            break;
        case 3:
            item_name = (char*)malloc(sizeof(char) * 7);
            strcpy(item_name, "Shirt-S");
            break;
        case 4:
            item_name = (char*)malloc(sizeof(char) * 8);
            strcpy(item_name, "Shorts-L");
            break;
        case 5:
            item_name = (char*)malloc(sizeof(char) * 8);
            strcpy(item_name, "Shorts-M");
            break;
        case 6:
            item_name = (char*)malloc(sizeof(char) * 8);
            strcpy(item_name, "Shorts-S");
            break;
        default:      /* when user input is digit but not 1-5 */
            printf("Invalid choice \n");
            break;
    }

    int i, size = 0 ;
    transaction_t * transactions;
    transaction_t * temp;
    temp = read_database(&size);
    remove_database();
    transactions = (transaction_t*) malloc (sizeof(transaction_t) * (size + 1));
    for(i = 0 ; i < size; i++){
        transactions[i]= temp[i];
    }

    transaction_t transaction;
    transaction.user_id=  user.user_id;
    strcpy(transaction.item_name, item_name);
    transaction.quantity = 1;
    transactions[size] = transaction;

    code_t code[22];
    huffman(code);
    create_compression(code, transactions, size + 1);
}

void view_my_transaction(user_t user){
    if(!has_transaction(user)){
        printf("You have NO transaction yet.\n");
        return;
    }
    transaction_t * transactions;
    int i, size = 0;
    decompress_to_file();
    transactions = read_database(&size);
    remove_database();
    transaction_t transaction;
    for(i = 0 ; i < size; i++){
        if(user.user_id == transactions[i].user_id){
	    transaction = transactions[i];
        }
    }
	print_bold_magenta();
    printf("Item purchased  Quantity\n");
    printf("--------------- ---------------\n");
	print_reset_color();
    printf("%-15s %-15d\n",  transaction.item_name, transaction.quantity);
}

int has_transaction(user_t user){
    transaction_t * transactions;
    int i, size = 0;
    decompress_to_file();
    transactions = read_database(&size);
    for(i = 0 ; i < size; i++){
        if(user.user_id == transactions[i].user_id){
	    return 1;
        }
    }
    return 0;
}

void view_my_details(user_t * users, int index){
	print_bold_magenta();
    printf("PERSONAL DETAILS\n");
    printf("First Name      Last Name       Student ID      Phone Number \n");
    printf("--------------- --------------- --------------- --------------- \n");
	print_reset_color();
    printf("%-15s %-15s %-15d %-15s\n\n", users[index].first_name, users[index].last_name, users[index].user_id, users[index].phone);
    char expiry_date[6];
    expiry(expiry_date, users[index].payment.month, users[index].payment.year);
	print_bold_magenta();
    printf("PAYMENT DETAILS\n");
    printf("Card Number          Expiry Date     CVC \n");
    printf("-------------------- --------------- ------\n");
	print_reset_color();
    printf("%-20s %-15s %-5s\n",
             users[index].payment.card_number, expiry_date, users[index].payment.cvc);
}

void expiry(char * expiry, int month, int year){
    int i = 0;
    sprintf(&expiry[i], "%02d", month);
    strcat(expiry, "/");
    i = strlen(expiry);
    i += sprintf(&expiry[i], "%02d", year);
}

void view_transactions(){
    transaction_t * transactions;
    int i, size = 0;
    decompress_to_file();
    transactions = read_database(&size);
    remove_database();
	print_bold_magenta();
    printf("Transaction User ID  Item purchased  Quantity\n");
    printf("-------------------- --------------- ---------------\n");
	print_reset_color();
    for(i = 0 ; i < size; i++){
       printf("%-20d %-15s %-15d\n", transactions[i].user_id, transactions[i].item_name,
            transactions[i].quantity);
    }
}


void search_transaction(){
    printf("Enter the student ID:\n");
    int login_id;
    scanf("%d", &login_id);

    transaction_t * transactions;
    int i, size = 0;
    decompress_to_file();
    int has_item = 0;
    transactions = read_database(&size);
    remove_database();
    transaction_t transaction;
    for(i = 0 ; i < size; i++){
        if(login_id == transactions[i].user_id){
	    transaction = transactions[i];
            has_item = 1;
        }
    }
    if(has_item){
	print_bold_magenta();
        printf("Transaction User ID  Item purchased  Quantity\n");
        printf("-------------------- --------------- ---------------\n");
	print_reset_color();
        printf("%-20d %-15s %-15d\n", transaction.user_id, transaction.item_name,
            transaction.quantity);
    } else {
        printf("No transaction made by that student\n");
    }
}

void search_student(user_t *users){
    int search_id;
    int existing_user = 0;
    int i;
    user_t user;

    printf("Enter the student id:\n");
    scanf("%d", &search_id);
    for(i = 0 ; i < MAX_NO_USERS; i++){
        if(search_id == users[i].user_id){
            user = users[i];
            existing_user = 1;
        }
    }
    if(existing_user){
	print_bold_magenta();
        printf("First Name      Last Name       Student ID      Phone Number \n");
        printf("--------------- --------------- --------------- --------------- \n");
	print_reset_color();
        printf("%-15s %-15s %-15d %-15s\n", user.first_name, user.last_name, user.user_id, user.phone);
    } else {
        printf("No students in database\n");
    }
}

int existing_student(int id, user_t * users){
    int i;
    for(i = 0 ; i < MAX_NO_USERS; i++){
        if(id == users[i].user_id){
            return 1;
        }
    }
    return 0;
}

void add_student(user_t *users, int * no_of_user) {
    user_t new;
    int valid_id = 1;
    int valid_lastname = 1;
    int valid_firstname = 1;
    char user_input[1000] = {};
    int signup_id;
    char first_name[MAX_NO_FIRSTNAME];
    char last_name[MAX_NO_LASTNAME];
    printf("Number of students: %d ", *no_of_user);
    while ((getchar()) != '\n');
    while(valid_id){
        printf("Enter new student id:\n");
        fgets(user_input, 10000 ,stdin);
        if(check_user_id_input(user_input, &signup_id)){
            if(existing_student(signup_id, users)){
                printf("You already have that student in the database\n");
            } else {
                new.user_id = signup_id;
                valid_id = 0;
            }
        } else {
            printf("Your input is not valid\n");
        }
    }

    while(valid_firstname){
        printf("Enter first name:\n");
        fgets(user_input, 10000 ,stdin);
        if(check_user_name(user_input, first_name)){
            first_name[strlen(first_name)-1] ='\0';
            strcpy(new.first_name, first_name);
            valid_firstname = 0;
        } else {
            printf("Your input is not valid\n");
        }
    }
    while(valid_lastname){
        printf("Enter last name:\n");
        fgets(user_input, 10000 ,stdin);
        if(check_user_name(user_input, last_name)){
            last_name[strlen(last_name)-1] ='\0';
            strcpy(new.last_name, last_name);
            valid_lastname = 0;
        } else {
            printf("Your input is not valid\n");
        }
    }

    strcpy(new.phone, "0000000000");
    strcpy(new.payment.card_number, "0000000000000000");
    strcpy(new.payment.cvc, "000");
    new.payment.month = 0;
    new.payment.year = 0;
    strcpy(new.password, new.first_name);
    users[*no_of_user] = new;
    *no_of_user += 1;
    printf("%s %s", new.first_name, new.last_name);
    for(valid_id = 0; valid_id < *no_of_user; valid_id ++){
       printf("%-15s %-15s %-15d %-15s\n", users[valid_id].first_name, users[valid_id].last_name, users[valid_id].user_id, users[valid_id].phone);
    }
    save_student_db(users, no_of_user);
}

int check_user_name(char * user_input,char * name){
    if(strlen(user_input) > MAX_NO_LASTNAME + 1){
        return 0;
    }
    int i;
    if(user_input[0] >= 65 && user_input[0] <= 90){
        name[0] = user_input[0];
    } else if (user_input[0] >= 97 && user_input[0] <= 122){
        name[0] = user_input[0] - 32;
    } else {
       return 0;
    }

    for(i = 1; i < strlen(user_input) + 1; i++){
        if(user_input[i] >= 'A' && user_input[i] <= 'Z'){
            name[i] = user_input[i] + 32;
        } else if (user_input[i] >= 'a' && user_input[i] <= 'z'){
            name[i] = user_input[i];
        }
    }

    return 1;
}


void update_payment(user_t * users, int index, int * no_of_user){
    char expiry_date[6];
    expiry(expiry_date, users[index].payment.month, users[index].payment.year);

    while ((getchar()) != '\n');
    int valid_card_no = 1;
    int valid_month = 1;
    int valid_year = 1;
    int valid_cvc = 1;

    int month= 1;
    int year = 1;
    char user_input[1000] = {};
    char card_no[MAX_NO_CARD];
    char cvc[MAX_NO_CVC];
    payment_t new;

    while(valid_card_no){
        printf("Enter new card number (16 digits):\n");
        fgets(user_input, 100 ,stdin);
        if(check_card_number(user_input, card_no)){
            strcpy(new.card_number, card_no);
            valid_card_no = 0;
        } else {
            printf("Your input is not valid\n");
        }
    }

    while(valid_year){
        printf("Enter new card expiry year(2021 will be 21):\n");
        fgets(user_input, 10000 ,stdin);
        if(check_year(user_input, &year)){
            new.year = year;
            valid_year = 0;
        } else {
            printf("Your input is not valid\n");
        }
    }

    while(valid_month){
        printf("Enter new card expiry month:\n");
        fgets(user_input, 10000 ,stdin);
        if(check_month(user_input, &month, year)){
            new.month = month;
            valid_month = 0;
        } else {
            printf("Your input is not valid\n");
        }
    }

    while(valid_cvc){
        printf("Enter new card cvc:\n");
        fgets(user_input, 10000 ,stdin);
        if(check_cvc(user_input, cvc)){
            strcpy(new.cvc, cvc);
            valid_cvc = 0;
        } else {
            printf("Your input is not valid\n");
        }
    }

    printf("Press 'Enter' key to view details\n");
    while ((getchar()) != '\n');

    printf("CURRENT PAYMENT DETAILS\n");
    printf("Card Number          Expiry Date     CVC \n");
    printf("-------------------- --------------- ------\n");
    printf("%-20s %-15s %-5s\n\n",
             users[index].payment.card_number, expiry_date, users[index].payment.cvc);

    expiry(expiry_date, new.month, new.year);

    printf("NEW PAYMENT DETAILS\n");
    printf("Card Number          Expiry Date     CVC \n");
    printf("-------------------- --------------- ------\n");
    printf("%-20s %-15s %-5s\n\n",
             new.card_number, expiry_date, new.cvc);

    printf("Do you want to update new payment details? y/n\n");
    char choice;
    scanf("%c", &choice);

    if(choice == 'y'){
        strcpy(users[index].payment.card_number, new.card_number);
        users[index].payment.month = new.month;
        users[index].payment.year = new.year;
        strcpy(users[index].payment.cvc, new.cvc);
        save_student_db(users, no_of_user);
    } else if (choice == 'n') {
        printf("Going back to main without saving\n");
    } else {
        printf("Invalid choice; going back to menu\n");
    }
}

int check_card_number(char * user_input, char * card_number){
    if(strlen(user_input) != MAX_NO_CARD + 1){
        return 0;
    }
    int i;
    user_input[MAX_NO_CARD] ='\0';
    for(i = 0; i < MAX_NO_CARD; i++){
        if(!is_right_format_number(user_input[i])){
            return 0;
        }
    }
    for(i = 0; i < MAX_NO_CARD + 1 ; i++){
        card_number[i] = user_input[i];
    }
    return 1;
}

int check_month(char * user_input, int * month, int year){
    if(strlen(user_input) > 3){
        return 0;
    }
    int i;
    char temp[2];
    user_input[strlen(user_input)] ='\0';
    for(i = 0; i < 3; i++){
        temp[i] = user_input[i];
    }
    for(i = 0; i < strlen(user_input) - 1; i++){
        if(!is_right_format_number(temp[i])){
            return 0;
        }
    }
    sscanf(temp, "%d", month);
    if(*month < 1 || *month > 12){
        return 0;
    }
    if(year == 19){
        if(*month < 6) return 0;
    }
    return 1;
}

int check_year(char * user_input, int * year){
    if(strlen(user_input) > 3){
        return 0;
    }
    int i;
    char temp[2];
    user_input[strlen(user_input)] ='\0';
    for(i = 0; i < 3; i++){
        temp[i] = user_input[i];
    }
    for(i = 0; i < strlen(user_input) - 1; i++){
        if(!is_right_format_number(temp[i])){
            return 0;
        }
    }
    sscanf(temp, "%d", year);
    if(*year < 19){
        return 0;
    }
    return 1;
}

int check_cvc(char * user_input, char * cvc){
    if(strlen(user_input) != MAX_NO_CVC + 1){
        return 0;
    }
    int i;
    user_input[MAX_NO_CVC] ='\0';
    for(i = 0; i < MAX_NO_CVC ; i++){
        if(!is_right_format_number(user_input[i])){
            return 0;
        }
    }
    for(i = 0; i < MAX_NO_CVC + 1; i++){
        cvc[i] = user_input[i];
    }
    return 1;
}

void init_menu(){    
	user_t users[MAX_NO_USERS];
    int no_of_user;
    load_user(users, &no_of_user);

    /*int variable that would store user input for menu*/
    int choice = 0;

    /*menu would loop unless user enters 3 */
    while(choice != 3) {
        intro_prompt();    /* print login prompt */
        if(scanf("%d", &choice) != 1){     /* if user input is NOT digit */
            while ((getchar()) != '\n');      /* flush input buffer */
            printf("Invalid choice \n");      /* prints error message */
        } else {     /* if user input is digit */
            switch(choice){
                case 1:
                    login(users, &no_of_user);
                    break;
                case 2:
                    login_as_admin(users, &no_of_user);
                    break;
                case 3:
                    exit(0);
;                default:      /* when user input is digit but not 1-5 */
                    printf("Invalid choice \n");
                    break;
            }
        }
    }
}
