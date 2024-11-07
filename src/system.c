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
    char option[1];
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%s", option);
        if (option == "0")
            f(u);
        else if (option == "1")
            mainMenu(u);
        else if (option == "2")
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
        scanf("%s", option);
    }
    if (option == "1")
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
    struct Record r, cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    if (!pf)
    {
        printf("Error: Unable to open records file.\n");
        return;
    }

    // Determine the latest record ID
    int recordId = 0;
    FILE *rf = fopen(RECORDS, "r");
    if (rf)
    {
        while (fscanf(rf, "%d %*[^'\n]", &r.id) != EOF)
        {
            recordId = r.id;
        }
        fclose(rf);
    }
    
    int validEntry = 0;
    do
    {
        system("clear");
        printf("\t\t\t===== New Record =====\n");

        printf("\nEnter today's date (mm/dd/yyyy): ");
        if (scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year) != 3)
        {
            printf("Invalid date format. Please enter as mm/dd/yyyy.\n");
            while (getchar() != '\n');  // Clear invalid input from buffer
            continue;
        }

        printf("\nEnter the account number: ");
        if (scanf("%d", &r.accountNbr) != 1)
        {
            printf("Invalid account number. Try again.\n");
            while (getchar() != '\n');  // Clear invalid input from buffer
            continue;
        }

        // Check if account already exists for the user
        int accountExists = 0;
        rewind(pf);
        while (getAccountFromFile(pf, userName, &cr))
        {
            if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
            {
                printf("✖ This Account already exists for this user.\n\n");
                accountExists = 1;
                break;
            }
        }
        if (accountExists) continue;

        // Gather other details
        printf("\nEnter the country: ");
        scanf("%s", r.country);
        printf("\nEnter the phone number: ");
        if (scanf("%d", &r.phone) != 1)
        {
            printf("Invalid phone number. Try again.\n");
            while (getchar() != '\n');  // Clear invalid input from buffer
            continue;
        }
        printf("\nEnter amount to deposit: $");
        if (scanf("%lf", &r.amount) != 1 || r.amount < 0)
        {
            printf("Invalid amount. Try again.\n");
            while (getchar() != '\n');  // Clear invalid input from buffer
            continue;
        }

        printf("\nChoose the type of account:\n\t1 -> savings\n\t2 -> current\n\t3 -> fixed01(for 1 year)\n\t4 -> fixed02(for 2 years)\n\t5 -> fixed03(for 3 years)\n\n\tEnter your choice (1, 2, 3, 4, or 5): ");
        int option;
        if (scanf("%d", &option) != 1)
        {
            printf("Invalid choice. Setting account type as 'savings'.\n");
            option = 1;
            while (getchar() != '\n');
        }

        switch (option)
        {
        case 1: strcpy(r.accountType, "savings"); break;
        case 2: strcpy(r.accountType, "current"); break;
        case 3: strcpy(r.accountType, "fixed01"); break;
        case 4: strcpy(r.accountType, "fixed02"); break;
        case 5: strcpy(r.accountType, "fixed03"); break;
        default: 
            strcpy(r.accountType, "savings");
            printf("\nAccount type defaulted to Savings.\n");
            break;
        }

        // Set record ID and user ID, then save account
        u.id = getUserId(u);
        r.id = recordId + 1;

        saveAccountToFile(pf, u, r);
        fclose(pf);
        success(u);
        validEntry = 1;

    } while (!validEntry);
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

int getUserId(struct User u){
    FILE *pf = fopen("data/users.txt","r");
    struct User user;
    while (fscanf(pf, "%d %s %s", &user.id, user.name, user.password) == 3)
    {
        if (strcmp(u.name,user.name) == 0){
            fclose(pf);
            return user.id;
            
        }
    }
    fclose(pf);
    return -1;
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
            break;
        }
    }

    fclose(pf);
    strcpy(r.name,user.name);

    if (accountFound) {

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

    // Update matching record
    for (int i = 0; i < recordCount; i++) {            
        if (strcmp(records[i].name,r.name)== 0 && records[i].accountNbr == r.accountNbr){
           strcpy(records[i].country, r.country); // change country
            records[i].phone = r.phone; // change phone number
            records[i].amount = r.amount; // change amount
        }            
    }

    // Write updated records to the file
    FILE *file = fopen(RECORDS, "w");
    if (file == NULL) {
        perror("\n\t\tFailed to open file");
        return;
    }

    for (int i = 0; i < recordCount; i++) {
        struct User user;
        user.id = records[i].userId; // id of user
        strcpy(user.name, records[i].name); // name of user
        saveAccountToFile(file, user, records[i]);
    }
    fclose(file);
}

