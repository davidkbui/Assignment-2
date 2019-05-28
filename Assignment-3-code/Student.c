/*******************************************************************************
 * STUDENT - AUTHOR: JOEL MORRISON
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_NAME "student_database"
#define BUFFER_SIZE 1000
#define ID_SIZE 5



int Student_Main();
int Student_Login();
int student_menu(const char *ID_number);
void check_my_details(const char *ID_number);
void input_Student_Cases (int studentSelection,const char *ID_number);
int UpdateDetailsOptions(const char *ID_number);
void UpdateDetailsSelection (int updateSelect, const char *ID_number);
void replaceOldBankDetails(char *str, const char *find, const char *newBankNumber);
int UpdateBankNumber(const char *ID_number);
void replaceOldPhoneDetails(char *str, const char *find, const char *newPhoneNumber);
int UpdatePhoneNumber(const char *ID_number);
void replaceOldCVVDetails(char *str, const char *find, const char *newCVVNumber);
int UpdateCVVNumber(const char *ID_number);
void replaceOldExpiryDetails(char *str, const char *find, const char *newExpiryNumber);
int UpdateExpiryNumber(const char *ID_number);
void check_password(const char *ID_number);



int main(){
    Student_Main();
    return 0;
}


int Student_Main(){
    Student_Login();
    return 0;

}

int Student_Login(){

    int i;
    int j=0;
    int  p;
    char ID_number[6];
    printf("------------------\n");
    printf("Welcome Student\n");
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
                /*printf("Success\n");*/
              /*  CheckPassword(ID_number);*/
                check_password(ID_number);
             /*  student_menu(ID_number);*/
             
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
    char ID_password[10];
    FILE * fPtr;
    fPtr  = fopen(DB_NAME, "r");
    char line[20];
    int linenum =0;
    int foundline =(linenum) ;
    int lineStop = (foundline+0);

    /* return NULL if unable to open file. */
    if (fPtr == NULL)
    {
        printf("\nUnable to open file.\n");
        exit(EXIT_SUCCESS);
    }

   /* printf("Enter ID>\n");
    scanf ("%s", ID_number);*/
    while (fgets(line, sizeof line, fPtr) != NULL) 
    {   
          
        linenum++;
        if (strncmp(ID_number, line,ID_SIZE) ==0)
        {
            /*printf("ID found\n" );*/
            break;
        }
    
    }

   /* printf("User: %s \n",ID_number); */

    char student_password[256]; 
    while (fgets( student_password, sizeof  student_password, fPtr) != NULL) 
        {   
            if (foundline <= lineStop)
            {  
                /*printf("Your password is:%s",  student_password);*/

                    printf("Enter password\n");
                     scanf ("%s", ID_password);

                     if (strncmp(ID_password, student_password,6)==0)
                        {
                    /* printf("succes password is:%s",  student_password);*/
                        fclose(fPtr);
                        student_menu(ID_number);
                       
                             }
                         else {
                        printf("Access Denined!!!\n");


                             fclose(fPtr);

                             exit(0);
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



    "3. Coming Soon *******\n"
    "4. Exit\n"
    "Enter choice 1 - 4>\n");

    int student_menu_select;
    scanf("%d", &student_menu_select);
   

   /* while(student_menu_select != 4)
    { 
        if((student_menu_select >5) | (student_menu_select <1) ){     
            printf("Invalid choice \n");
              scanf("%d", &student_menu_select);

        }
        else
        {*/
            input_Student_Cases(student_menu_select, ID_number);

    
    return 0;


   
}

void input_Student_Cases (int studentSelection, const char *ID_number)
{
    switch(studentSelection) 
    {
      case 1: check_my_details(ID_number); break;
      case 2: UpdateDetailsOptions(ID_number); break;
      case 4: exit(0); break;
      /*case 3: view_my_trID_numberactions(); break;*/
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

   /* printf("Enter ID>\n");
    scanf ("%s", ID_number);*/
    while (fgets(line, sizeof line, fPtr) != NULL) 
    {   
          
        linenum++;
        if (strncmp(ID_number, line, ID_SIZE) ==0)
        {
            /*printf("Details found\n" );*/
            break;
        }
    
    }
    int foundline =(linenum) ;
    int lineStop = (foundline+7);

    printf("User: %d \n", linenum); 

    printf("Use11r: %d \n", foundline); 

    printf("\nYour Details.\n");

    char student_details[256]; 
    while (fgets(student_details, sizeof  student_details, fPtr) != NULL) 
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
    "1. Update Bank Number\n"
    "2. Update Expiry Date\n"
    "3. Update Phone Number\n"
    "4. Exit\n"
    "Enter choice 1 - 4>\n");


    int updateDetailsSelect;
    scanf("%d", &updateDetailsSelect);
    /*
    while(updateDetailsSelect != 4)
    { 
        if(( updateDetailsSelect > 4) | ( updateDetailsSelect < 1) ){     
            printf("Invalid choice \n");
            scanf("%d", &updateDetailsSelect);

        }
        else
        {*/
            UpdateDetailsSelection (updateDetailsSelect, ID_number);
        
    return 0;



}


void UpdateDetailsSelection (int updateSelect, const char *ID_number)
{
    switch(updateSelect) 
    {
      case 1: UpdateBankNumber(ID_number); break; 
      case 2: UpdateExpiryNumber(ID_number); break;
      case 3: UpdatePhoneNumber(ID_number); break;
      case 4: exit(0); break;
    }
}


int UpdateBankNumber(const char *ID_number)
{
    
    printf("-------------------------UpdateBank-------------------\n");

        /* File pointer to hold reference of input file */
    FILE * fPtr;
    FILE * fTemp;
    
    char buffer[BUFFER_SIZE];
    char find[100];

 
    char newBankNumber[100];

    {
            
                printf("Bank Number Selected\n"); 
                FILE * fPtr;
                fPtr  = fopen(DB_NAME, "r");
                char line[20];
                int linenum =0;
                int foundline =(linenum) ;
                int lineStop = (foundline+5);
                char find[100];
                
                

                /* return NULL if unable to open file. */
                if (fPtr == NULL)
                {
                    printf("\nUnable to open file.\n");
                    exit(EXIT_SUCCESS);
                }

           /*     printf("Enter ID>\n");
                scanf ("%s", ID_number);*/
                while (fgets(line, sizeof line, fPtr) != NULL) 
                {     
                    linenum++;
                    if (strncmp(ID_number, line,ID_SIZE) ==0)
                    {
                        break;
                    }
                }

                char student_details[100];
                while (fgets(student_details, sizeof student_details, fPtr) != NULL) 
                    {   
                        if (foundline == lineStop)
                        {  
                            printf("Old Bank Number is %s", student_details);
                            foundline++;
                            memcpy(find, student_details, sizeof(find));

                        }
                        else
                        {
                            foundline++;
                        }
                    }


             /*   printf("Final is: %s\n", find ); */

                /* Close file*/
                fclose(fPtr);


                /*printf("find was %s\n", find);*/
                printf("Replace with: ");
                scanf("%s", newBankNumber);

     }

                
    /*  Open all required files */
    fPtr  = fopen(DB_NAME, "r");
    fTemp = fopen("replace.tmp", "w"); 

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file*/
        printf("\nUnable to open file.\n");
        exit(EXIT_SUCCESS);
    }

    /*
     * Read line from source file and write to destination 
     * file after replacing given word.
     */
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        /* Replace all occurrence of word from current line*/
        replaceOldBankDetails(buffer, find, newBankNumber);

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

    printf("\nSuccessfully replaced   '%s' with '%s'.", find, newBankNumber);

    printf("\nPlease now update your CVV for your new Bank Number\n");
    UpdateCVVNumber(ID_number);

    UpdateDetailsOptions(ID_number);
    return 0;

}


