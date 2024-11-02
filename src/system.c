#include "header.h"

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
		  &r->userId,
		  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    printf("%s",u.id);
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
	    u.id,
	    u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    FILE *rf = fopen(RECORDS,"r");


int recordId = 0;
    while (fscanf(rf,"%d %*[^'\n]",&r.id) != EOF)
    {
        recordId = r.id;
    }
    
fclose(rf);
noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
    }
    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);

    r.id = recordId + 1;

    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

// save the new user details to users.txt
int saveUser(int id, char *username, char *password) {
    FILE *file = fopen("data/users.txt", "a");
    if (!file) {
        perror("Could not open users file for writing");
        return -1;  // Error opening file
    }

    // Write the new user to the file
    fprintf(file, "%d %s %s\n", id, username, password);
    fclose(file);

    return 0;  // Successful save
}
// read users.txt to find the highest existing user ID and return the next available ID.
int determineUserId() {
    FILE *file = fopen("data/users.txt", "r");
    if (!file) {
        perror("Could not open users file for reading");
        return -1;  // Error opening file
    }

    int maxId = -1;  // Start with -1 to indicate no users found
    int id;
    char username[50], password[50];

    // Read through the file to find the highest ID
    while (fscanf(file, "%d %s %s", &id, username, password) == 3) {
        if (id > maxId) {
            maxId = id;  // Update maxId if a higher ID is found
        }
    }

    fclose(file);
    return maxId + 1;  // Return the next available user ID
}

void updateAccount( struct User u)
{
    struct Record r;
    struct User user;
    int AccountNum;
    system("clear");

    printf("\t\t\t===== Update Account for %s=====\n",u.name);
    printf("\n Enter the account number: ");
    scanf("%d",&AccountNum);

    // check user has account
    FILE *pf = fopen(RECORDS,"r");
    if (pf == NULL){
        perror("Could not open records file");
        return;
    }

    int accountFound = 0;

    while (getAccountFromFile(pf,user.name,&r)){
        if (strcmp(u.name,user.name) == 0 && AccountNum == r.accountNbr){
            accountFound = 1;

            int option;
            printf("\nChoose the field to change:\n\t-> 1: Phone Number\n\t-> 2: Country\n\n\tEnter your choice(1 or 2): ");
            scanf("%d", &option);

            switch (option) {
                case 1:
                    printf("\nEnter your new phone number:");
                    scanf("%d",&r.phone);
                    break;
                case 2:
                    printf("\nEnter your new country:");
                    scanf("%s",r.country);
                    break;
                default:
                    printf("Invalid option selected.\n");
                    fclose(pf);
                    return;
            }
            break;
        }
    }

    fclose(pf);


    if (accountFound) {
        updateRecord(r);
        success(u);
    } else {
        printf("Account ID not found!\n");
    }

}


void updateRecord(struct Record r) {
    struct Record records[100];
    FILE *pf = fopen(RECORDS, "r");
    int recordCount = 0;

    if (pf == NULL) {
        perror("Could not open file");
        return;
    }

    // Read records from the file
    while (fscanf(pf, "%d %d %s %d %d/%d/%d %s %d %lf %s\n",
                  &records[recordCount].id, &records[recordCount].userId, records[recordCount].name, 
                  &records[recordCount].accountNbr, &records[recordCount].deposit.month, 
                  &records[recordCount].deposit.day, &records[recordCount].deposit.year, 
                  records[recordCount].country, &records[recordCount].phone, 
                  &records[recordCount].amount, records[recordCount].accountType) != EOF) {
        recordCount++;
    }
    fclose(pf);

    printf("the name is%s", r.name);
    // Update matching record
    for (int i = 0; i < recordCount; i++) {
        if (1) {
            // strcpy(records[i].country, r.country);
            // records[i].phone = r.phone;
            // if (strcmp(records[i].name,r.name)== 0)
            {
                 printf(":%s:%s:\n", records[i].name,r.name);
            }
           
        }
    }


    // Write updated records to the file
    FILE *file = fopen(RECORDS, "w");
    if (file == NULL) {
        perror("\n\t\tFailed to open file");
        return;
    }

    for (int i = 0; i < recordCount; i++) {
        struct User u;
        u.id = records[i].userId;
        strcpy(u.name, records[i].name);
        saveAccountToFile(file, u, records[i]);
    }
    fclose(file);

    printf("\n\t\t✔ Account information updated successfully.\n");
}

