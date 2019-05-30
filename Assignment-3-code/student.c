/*******************************************************************************
 * STUDENT - AUTHOR: JOEL MORRISON
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_NAME "student_database"
#define BUFFER_SIZE 1000
#define ID_SIZE 5

int student_main(){
    
	printf("------------------\n");
    printf("Welcome Student\n");
    student_login();
    return 0;

}

int student_login(){

    int i;
    int j=0;
    int  p;
    char ID_number[6];

  
	printf("----------------------\n");
    printf("Enter Student Number\n");

    while (j != 1)
    {
        scanf ("%s", ID_number);
        p = strlen(ID_number);
        for (i=0; i<p; i++)
        {
            if (ID_number[i] >= '0' && ID_number[i] <= '9')
            {
                j= 1;
                check_password(ID_number);
            }

            else
            {
                printf("Invalid ID, try again\n");
                break;
            }
        }
     
    }

    return 0;
}



void check_password(const char *ID_number)
{
    char ID_password[20];
    FILE *fPtr;
    fPtr  = open_db();
    char line[20];
    int linenum =0;
    int foundline =(linenum);
    int lineStop = (foundline+0);
    
    /* return NULL if unable to open file. */
    if (fPtr == NULL)
    {
        printf("\nUnable to open file.\n");
        exit(0);
    }

    while (fgets(line, sizeof line, fPtr) != NULL) 
    {   
          
        linenum++;
        if (strncmp(ID_number, line, ID_SIZE) ==0)
        {
            break;
        }
    
    }

    char student_password[256]; 
    while (fgets( student_password, sizeof  student_password, fPtr) != NULL) 
        {   
            if (foundline <= lineStop)
            {  

                printf("Enter password\n");
                scanf ("%s", ID_password);
	
				int matching_passwords = 0;
				matching_passwords = strcmp(ID_password,student_password);

                if (matching_passwords==-10)
            	{
                    student_menu(ID_number);
                    close_db(open_db);

                }
                
                else 
                {
			
		print_bold_red();		
                    printf("Access Denied!\n");
		print_reset_color();
                    student_login();
                    close_db(open_db);
                }

                foundline++;
        	}

            else
            {
                foundline++;
            }
        }


}


int student_menu(const char *ID_number)
{
    printf("\n"
    "------------------\n"
    "Select an option\n"
    "1. Check My Details\n"
    "2. Update My payment details\n"
    "3. Exit\n"
    "Enter choice 1 - 3>\n");

    int student_menu_select;
    scanf("%d", &student_menu_select);
    input_Student_Cases(student_menu_select, ID_number);

    return 0;
   
}

void input_Student_Cases (int studentSelection, const char *ID_number)
{
    switch(studentSelection) 
    {
      case 1: check_my_details(ID_number); break;
      case 2: UpdateDetailsOptions(ID_number); break;
      case 3: exit(0); break;
    }
}

void check_my_details(const char *ID_number)
{
    FILE * fPtr;
    fPtr  = fopen(DB_NAME, "r");
    char line[255];
    int linenum = 0;

    /* return NULL if unable to open file. */
    if (fPtr == NULL)
    {
        printf("\nUnable to open file.\n");
        exit(0);
    }

    while (fgets(line, sizeof line, fPtr) != NULL) 
    {     
        linenum++;
        if (strncmp(ID_number, line, ID_SIZE) ==0)
        {
            break;
        }
    
    }

    int foundline =(linenum);
    int lineStop = (foundline+7);

    printf("\nYour Details.\n");

    char student_details[256]; 
    while (fgets(student_details, sizeof student_details, fPtr) != NULL) 
        {  
            if ( (foundline) == lineStop-6)
            {  
                printf("First Name: %s",  student_details);
                foundline++;
            }

            else if ( (foundline) == lineStop-5)
            {  
                printf("Last Name: %s",  student_details);
                foundline++;
            }

            else if ( (foundline) == lineStop-4)
            {  
                printf("Year: %s",  student_details);
                foundline++;
            }
            
             else if ( (foundline) == lineStop-3)
            {  
                printf("Phone Number: %s",  student_details);
                foundline++;
            }
             else if ( (foundline) == lineStop-2)
            {  
                printf("Bank Number: %s",  student_details);
                foundline++;
            }
                else if ( (foundline) == lineStop-1)
            {  
                printf("Bank Number Expiry Date: %s",  student_details);
                foundline++;
            }

            else if ( (foundline) == lineStop)
            {  
                printf("CVV: %s",  student_details);
                foundline++;
            }
            else
            {
                foundline++;
            }
        }

    /* Close file*/
    fclose(fPtr);

    student_menu(ID_number);
}


