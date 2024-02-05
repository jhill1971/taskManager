# Command-Line Task Manager
## By James Hill

##  Purpose:
### This program provides the user with a command-line based task manager. The task manager has CRUD capabilites allowing the user to create a task, view a color-coded list of all tasks, update a task to "complete", and delete a task.

##  Functions:
### main()
#### The main() function opens by creating an array to hold the tasks, with a maximun of 200 tasks. Next, the program loads existing tasks from the CSV file and places them in the array. It then checks for command-line arguments. If no flag is provided by the user, then the help() function is called in order to show the user what flags are available. Otherwise, the flag in argv[1] is passed to a switch statement that determines the next function to be called. The main() function closes by writing the contents of the tasks array to CSV file before exiting.
### help()
#### When the help() function is called, it displays the program name, programmer details, and the year. Below the credits, a list of command-line flags and their usage information is displayed. Following that, a list of options for each flag is displayed. 
### create() First, the function checks if the task array is full (200 items), then it prompts the user to enter the task description. If one exisits, the newline character at the end of the task is removed. The function then adds a unique task id to the item and adds it to the array with a status of INCOMPLETE. Finally, a confirmation message is displayed to the user.
####
### view() 
#### This function displays a list of all tasks to the user. Incomplete tasks are colored amber, while complete tasks are colored red. 
### update() 
#### The update() function allows uaera to mark as task as complete by specifying its task id. First of all, the user is prompted to enter the id number of the task he or she wishes to mark as complete. If the task id is not found in the array, an error message is displayed. If the operation is successful, a comfirmation message is displayed to the user. 
### delete()
#### This function allows for the deletion of tasks. Firstly, the user is prompted for the task id of the item he or she wants to delete. If the task is found, it is deleted and the remaining tasks are shifted to fill the gap created by the deletion and the numer of tasks is decremented. If the task id is not found, an error message is displayed. Finally, a confirmation message is displayed.
### saveTasksToFile()
#### In this function, tasks.csv is opened for writing using fopen(). If the file cannot be opened, an error message is displayed. The function itereates through all of the tasks and writes them to the CSV file.
### loadTasksFromFile()
#### As above, the file tasks.csv is opened using fopen(). If it cannot be opened, an error message is returned. Otherwise, data is read from the file using fscanf(). The status integer is converted into the appropriate status  value (COMPLETE or INCOMPLETE). The data is added to the task list array, and finally fclose() is called to close the file.