void replaceOldBankDetails(char *str, const char *find, const char *newBankNumber)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;
    char blank[10]="\n";
    owlen = strlen(find);

    
    while ((pos = strstr(str, find)) != NULL)
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
        strcat(str, temp + index + owlen);

    }
}


int UpdatePhoneNumber(const char *ID_number)
{
    
    printf("-------------------------UpdatePhone-------------------\n");

        /* File pointer to hold reference of input file */
    FILE * fPtr;
    FILE * fTemp;
    
    char buffer[BUFFER_SIZE];
    char find[100];

 
    char newPhoneNumber[100];

    {
            
                printf("Bank Number Selected\n"); 
                FILE * fPtr;
                fPtr  = fopen(DB_NAME, "r");
                char line[20];
                int linenum =0;
                int foundline =(linenum) ;
                int lineStop = (foundline+4);
                char find[100];
                
                

                /* return NULL if unable to open file. */
                if (fPtr == NULL)
                {
                    printf("\nUnable to open file.\n");
                    exit(EXIT_SUCCESS);
                }

           /*     printf("Enter ID>\n");
                scanf ("%s", ID_number);*/
                while (fgets(line, sizeof line, fPtr) != NULL) 
                {     
                    linenum++;
                    if (strncmp(ID_number, line, 4) ==0)
                    {
                        break;
                    }
                }

                char student_details[100];
                while (fgets(student_details, sizeof student_details, fPtr) != NULL) 
                    {   
                        if (foundline == lineStop)
                        {  
                            printf("Old Phone Number is %s", student_details);
                            foundline++;
                            memcpy(find, student_details, sizeof(find));

                        }
                        else
                        {
                            foundline++;
                        }
                    }


             /*   printf("Final is: %s\n", find ); */

                /* Close file*/
                fclose(fPtr);


                /*printf("find was %s\n", find);*/
                printf("Replace with: ");
                scanf("%s", newPhoneNumber);

     }

                
    /*  Open all required files */
    fPtr  = fopen(DB_NAME, "r");
    fTemp = fopen("replace.tmp", "w"); 

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file*/
        printf("\nUnable to open file.\n");
        exit(EXIT_SUCCESS);
    }

    /*
     * Read line from source file and write to destination 
     * file after replacing given word.
     */
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        /* Replace all occurrence of word from current line*/
        replaceOldBankDetails(buffer, find, newPhoneNumber);

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

    printf("\nSuccessfully replaced  '%s' with '%s'.", find, newPhoneNumber);

    UpdateDetailsOptions(ID_number);
    return 0;

}


