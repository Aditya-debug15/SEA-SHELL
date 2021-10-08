# SHELL BY Aditya Malhotra
# Compiling
execute the given command to create an executable file<br>
`make`<br>
Now run<br>
`./shell.out`
## cd_b.c
This command is made using chdir whereas egde cases like<br>
cd - is taken care by storing OLD PWD<br>
cd ~/dir is taken by manipulating strings
## display.c
This is used to display the prompt
## echo_b.c
This is used to do echo using string manipulation and printf
## headers.h
It contains global varibale that will be used by different c files and contains headers for all files
## history.c
1. void readfromhistory(); to read from history.txt only to be used in the begining
2. void writetohistory(); to write to history.txt it is executed after exit is enetered by user
3. void commandhistory(int number); to implement history command , displays the name of recent commands based upon arguments
## leftover() leftover.c
This is used to take care of all the commands that are not implemented by me<br>
Uses fork and execvp to execute things in child process<br>
Parent waits for foreground<br>
## linkedfgs.c
This contains function that are executed on singly linked list this linked list conatins process id and process command and job number<br>
Additionally the linked list is stored in sorted order according to command name
## ls_b.c
Implements ls command, taken care of 2 flags -l and -a given by user in any order
## execute.c
2 functions execute and execute_withstring both performs same function just different inputs<br>
## main.c
1. Set signal
2. Reading history
3. Getting other essemtial things like tilda
4. Taking input
5. Tokenize them and execute
## pinfo.c
To display inpformation of pid given by user
## pwd_b.c
Print the current directory
## repeat.c
Implementation of repeat function
## ioredirect.c
Implements I/O redirection taken care of `<, >, >>`.
## pipe_b.c
Implements piping `command a | command b` where command a acts as input for command b
## jobs_b.c
Prints all the background process initiated by my shell<br>
Prints `[job number] (process state) (process name) [process pid]`<br>
Job number is unique for each process and process state have 2 options either it will be stopped or running<br>
Sorted by process name in case of ties they are sorted by job number.
## sig_b.c
Users can send signal to background process according to their job number.
## fg_b.c
To bring a background process into foreground
## bg_b.c
Changes the state of a stopped background job to running (int background).
## Ctrl+C       Ctrl+Z       Ctrl+D
1. Ctrl+C sends SIGINT signal to child foreground process if no foreground process it does nothing.
2. Ctrl+Z sends SIGSGTP signal to child foreground process thus sending it to background and the state becomes STOPPED.
3. Ctrl+D logs out of the shell, before logging out it writes to history and free memory used by linked list.
## exit command can also be used for exiting
## Some Assumptions
1. Path length, input string will be less than 1024 charcters
2. Pinfo prints both virtual memory address/mapping and virtual memory size
