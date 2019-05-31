/*******************************************************************************
 * ENCRYPTION
*******************************************************************************/

/*******************************************************************************
 * This function encrypts the student database file
 * Author: Mitch Winyard
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define DB_NAME "student_database"

/*******************************************************************************
* The following functions are PRIVATE and should not be used on their own by the
* program.
*******************************************************************************/

FILE *open_existing_db_file ()
{
    FILE *fp;

    fp=fopen(DB_NAME, "a+"); /* Opens the student_database.txt file in read-only mode */
    if(fp==NULL) /* If the student_database.txt file is not found, return this error message */
    {
        printf(" ERROR - File does not exist, or error in opening.\n");
        return fp;
    }
    return fp;
}


FILE *open_clean_db_file ()
{
    FILE *fp;

    fp=fopen(DB_NAME, "w+"); /* Opens the student_database.txt file in read-only mode */
    if(fp==NULL) /* If the student_database.txt file is not found, return this error message */
    {
        printf(" ERROR - File does not exist, or error in opening.\n");
        return fp;
    }
    return fp;
}


FILE *open_db_temp_file ()
{
    FILE *fp;
    fp=fopen("temp.txt", "w+"); /* Creates/opens a file called temp.txt in write mode */
    if (fp==NULL) /* If the system is unable to create a temp.txt file, return this error message */
    {
        printf(" ERROR - Error in creation of file 'temp.txt'\n");
		return fp;
    }
    return fp;
}


void close_db_file (FILE *fp)
{
    fclose(fp);
}


void close_db_temp_file (FILE *fp)
{
    fclose(fp);
}


void save_temp_to_db (FILE *fptrt, FILE *fptrs)
{
    char ch;

    rewind(fptrs);
    rewind(fptrt);

	while(1)
	{
		ch=fgetc(fptrt); /* Read each char in the file including spaces and newlines */
		if(ch==EOF)  /* Stop reading at end of file */
		{
			break;
		}
		else
		{
			fputc(ch, fptrs); /* Replace each corresponding char in student_database.txt with the data from temp.txt */
		}
	}
}

void encrypt (FILE *fptrt, FILE *fptrs)
{
    char ch, key;

    key = 'm';

    while(1)
    {
        ch=fgetc(fptrs); /* Read each char in the file including spaces and newlines */
        if(ch==EOF) /* Stop reading at end of file */
        {
            break;
        }
        else
        {
            ch=ch ^ key;
            fputc(ch, fptrt);
        }
    }
    return;
}

void delete_temp_file ()
{
    remove("temp.txt");
}

/*******************************************************************************
* The following functions are PUBLIC and can be called into the code.
* open_db should ALWAYS be followed by close_db once the program has completed
* other fucntions.
*******************************************************************************/

/*******************************************************************************
* This function is used to decrypt and open the database. Once the database is
* in plain, it is presented to the program for view, scan, edit etc.
* IMPORTANT - The database is now in PLAIN TEXT.
* Users cannot edit the database in plain form outside of the program as
* the program is holding the file
*******************************************************************************/
FILE *open_db ()
{
    FILE *db_ptr, *fptrt;

    db_ptr = open_existing_db_file();
    fptrt = open_db_temp_file();
    encrypt (fptrt, db_ptr);
    close_db_file (db_ptr);
    db_ptr = open_clean_db_file ();
    save_temp_to_db (fptrt, db_ptr);
    close_db_temp_file(fptrt);
    delete_temp_file();
    rewind (db_ptr);
    return db_ptr;
}

/*******************************************************************************
* This function is used to encrypt and close the database. Once the database
* in no longer needed to be in plain, this function should be run immediately.
* IMPORTANT - The database is now in CIPHER TEXT. Futher using the database will
* now return unreadable data.
*******************************************************************************/
void close_db (FILE *db_ptr)
{
    FILE *fptrt;

    fptrt = open_db_temp_file();
	encrypt (fptrt, db_ptr);
	close_db_file (db_ptr);
	db_ptr = open_clean_db_file ();
	save_temp_to_db (fptrt, db_ptr);
	close_db_file (db_ptr);
	close_db_temp_file (fptrt);
	delete_temp_file ();
}
/*******************************************************************************
* This function is used to swap the database from one encryption state to the other
* as XOR is symmetrical.
* If at any stage the database is NOT encrypted when the program initialises, run
* this function to ensure the database in in the correct state.
*******************************************************************************/
void first_encryption()
{
    FILE *db_ptr, *fptrt;

    db_ptr = open_existing_db_file();
    fptrt = open_db_temp_file();
    encrypt (fptrt, db_ptr);
    close_db_file (db_ptr);
    db_ptr = open_clean_db_file ();
    save_temp_to_db (fptrt, db_ptr);
    close_db_temp_file(fptrt);
    delete_temp_file();
   rewind (db_ptr);
}
