/*student.h file*/
#ifndef STUDENT_H

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


#endif
