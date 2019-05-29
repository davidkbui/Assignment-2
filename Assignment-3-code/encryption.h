#ifndef COMPRESSION_H
#define COMPRESSION_H

FILE *open_db();
void close_db(FILE *db_ptr);
void encrypt();
void init_db();
void first_encryption();

#endif
