#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void updateAccount( struct User u);
void checkAccounts(struct User u);
void makeTransaction(struct User u);

void updateRecord(struct Record r);


int saveUser(int id, char *username, char *password);
int determineUserId();
int getUserId(struct User u);