int UpdateDetailsOptions(const char *ID_number){

    printf("\nWhat would you like to update?\n");
    printf("\n"
    "Select an option\n"
    "1. Update Bank Details\n"
    "2. Update Phone Number\n"
    "3. Exit\n"
    "Enter choice 1 - 3>\n");

    int updateDetailsSelect;
    scanf("%d", &updateDetailsSelect);
    UpdateDetailsSelection (updateDetailsSelect, ID_number);
        
    return 0;

}


void UpdateDetailsSelection (int updateSelect, const char *ID_number)
{
    switch(updateSelect) 
    {
      case 1: UpdateBankNumber(ID_number); break; 
      case 2: UpdatePhoneNumber(ID_number); break;
      case 3: exit(0); break;
    }
}


int UpdateBankNumber(const char *ID_number)
{

    FILE * fPtr;
    FILE * fTemp;             
    fPtr  = fopen(DB_NAME, "r");
    
    char buffer[BUFFER_SIZE];
    char find_bank[100];
    char newBankNumber[100];
    char line[100];
    int linenum =0;
    int foundline =(linenum) ;
    int lineStop = (foundline+5);
    char student_details[100];

    printf("-------------------------UpdateBankNumber-------------------\n");
    printf("Bank Number Selected\n"); 
            

    /* return NULL if unable to open file. */
    if (fPtr == NULL)
        {
            printf("\nUnable to open file.\n");
            exit(0);
        }

    while (fgets(line, sizeof line, fPtr) != NULL) 
    {
        linenum++;
        if (strncmp(ID_number, line, ID_SIZE)==0)
        {
            break;
        }
    }
    

    while (fgets(student_details, sizeof student_details, fPtr) != NULL) 
    {   
        if (foundline == lineStop)
        {  
            printf("Old Bank Number is %s", student_details);
            foundline++;
            memcpy(find_bank, student_details, sizeof(find_bank));

        }
        else
            {
                foundline++;
            }
    }



    fclose(fPtr);


    printf("\nReplace with: ");
    scanf("%s", newBankNumber);

                
    /*  Open all required files */
    fPtr  = fopen(DB_NAME, "r");
    fTemp = fopen("replace.tmp", "w"); 

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file*/
        printf("\nUnable to open file.\n");
        exit(0);
    }

    /*
     * Read line from source file and write to destination 
     * file after replacing given word.
     */
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        /* Replace word from current line*/
        replaceOldBankDetails(buffer, find_bank, newBankNumber);

        /* After replacing write it to temp file.*/
        fputs(buffer, fTemp);

    }


    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);

    /* Delete original source file */
    remove(DB_NAME);

    /* Rename temp file as original file */
    rename("replace.tmp", DB_NAME);

    printf("\nSuccessfully replaced  '%s' with '%s'.", find_bank, newBankNumber);

    UpdateCVVNumber(ID_number);

    UpdateDetailsOptions(ID_number);
    return 0;

}


void replaceOldBankDetails(char *str, const char *find_bank, const char *newBankNumber)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    char blank[10]="\n";
    int word_len = strlen(find_bank);


    while ((pos = strstr(str, find_bank)) != NULL)
    {
        /* Backup current line*/
        strcpy(temp, str);

        /*Index of current found word*/
        index = pos - str;

        /* Terminate str after word found index*/
        str[index] = '\0';


        /* Concatenate str with new word */

        strcat(str, newBankNumber);
        strcat(str,blank);

        /* Concatenate str with remaining words after */
        /* find found index.*/
        strcat(str, temp + index + word_len);

    }
}