void checkAccounts(struct User u)
{
    int accountNbr;
    struct Record r;
    char username[50];
    double interest;

    FILE *pf = fopen(RECORDS,"r");
    if (pf == NULL) {
        perror("Could not open records file");
        return;
    }

    // ask for account id
    printf("\nEnter the account number:");
    scanf("%d", &accountNbr);
    
    system("clear");
    int accountFound = 0;
    // retrieve account info
    while (getAccountFromFile(pf,username,&r)) {
        if (strcmp(username,u.name) == 0 && r.accountNbr == accountNbr){
            accountFound = 1;
            printAccountDetails(r);
            break;
        }
    }

    fclose(pf);

    if (!accountFound) {
        printf("Account not found.\n");
        return;
    }
    
    if (strcmp(r.accountType,"fixed01") == 0 ){
        interest = r.amount * 0.04 ;
        printf("\nYou will get $%.2lf as interest on day %d/%d/%d\n",interest,r.deposit.month,r.deposit.day,r.deposit.year+1);
    } else if (strcmp(r.accountType,"fixed02") == 0)
    {
        interest = r.amount * 0.05;
        printf("\nYou will get $%.2lf as interest on day %d/%d/%d\n",interest*2,r.deposit.month,r.deposit.day,r.deposit.year+2);
    } else if (strcmp(r.accountType,"fixed03") == 0)
    {
        interest = r.amount * 0.08;
        printf("\nYou will get $%.2lf as interest on day %d/%d/%d\n",interest*3,r.deposit.month,r.deposit.day,r.deposit.year+3);
    }else if (strcmp(r.accountType,"savings") == 0)
    {
        interest = r.amount *0.07 / 12;
        printf("\nYou will get $%.2lf as interest on day %d of every month\n",interest,r.deposit.day);
    }else if (strcmp(r.accountType,"current") == 0)
    {
        printf("\nYou will not get interests because the account is of type current\n");
    }
    
    stayOrReturn(1,checkAccounts,u);
}

void makeTransaction(struct User u)
{
    struct User user;
    struct Record r;
    int option;
    int accNbr;
    int accountFound = 0;

    FILE *file = fopen(RECORDS,"r");
    if (file == NULL) {
        perror("Could not open records file");
        return;
    }

    printf("\nEnter the account number of the customer:");
    scanf("%d",&accNbr);

    // check user and account nbr exists
    // type of transaction
    while (getAccountFromFile(file,user.name,&r)){
        if (strcmp(u.name,user.name) == 0 && accNbr == r.accountNbr)
        {
            strcpy(r.name,user.name);
            accountFound = 1;
            break;
        }
    }

    fclose(file);

    

    if (accountFound){
        // check type of account
        if (strcmp(r.accountType,"fixed01") == 0 || 
            strcmp(r.accountType,"fixed02") == 0 || 
            strcmp(r.accountType,"fixed03") == 0 ) 
        {
            printf("You cannot deposit or withdraw cash in fixed accounts!\n");
            stayOrReturn(0,makeTransaction,u);
            return;
        }
        printf("\nDo you want to:\n\t\t1->Withdraw\n\t\t2->Deposit\nEnter your choice:");
        scanf("%d",&option);
        while (getchar() != '\n');  // Clear invalid input from buffer

        switch (option)
        {
        case 1: {
            double withdrawAmt;
            printf("Enter the amount:");
            scanf("%lf",&withdrawAmt);
            if (withdrawAmt > r.amount){
                printf("The amount you chose to withdraw is superior to your available balance!\n");
                stayOrReturn(0,makeTransaction,u);
                return;
            } else if (withdrawAmt <= 0.0){
                printf("The amount you chose to withdraw should be greater than $0.0\n");
                stayOrReturn(0,makeTransaction,u);
                return;
            } else{
                r.amount = r.amount - withdrawAmt;
                // printf("Withdraw Name:%s and Account Nbr:%d",r.name, r.accountNbr);
                updateRecord(r);
                printf("%s: Successfully withdrawn $%.2lf. New balance: $%.2lf\n",r.name, withdrawAmt, r.amount);
                success(u);
            }
            break;
        }
        case 2:{
            // amount to deposit
            // check for overflow :TODO
            double depositAmt;
            printf("Enter the amount:");
            scanf("%lf",&depositAmt);
            if (depositAmt <= 0.0){
                printf("The amount you chose to deposit is less than or equal to $0.0");
                // sleep(3);
                stayOrReturn(0,makeTransaction,u);
                return;
            }
            r.amount +=depositAmt;
            updateRecord(r);
            success(u);
            break;
        }
        default:
            printf("Invalid option selected.\n");
            stayOrReturn(1,makeTransaction,u);
            break;
        }

    } else{
        printf("Account not Found");
        while (getchar() != '\n');  // Clear invalid input from buffer
        stayOrReturn(0,makeTransaction,u);
    }
   
}


