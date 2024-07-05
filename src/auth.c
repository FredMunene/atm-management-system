#include <termios.h>
#include "header.h"

char *USERS = "data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s",&userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}

void registerMenu()
{
    struct User newUser;
    struct termios oflags, nflags;
    //declare a pointer
    FILE *pf = fopen(USERS,"a+");

    system("clear");
    // get name
    printf("\n\n\n\t\t\t Bank Management System\n\t\t\t\t\t Registration\n\t\t\t\t\t Username: ");
    scanf("%s",newUser.name);

    // check that name is unique

    if (checkNameIsUnique(pf,newUser.name)) {
            printf("The user with the name '%s' is already registered\n",newUser.name);
    fclose(pf);
        exit(1);
    }

    

    // get id
    printf("\n\n\t\t\t\tid no: ");
    scanf("%d", &newUser.id);


    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }


    // get password
    printf("\n\n\t\t\t\tEnter the password to register:");
    scanf("%s", newUser.password);



    fprintf(pf,"%d %s %s\n",newUser.id,newUser.name,newUser.password);
    fclose(pf);
    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    } 
};

int checkNameIsUnique(FILE *pt,const char *r) {
    char line[50];
    while (fgets(line, sizeof(line), pt) != NULL) {
        char *token = strtok(line," ");
        token = strtok(NULL," ");

        if (token != NULL && strcmp(token,r) == 0) {
            return 1;
        }
    }
        return 0;
}
