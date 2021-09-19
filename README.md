# SHELL BY Aditya Malhotra
## cd() in cd_b.c file
This command is made using chdir whereas egde cases like<br>
cd - is taken care by storing OLD PWD<br>
cd ~/dir is taken by manipulating strings
## dis() in display.c
This is used to display the prompt
## echo() in echo_b.c
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
This contains function that are executed on singly linked list this linked list conatins process id and process name
## ls() in ls_b.c
Implements ls command, taken care of 2 flags -l and -a given by user in any order
## main.c
1. Set signal
2. Reading history
3. Getting other essemtial things like tilda
4. Taking input
5. Tokenize them and execute
## pinfo() in pinfo.c
To display inpformation of pid given by user
## pwd() in pwd_b.c
Print the current directory
## repeat() in repeat.c
Implementation of repeat function
## Some Assumptions
1. Path length, input string will be less than 1024 charcters
2. Pinfo prints both virtual memory address/mapping and virtual memory size
