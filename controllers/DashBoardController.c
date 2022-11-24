#include <stdio.h>
#include "./TaskController.c"

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