#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./DashBoardController.c"

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
    // char ch;
    // int i = 0;
    // while (1)
    // {
    //     ch = getch();
    //     if (ch == 13)
    //     {
    //         break;
    //     }
    //     if (ch != 8)
    //     {
    //         password[i++] = ch;
    //         printf("*");
    //     }
    // }
    scanf("%s", &password);
    while (fread(&user, sizeof(struct User), 1, userPtr) > 0)
    {
        if (strcmp(user.username, username) == 0)
        {
            if (strcmp(user.password, password) == 0)
            {
                is_logged_in = 1;
                current_user = user;
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
            fwrite(&user, sizeof(struct User), 1, userPtr);
            printf("\t\t\tRegistered successfuly\n");
            textToVoiceConverter("Account created successfully");
            // loginAccount();
        }
        else
        {
            printf("\t\tUsername already taken.");
        }
    }
    fclose(userPtr);
}
