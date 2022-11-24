#include <stdio.h>

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