int UpdateCVVNumber(const char *ID_number)
{

    FILE * fPtr;
    FILE * fTemp;             
    fPtr  = fopen(DB_NAME, "r");
    
    char buffer[BUFFER_SIZE];
    char find_CVV[100];
    char newCVVNumber[100];
    char line[100];
    int linenum =0;
    int foundline =(linenum) ;
    int lineStop = (foundline+7);
    char student_details[100];

    printf("-------------------------UpdateCVVNumber-------------------\n");
    printf("CVV Number Selected\n"); 
            

    /* return NULL if unable to open file. */
    if (fPtr == NULL)
        {
            printf("\nUnable to open file.\n");
            exit(0);
        }

    while (fgets(line, sizeof line, fPtr) != NULL) 
    {
        linenum++;
        if (strncmp(ID_number, line, ID_SIZE)==0)
        {
            break;
        }
    }
    

    while (fgets(student_details, sizeof student_details, fPtr) != NULL) 
    {   
        if (foundline == lineStop)
        {  
            printf("Old CVV Number is %s", student_details);
            foundline++;
            memcpy(find_CVV, student_details, sizeof(find_CVV));

        }
        else
            {
                foundline++;
            }
    }



    fclose(fPtr);


    printf("\nReplace with: ");
    scanf("%s", newCVVNumber);

                
    /*  Open all required files */
    fPtr  = fopen(DB_NAME, "r");
    fTemp = fopen("replace.tmp", "w"); 

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file*/
        printf("\nUnable to open file.\n");
        exit(0);
    }

    /*
     * Read line from source file and write to destination 
     * file after replacing given word.
     */
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        /* Replace word from current line*/
        replaceOldCVVDetails(buffer, find_CVV, newCVVNumber);

        /* After replacing write it to temp file.*/
        fputs(buffer, fTemp);

    }


    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);

    /* Delete original source file */
    remove(DB_NAME);

    /* Rename temp file as original file */
    rename("replace.tmp", DB_NAME);

    printf("\nSuccessfully replaced  '%s' with '%s'.", find_CVV, newCVVNumber);

    UpdateExpiryNumber(ID_number);
    
    return 0;

}


void replaceOldCVVDetails(char *str, const char *find_CVV, const char *newCVVNumber)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    char blank[10]="\n";
    int word_len = strlen(find_CVV);


    while ((pos = strstr(str, find_CVV)) != NULL)
    {
        /* Backup current line*/
        strcpy(temp, str);

        /*Index of current found word*/
        index = pos - str;

        /* Terminate str after word found index*/
        str[index] = '\0';


        /* Concatenate str with new word */

        strcat(str, newCVVNumber);
        strcat(str,blank);

        /* Concatenate str with remaining words after */
        /* find found index.*/
        strcat(str, temp + index + word_len);

    }
}


int UpdateExpiryNumber(const char *ID_number)
{

    FILE * fPtr;
    FILE * fTemp;             
    fPtr  = fopen(DB_NAME, "r");
    
    char buffer[BUFFER_SIZE];
    char find_expiry[100];
    char newExpiryNumber[100];
    char line[100];
    int linenum =0;
    int foundline =(linenum) ;
    int lineStop = (foundline+6);
    char student_details[100];

    printf("-------------------------UpdateExpiryNumber-------------------\n");
    printf("Expiry Number Selected\n"); 
            

    /* return NULL if unable to open file. */
    if (fPtr == NULL)
        {
            printf("\nUnable to open file.\n");
            exit(0);
        }

    while (fgets(line, sizeof line, fPtr) != NULL) 
    {
        linenum++;
        if (strncmp(ID_number, line, ID_SIZE)==0)
        {
            break;
        }
    }
    

    while (fgets(student_details, sizeof student_details, fPtr) != NULL) 
    {   
        if (foundline == lineStop)
        {  
            printf("Old Expiry Date was %s", student_details);
            foundline++;
            memcpy(find_expiry, student_details, sizeof(find_expiry));

        }
        else
            {
                foundline++;
            }
    }



    fclose(fPtr);


    printf("\nReplace with: ");
    scanf("%s", newExpiryNumber);

                
    /*  Open all required files */
    fPtr  = fopen(DB_NAME, "r");
    fTemp = fopen("replace.tmp", "w"); 

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file*/
        printf("\nUnable to open file.\n");
        exit(0);
    }

    /*
     * Read line from source file and write to destination 
     * file after replacing given word.
     */
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        /* Replace word from current line*/
        replaceOldExpiryDetails(buffer, find_expiry, newExpiryNumber);

        /* After replacing write it to temp file.*/
        fputs(buffer, fTemp);

    }


    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);

    /* Delete original source file */
    remove(DB_NAME);

    /* Rename temp file as original file */
    rename("replace.tmp", DB_NAME);

    printf("\nSuccessfully replaced  '%s' with '%s'.", find_expiry, newExpiryNumber);

    UpdateDetailsOptions(ID_number);
    return 0;

}