// void displayMessageWithDelay() {
//     printf("The amount you chose to deposit is less than or equal to $0.0\n");
//     sleep(3); // Sleep for 3 seconds
// }

void deleteAccount(struct User u)
{

    struct User user;
    struct Record r;
    int accountFound = 0;
    int accNbr;
    FILE *file = fopen(RECORDS,"r");
    if (file == NULL) {
        perror("Could not open records file");
        return;
    }
    printf("\nEnter the account number of the customer:");
    scanf("%d",&accNbr);

    // check user and account nbr exists
    // type of transaction
    while (getAccountFromFile(file,user.name,&r)){
        if (strcmp(u.name,user.name) == 0 && accNbr == r.accountNbr)
        {
            strcpy(r.name,user.name);
            accountFound = 1;
            break;
        }
    }

    fclose(file);

    

    if (accountFound){
        // delete record
        // print out the details
        system("clear");
        printf("\t\t====== Deleted account for user, %s =====\n\n", u.name);
        printAccountDetails(r);

    deleteRecord(r);
    printf("\n\t\t✔ Account deleted successfully.\n");
    stayOrReturn(1,deleteAccount,u);

    } else {
        while (getchar() != '\n');
        stayOrReturn(0,deleteAccount,u);
    }
}

void deleteRecord(struct Record r) {
    struct Record records[100];
    FILE *pf = fopen(RECORDS, "r");
    int recordCount = 0;
    int recordToDelete;

    // printf("\n%s:%f",r.name,r.amount);
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

    // Update matching record
    for (int i = 0; i < recordCount; i++) {            
        if (strcmp(records[i].name,r.name)== 0 && records[i].accountNbr == r.accountNbr){
           recordToDelete = i;
        }            
    }

   // Write updated records to the file
    FILE *rf = fopen(RECORDS, "w");
    if (rf == NULL) {
        perror("\n\t\tFailed to open file");
        return;
    }

    for (int i = 0; i < recordCount; i++) {
        struct User u;
        u.id = records[i].userId;
        strcpy(u.name, records[i].name);
        if (i != recordToDelete){
            saveAccountToFile(rf, u, records[i]);
        }   
    }
    fclose(pf);
}

void transferAccount(struct User u)
{ 
    int accNbr;
    struct User newOwner;
    struct Record userRecord;
    struct Record records[100];
    int recordCount = 0;
    int accountFound = 0;

    printf("Enter the account number you want to transfer ownership:");
    scanf("%d",&accNbr);

    FILE *file = fopen(RECORDS,"a+");
    if (file == NULL) {
        perror("Could not open file");
        return;
    }  
    // Load records into memory
    recordCount = loadRecords(file,records);

    // check account exists
    for (int i = 0; i < recordCount; i++){
        if (strcmp(records[i].name,u.name)==0 && records[i].accountNbr == accNbr){
            accountFound = 1;
            userRecord = records[i];
        }
    }

   
    if (accountFound){

        printf("\t\t====== Account for user:%s =====\n\n", u.name);
        printAccountDetails(userRecord);

        printf("\nWhich user you want to transfer ownership to (user name):");
        scanf("%49s",newOwner.name);

        // IF USER IS PRESENT || IF USER HAS AN ACCOUNT WITH SAME NUMBER:: TODO
        int userId = getUserId(newOwner);
        printf("%d",userId);
        if ( userId == -1){
            printf("User not Found");
            stayOrReturn(0,transferAccount,u);
            return;
            
        } else {
            // delete that account
            deleteRecord(userRecord);

            // Update matching record
            strcpy(userRecord.name,newOwner.name);
            newOwner.id = userId;
            
            // save account to file
            saveAccountToFile(file, newOwner, userRecord);
        
            fclose(file);                        
            success(u);
        }

    } else{

        //check user has that account, if not
        printf("\n\t\t No account found");
        stayOrReturn(0,transferAccount,u);
    }



}

void printAccountDetails(struct Record r){
    
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

int loadRecords(FILE *file, struct Record *records) {
    int count = 0;
    while (fscanf(file,  "%d %d %s %d %d/%d/%d %s %d %lf %s\n",
                  &records[count].id, &records[count].userId, records[count].name, 
                  &records[count].accountNbr, &records[count].deposit.month, 
                  &records[count].deposit.day, &records[count].deposit.year, 
                  records[count].country, &records[count].phone, 
                  &records[count].amount, records[count].accountType) != EOF) {
        count++;
    }
    return count;
}