void replaceOldPhoneDetails(char *str, const char *find, const char *newPhoneNumber)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;
    char blank[10]="\n";
    owlen = strlen(find);

    
    while ((pos = strstr(str, find)) != NULL)
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
        strcat(str, temp + index + owlen);

    }
}


int UpdateCVVNumber(const char *ID_number)
{
    
    printf("-------------------------UpdateCVV-------------------\n");

        /* File pointer to hold reference of input file */
    FILE * fPtr;
    FILE * fTemp;
    
    char buffer[BUFFER_SIZE];
    char find[100];

 
    char newCVVNumber[100];

    {
            
                printf("Bank Number Selected\n"); 
                FILE * fPtr;
                fPtr  = fopen(DB_NAME, "r");
                char line[20];
                int linenum =0;
                int foundline =(linenum) ;
                int lineStop = (foundline+7);
                char find[100];
                
                

                /* return NULL if unable to open file. */
                if (fPtr == NULL)
                {
                    printf("\nUnable to open file.\n");
                    exit(EXIT_SUCCESS);
                }

           /*     printf("Enter ID>\n");
                scanf ("%s", ID_number);*/
                while (fgets(line, sizeof line, fPtr) != NULL) 
                {     
                    linenum++;
                    if (strncmp(ID_number, line,ID_SIZE) ==0)
                    {
                        break;
                    }
                }

                char student_details[100];
                while (fgets(student_details, sizeof student_details, fPtr) != NULL) 
                    {   
                        if (foundline == lineStop)
                        {  
                            printf("Old CVV Number is %s", student_details);
                            foundline++;
                            memcpy(find, student_details, sizeof(find));

                        }
                        else
                        {
                            foundline++;
                        }
                    }


             /*   printf("Final is: %s\n", find ); */

                /* Close file*/
                fclose(fPtr);


                /*printf("find was %s\n", find);*/
                printf("Replace with: ");
                scanf("%s", newCVVNumber);

     }

                
    /*  Open all required files */
    fPtr  = fopen(DB_NAME, "r");
    fTemp = fopen("replace.tmp", "w"); 

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file*/
        printf("\nUnable to open file.\n");
        exit(EXIT_SUCCESS);
    }

    /*
     * Read line from source file and write to destination 
     * file after replacing given word.
     */
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        /* Replace all occurrence of word from current line*/
        replaceOldBankDetails(buffer, find, newCVVNumber);

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

    printf("\nSuccessfully replaced   '%s' with '%s'.", find, newCVVNumber);


    UpdateDetailsOptions(ID_number);
    return 0;

}


