/* command-line based task manager */
/* Programmer: James Hill. Houston, Texas. 2024 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants for file handling
#define FILENAME "tasks.csv"
#define MAX_DESCRIPTION_LENGTH 270

// Task Structure
typedef enum { INCOMPLETE, COMPLETE } TaskStatus;

typedef struct
{
    int task_id;
    char task_description[270];
    TaskStatus status;
} Task;

// Function Prototypes
void help();
void create(Task *tasks, int *num_tasks);
void view(Task *tasks, int *num_tasks);
void update(Task *tasks, int num_tasks);
void delete(Task *tasks, int *num_tasks);
void saveTasksToFile(Task *tasks, int *num_tasks);
void loadTasksFromFile(Task *tasks, int *num_tasks);

int main(int argc, char *argv[])
{
    // Array to hold tasks
    Task tasks[200];   // Max 200 tasks at one time
    int num_tasks = 0; // Current number of tasks in the array

    // Load tasks from file
    loadTasksFromFile(tasks, &num_tasks);

    // Check for command-line flags
    if (argc > 1)
    {
        switch (argv[1][1])
        {
            case 'h':
                // Display the help text
                help();
                break;
            case 'c':
                // Create a task
                create(tasks, &num_tasks);
                break;
            case 'r':
                // View all tasks
                view(tasks, &num_tasks);
                break;
            case 'u':
                // Update a task
                update(tasks, num_tasks);
                break;
            case 'd':
                // Delete a task
                delete (tasks, &num_tasks);
                break;
            default:
                printf("Unknown option: %s\n", argv[1]);
                help();
                break;
        }
    }
    else
    {
        // No command-line argument provided, display help text.
        help();
    }

    // Save tasks to file before exiting
    saveTasksToFile(tasks, &num_tasks);
    return 0;
}

/*This function displays a help text and credits for this program*/
void help()
{
    // Text color control
    const char *color_green = "\033[1;32m"; // Green
    const char *color_reset = "\033[0m";    // reset text color to default
    // Display help text in green
    printf("%s", color_green);
    printf("Command Line Task Manager\n");
    printf("By James Hill. Houston, Texas. 2024\n\n");
    printf("Usage:\n");
    printf("  project -h               Display this help text\n");
    printf("  project -c               Create a new task\n");
    printf("  project -r               View all tasks\n");
    printf("  project -u               Mark a task as completed\n");
    printf("  project -d               Delete a task\n\n");
    printf("Options:\n");
    printf("  -h, --help               Display this help text\n");
    printf("  -c, --create             Create a new task\n");
    printf("  -r, --read               View all tasks\n");
    printf("  -u, --update             Mark a task as completed\n");
    printf("  -d, --delete             Delete a task\n");
    printf("%s", color_reset);
}

/*This function allows the user to create a new task*/
void create(Task *tasks, int *num_tasks)
{
    // Check if the task list is full
    if (*num_tasks >= 200)
    {
        printf("The task list is full. Please condider making room.\n");
        return;
    }

    // Prompt the user to enter a task description
    printf("Enter task description (max %d characters): ", MAX_DESCRIPTION_LENGTH);
    char description[MAX_DESCRIPTION_LENGTH + 1]; // +1 for null terminator
    fgets(description, sizeof(description), stdin);

    // Remove newline character from description
    size_t len = strlen(description);
    if (len > 0 && description[len - 1] == '\n')
    {
        description[len - 1] = '\0';
    }

    // Add the new task to the task list
    tasks[*num_tasks].task_id = *num_tasks + 1; // Assign unique task id
    strncpy(tasks[*num_tasks].task_description, description, MAX_DESCRIPTION_LENGTH);
    tasks[*num_tasks].status = INCOMPLETE;

    // Increment the number of tasks
    (*num_tasks)++;

    // Display confirmation message
    printf("Task created successfully.\n");
}

void view(Task *tasks, int *num_tasks)
{
    // ANSI Escacpe codes for text colors
    const char *color_amber = "\033[38;2;255;176;0m"; // Amber RGB(255,176,0)
    const char *color_red = "\033[38;2;255;0;0m";     // Red RGB(255,0,0)
    const char *color_reset = "\033[0m";

    // Display header
    printf("Task ID\tStatus\tDescription\n");

    // Loop through all tasks
    for (int i = 0; i < *num_tasks; i++)
    {
        // Determine text color based on task status
        const char *color = (tasks[i].status == INCOMPLETE) ? color_amber : color_red;

        // Print task details
        printf("%d\t%s%s%s\t%s\n", tasks[i].task_id, color, (tasks[i].status == INCOMPLETE) ? "Incomplete" : "Complete",
               color_reset, tasks[i].task_description);
    }
}

/*This function allows the user to mark a task as complete*/
void update(Task *tasks, int num_tasks)
{
    // Prompt the user to enter the task ID to mark as completed
    printf("Enter the task ID to mark as completed: ");
    int task_id;
    scanf("%d", &task_id);

    // Search for the task with that ID
    int index = -1;
    for (int i = 0; i < num_tasks; i++)
    {
        if (tasks[i].task_id == task_id)
        {
            index = i;
            break;
        }
    }

    // Check if the task ID was found
    if (index == -1)
    {
        printf("Task with ID %d not found.\n", task_id);
        return;
    }

    // Mark the task as completed
    tasks[index].status = COMPLETE;
    // Display confirmation message
    printf("Task with id %d marked as completed.\n", task_id);
}

/*This function allows the user to delete a task*/
void delete(Task *tasks, int *num_tasks)
{
    // Prompt the user to enter the task ID to delete
    printf("ENter the task ID to delete: ");
    int task_id;
    scanf("%d", &task_id);

    // Search for the task with that ID
    int index = -1;
    for (int i = 0; i < *num_tasks; i++)
    {
        if (tasks[i].task_id == task_id)
        {
            index = i;
            break;
        }
    }

    // Check that the task ID was found
    if (index == -1)
    {
        printf("Task with ID %d not found.\n", task_id);
        return;
    }

    // Shift remaining tasks to fill the gap
    for (int i = index; i < (*num_tasks - 1); i++)
    {
        tasks[i] = tasks[i + 1];
    }

    // Decrement the number of tasks
    (*num_tasks)--;

    // Confirm deletion
    printf("Task with ID %d deleted successfully.\n", task_id);
}

/*This function handles writing tasks to the CSV file*/
void saveTasksToFile(Task *tasks, int *num_tasks)
{
    // Open the file
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL)
    {
        printf("Error: Unable to open file");
        return;
    }

    // Write task to the CSV file
    for (int i = 0; i < *num_tasks; i++)
    {
        fprintf(file, "%d,%d,%s\n", tasks[i].task_id, tasks[i].status, tasks[i].task_description);
    }

    // Close file after writing
    fclose(file);
}

/*This function handles loading the tasks from the CSV file*/
void loadTasksFromFile(Task *tasks, int *num_tasks)
{
    // Open the file
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("Error: unable to open file\n");
        return;
    }

    // Read task data from the file
    while (!feof(file))
    {
        // read task data from each line
        int id, status;
        char description[MAX_DESCRIPTION_LENGTH + 1]; // +1 for null terminator
        if (fscanf(file, " %d,%d,%270[^\n]", &id, &status, description) == 3)
        {
            // Add the task to the task list
            tasks[*num_tasks].task_id = id;
            tasks[*num_tasks].status = (status == 0) ? INCOMPLETE : COMPLETE;
            strncpy(tasks[*num_tasks].task_description, description, MAX_DESCRIPTION_LENGTH);
            (*num_tasks)++;
        }
    }

    // Close the file after reading
    fclose(file);
}
