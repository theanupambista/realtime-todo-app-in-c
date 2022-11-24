#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// custom includes
#include "./modals/user.c"
#include "./modals/task.c"
#include "./helpers/helpers.c"
#include "./controllers/AuthController.c"

void main()
{
    SetConsoleTitle("TODO LIST MANAGEMENT SYSTEM");
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
                registerAccount();
            }
            else
            {
                int choice;
                while (choice != 3)
                {
                    printf("\t\t\t=====TODO LIST MANAGEMENT SYSTEM=====");
                    printf("\n\n\n\t\t\t\t     1. Register Account\n");
                    printf("\t\t\t\t     2. Login\n");
                    printf("\t\t\t\t     3. Exit\n");
                    printf("\t\t\t\t    _____________________\n");
                    printf("\t\t\t\t     ");
                    scanf("%d", &choice);
                    switch (choice)
                    {
                    case 1:
                        system("cls");
                        registerAccount();
                        system("cls");
                        break;
                    case 2:
                        system("cls");
                        loginAccount();
                        system("cls");
                        break;
                    }
                }
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
