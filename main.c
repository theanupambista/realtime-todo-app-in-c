#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User
{
    int id;
    char first_name[20];
    char last_name[20];
    char username[20];
    char password[20];
};
struct Task
{
    int user_id;
    char task_name[100];
    int is_completed;
};
int is_logged_in = 0;

struct User current_user;
void showAllTask()
{
    int found = 0;
    FILE *taskPtr;
    struct Task task;
    taskPtr = fopen("tasks.txt", "r");
    while (fread(&task, sizeof(struct Task), 1, taskPtr) > 0)
    {
        if (current_user.id == task.user_id)
        {
            found += 1;
            printf("\n\t\t\t%s\n", task.task_name);
        }
    }
    if (!found)
    {
        printf("\n\t\t\tRecord not found\n");
    }
    fclose(taskPtr);
    printf("\n\t\t\tPress any key to continue.");
    getch();
}
void addTask()
{
    char another;
    FILE *taskPtr;
    int n, i;
    struct Task task;
    char temp;
    do
    {
        system("cls");
        printf("\t\t\t\t=======Add Task=======\n\n\n");
        taskPtr = fopen("tasks.txt", "a"); // use can give any file name. Give the name with extention or without extention.

        printf("\n\t\t\tEnter Task     : ");
        scanf("%c", &temp); // temp statement to clear buffer
        scanf("%[^\n]", &task.task_name);

        if (taskPtr == NULL)
        {
            fprintf(stderr, "can't open file");
        }
        else
        {
            task.user_id = current_user.id;
            task.is_completed = 0;
            fwrite(&task, sizeof(struct Task), 1, taskPtr);
            fclose(taskPtr);
            printf("\t\t\tRecord stored successfuly\n");
        }

        printf("\t\t\tYou want to add another record?(y/n) : ");

        scanf("%s", &another);

    } while (another == 'y' || another == 'Y');
}
void dashBoard()
{
    system("cls");
    if (is_logged_in == 1)
    {
        printf("\t\t\tHello %s %s\n\n", current_user.first_name, current_user.last_name);
        int choice;
        while (choice != 5)
        {
            printf("\t\t\t=====TODO LIST MANAGEMENT SYSTEM=====");
            printf("\n\n\n\t\t\t\t     1. Add Task\n");
            printf("\t\t\t\t     2. All Task\n");
            printf("\t\t\t\t     3. Search Task\n");
            printf("\t\t\t\t     4. Delete Task\n");
            printf("\t\t\t\t     5. Exit\n");
            printf("\t\t\t\t    _____________________\n");
            printf("\t\t\t\t     ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                system("cls");
                addTask();
                system("cls");
                break;
            case 2:
                system("cls");
                showAllTask();
                system("cls");
                break;
            }
        }
    }
}
void textToVoiceConverter(char phrase[])
{
    char charCommand[100];
    strcpy(charCommand, "espeak -v +m2 \"");
    strcat(charCommand, phrase);
    strcat(charCommand, "\"");
    system(charCommand);
}
int getId()
{
    int id = 1;
    FILE *userPtr;
    struct User user;
    userPtr = fopen("username.txt", "r");
    while (fread(&user, sizeof(struct User), 1, userPtr) > 0)
    {
        id += 1;
    }
    fclose(userPtr);
    return id;
}
int isValidUsername(char username[])
{
    FILE *userPtr;
    struct User user;
    userPtr = fopen("username.txt", "r");
    while (fread(&user, sizeof(struct User), 1, userPtr) > 0)
    {
        if (strcmp(user.username, username) == 0)
        {
            fclose(userPtr);
            return 0;
        }
    }
    fclose(userPtr);
    return 1;
}
void loginAccount()
{
    system("cls");
    char username[20];
    char password[20];
    FILE *userPtr;
    struct User user;
    userPtr = fopen("username.txt", "r");
    if (is_logged_in == 2)
    {
        printf("\033[0;31m"); // set text color to red
        printf("\t\t\t\t===Incorrect Credentials===\n");
        printf("\033[0m");
    }
    printf("\t\t\t\t=======Login=======\n\n\n");
    printf("\t\t\tEnter Username : ");
    scanf("%s", &username);
    printf("\t\t\tEnter Password : ");
    char ch;
    int i = 0;
    while (1)
    {
        ch = getch();
        if (ch == 13)
        {
            break;
        }
        if (ch != 8)
        {
            password[i++] = ch;
            printf("*");
        }
    }
    // scanf("%s", &password);
    while (fread(&user, sizeof(struct User), 1, userPtr) > 0)
    {
        if (strcmp(user.username, username) == 0)
        {
            if (strcmp(user.password, password) == 0)
            {
                is_logged_in = 1;
                current_user = user;
                printf("login successfully\n");
                printf("name: %s %s\n", current_user.first_name, user.last_name);
                dashBoard();
            }
            // else
            // {
            //     printf("Incorrect credentials");
            //     break;
            // }
        }
    }
    fclose(userPtr);
    if (is_logged_in != 1)
    {
        is_logged_in = 2;
        loginAccount();
    }
}
void registerAccount()
{
    system("cls");
    FILE *userPtr;
    struct User user;
    char password[20];
    printf("\t\t\t\t=======Register your account!=======\n\n\n");
    userPtr = fopen("username.txt", "a"); // use can give any file name. Give the name with extention or without extention.

    printf("\n\t\t\tEnter First Name     : ");
    scanf("%s", &user.first_name);
    printf("\n\t\t\tEnter Last Name     : ");
    scanf("%s", &user.last_name);
    printf("\n\t\t\tEnter Username : ");
    scanf("%s", &user.username);
    printf("\n\t\t\tEnter Password       : ");
    scanf("%s", &user.password);
    printf("\n\t\t\t______________________________\n");

    if (userPtr == NULL)
    {
        fprintf(stderr, "can't open file");
    }
    else
    {
        int isValid = isValidUsername(user.username);
        if (isValid)
        {
            user.id = getId();
            memcpy(user.password, password, sizeof(password));
            // user.password = *(&password);
            fwrite(&user, sizeof(struct User), 1, userPtr);
            printf("\t\t\tRegistered successfuly\n");
        }
        else
        {
            printf("\t\tUsername already taken.");
        }
    }
    fclose(userPtr);
}
void main()
{

    int isFirstTime;
    FILE *fp;
    if (access("username.txt", F_OK) == 0)
    {
        char email[30];
        char password[10];
        fp = fopen("username.txt", "r");
        if (fp != NULL)
        {
            fseek(fp, 0, SEEK_END);
            int size = ftell(fp);

            if (size == 0)
            {
                // textToVoiceConverter("Welcome back again. You have not created account yet. Please create your account to use the app.");
                registerAccount();
            }
            else
            {
                loginAccount();
                // registerAccount();
            }
        }
        else
        {
            printf("cannot open file.");
        }
    }
    else
    {
        registerAccount();
    }
}