void replaceOldCVVDetails(char *str, const char *find, const char *newCVVNumber)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;
    char blank[10]="\n";
    owlen = strlen(find);

    
    while ((pos = strstr(str, find)) != NULL)
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
        strcat(str, temp + index + owlen);

    }
}


int UpdateExpiryNumber(const char *ID_number)
{
    
    printf("-------------------------UpdateExpiry-------------------\n");

        /* File pointer to hold reference of input file */
    FILE * fPtr;
    FILE * fTemp;
    
    char buffer[BUFFER_SIZE];
    char find[100];

 
    char newExpiryNumber[100];

    {
            
                printf("Expiry Number Selected\n"); 
                FILE * fPtr;
                fPtr  = fopen(DB_NAME, "r");
                char line[20];
                int linenum =0;
                int foundline =(linenum) ;
                int lineStop = (foundline+6);
                char find[100];
                
                

                /* return NULL if unable to open file. */
                if (fPtr == NULL)
                {
                    printf("\nUnable to open file.\n");
                    exit(EXIT_SUCCESS);
                }

           /*     printf("Enter ID>\n");
                scanf ("%s", ID_number);*/
                while (fgets(line, sizeof line, fPtr) != NULL) 
                {     
                    linenum++;
                    if (strncmp(ID_number, line,ID_SIZE) ==0)
                    {
                        break;
                    }
                }

                char student_details[100];
                while (fgets(student_details, sizeof student_details, fPtr) != NULL) 
                    {   
                        if (foundline == lineStop)
                        {  
                            printf("Old Expiry Number is %s", student_details);
                            foundline++;
                            memcpy(find, student_details, sizeof(find));

                        }
                        else
                        {
                            foundline++;
                        }
                    }


             /*   printf("Final is: %s\n", find ); */

                /* Close file*/
                fclose(fPtr);


                /*printf("find was %s\n", find);*/
                printf("Replace with: ");
                scanf("%s", newExpiryNumber);

     }

                
    /*  Open all required files */
    fPtr  = fopen(DB_NAME, "r");
    fTemp = fopen("replace.tmp", "w"); 

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file*/
        printf("\nUnable to open file.\n");
        exit(EXIT_SUCCESS);
    }

    /*
     * Read line from source file and write to destination 
     * file after replacing given word.
     */
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        /* Replace all occurrence of word from current line*/
        replaceOldBankDetails(buffer, find, newExpiryNumber);

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

    printf("\nSuccessfully replaced   '%s' with '%s'.", find, newExpiryNumber);


    UpdateDetailsOptions(ID_number);
    return 0;

}


void replaceOldExpiryDetails(char *str, const char *find, const char *newExpiryNumber)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;
    char blank[10]="\n";
    owlen = strlen(find);

    
    while ((pos = strstr(str, find)) != NULL)
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
        strcat(str, temp + index + owlen);

    }
}


