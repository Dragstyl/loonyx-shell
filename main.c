#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

/*char toArguments(char *command) {
	char *arguments;
	arguments = strtok(command, " ");
	return *arguments;
}*/
void cat(char *command[]) {
	FILE *readfile;
	int characters;

	readfile = fopen(command[1], "r");
	if(readfile) {
		while((characters = getc(readfile)) != EOF)
			putchar(characters);
		fclose(readfile);
		printf("\n");
	}

}
void wordCount(char *command[]) {

}
void changeDirectory(char *command[]) {

}

void runCommand(char *command[]) {
	if(strcmp(command[0], "exit") == 0)
		exit(0);
	else if(strcmp(command[0], "clear") == 0)
        system("clear");
    else if(strcmp(command[0], "wc") == 0)
		wordCount(command);
	else if(strcmp(command[0], "cat") == 0)
		cat(command);
	else if(strcmp(command[0], "cd") == 0)
		changeDirectory(command);
    else
		printf("Unknown command\n");
}

int main(int argc, char *argv[]) {
	int no_of_args;
	char *line;    
	char *itr; int iterat = 0;
	char *command[255];
	
    while(1) {
        
	/* Displaying prompt and accepting command */
    line = readline("$>");
	
	/* Turn command into a list of arguments */
	itr = strtok(line, " ");
	while(itr != NULL) {
		command[iterat++] = itr;
		itr = strtok(NULL, " ");
	}
	iterat = 0;
	
	/* Run command */
	runCommand(command);
	
	/* Adding history support with up and down */
	add_history(line);
	
    }
    return 0;
}


