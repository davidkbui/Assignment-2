/*******************************************************************************
 * STUDENT - AUTHOR: JOEL MORRISON
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*******************************************************************************
 * This function prints the available options for the student 
 * user to chose from.
*******************************************************************************/

int main(void){
    student_menu();
    int selection;
    scanf("%d", &selection);
    inputCases(selection);
    return 0;
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

    main();
}


/*******************************************************************************
 * This function allows the user to edit and then update their details
 * in the database 
*******************************************************************************/
void update_my_details(){

    /*Not Finished*/
    scanf("%d", &student.bankDetails);

    printf("Enter expiry >\n");
    scanf("%d %d", &student.expiryMonth, &student.expiryYear);

    printf("Enter CCV Details>\n");
    scanf("%d", &student.ccv);
    main();


}


/*******************************************************************************
 * Function prints the history for either the day, month or year of previous 
 * transactions, depending on what the user has selected.
*******************************************************************************/

void view_my_transactions(){

       printf("Coming Soon>\n");
       main();
    
}