void replaceOldExpiryDetails(char *str, const char *find_expiry, const char *newExpiryNumber)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    char blank[10]="\n";
    int word_len = strlen(find_expiry);


    while ((pos = strstr(str, find_expiry)) != NULL)
    {
        /* Backup current line*/
        strcpy(temp, str);

        /*Index of current found word*/
        index = pos - str;

        /* Terminate str after word found index*/
        str[index] = '\0';


        /* Concatenate str with new word */

        strcat(str, newExpiryNumber);
        strcat(str,blank);

        /* Concatenate str with remaining words after */
        /* find found index.*/
        strcat(str, temp + index + word_len);

    }
}


int UpdatePhoneNumber(const char *ID_number)
{

    FILE * fPtr;
    FILE * fTemp;             
    fPtr  = fopen(DB_NAME, "r");
    
    char buffer[BUFFER_SIZE];
    char find_phone[100];
    char newPhoneNumber[100];
    char line[100];
    int linenum =0;
    int foundline =(linenum) ;
    int lineStop = (foundline+4);
    char student_details[100];

    printf("-------------------------UpdatePhone-------------------\n");
    printf("Phone Number Selected\n"); 
            

    /* return NULL if unable to open file. */
    if (fPtr == NULL)
        {
            printf("\nUnable to open file.\n");
            exit(0);
        }

    while (fgets(line, sizeof line, fPtr) != NULL) 
    {
        linenum++;
        if (strncmp(ID_number, line, ID_SIZE)==0)
        {
            break;
        }
    }
    

    while (fgets(student_details, sizeof student_details, fPtr) != NULL) 
    {   
        if (foundline == lineStop)
        {  
            printf("Old Phone Number is %s", student_details);
            foundline++;
            memcpy(find_phone, student_details, sizeof(find_phone));
			printf( "find = %s\n", find_phone);

        }
        else
            {
                foundline++;
            }
    }



    fclose(fPtr);



	printf( "confirm find = %s\n", find_phone);

    printf("\nReplace with: ");
    scanf("%s", newPhoneNumber);

                
    /*  Open all required files */
    fPtr  = fopen(DB_NAME, "r");
    fTemp = fopen("replace.tmp", "w"); 

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file*/
        printf("\nUnable to open file.\n");
        exit(0);
    }

    /*
     * Read line from source file and write to destination 
     * file after replacing given word.
     */
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        /* Replace word from current line*/
        replaceOldPhoneDetails(buffer, find_phone, newPhoneNumber);

        /* After replacing write it to temp file.*/
        fputs(buffer, fTemp);

    }


    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);

    /* Delete original source file */
    remove(DB_NAME);

    /* Rename temp file as original file */
    rename("replace.tmp", DB_NAME);

    printf("\nSuccessfully replaced  '%s' with '%s'.", find_phone, newPhoneNumber);

    UpdateDetailsOptions(ID_number);
    return 0;

}


void replaceOldPhoneDetails(char *str, const char *find_phone, const char *newPhoneNumber)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    char blank[10]="\n";
    int word_len = strlen(find_phone);


    while ((pos = strstr(str, find_phone)) != NULL)
    {
        /* Backup current line*/
        strcpy(temp, str);

        /*Index of current found word*/
        index = pos - str;

        /* Terminate str after word found index*/
        str[index] = '\0';


        /* Concatenate str with new word */

        strcat(str, newPhoneNumber);
        strcat(str,blank);

        /* Concatenate str with remaining words after */
        /* find found index.*/
        strcat(str, temp + index + word_len);

    }
}



