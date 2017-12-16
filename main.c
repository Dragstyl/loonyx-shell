#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

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

void tee(char *command[]) {

}

void wordCount(char *command[]) {
	FILE *readfile;
	int characters;
	int words = 0;
	if(!(readfile = fopen(command[1], "r"))) {
		printf("Filename invalid\n");
		exit(1);
	}
	if(readfile) {
		while((characters = getc(readfile)) != EOF) {
			if(characters == ' ' || characters == '\n' || characters == '\0')
				words++;
		}
	}

	printf("%d\n", words);
}

void changeDirectory(char *command[]){
	if(command[1] == NULL){
		printf("No directory specified\n");
	}
	else if(strcmp(command[1], "..") == 0){
		chdir("..");
	}
	else if(chdir(command[1]) == -1) {
		printf("Directory doesn't exist or unknown error\n");
	}
	else {
		chdir(command[1]);
	}
};

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
	char *line;
	char *itr;
	int iterat = 0;
	char *command[255];

	while(1) {
        
	/* Displaying prompt and accepting command */
	line = readline("$>");
	/* Adding history support with up and down */
	add_history(line);

	/* Reset command */
	memset(command, '\0', 255);
	
	/* Turn command into a list of arguments */
	itr = strtok(line, " ");
	while(itr != NULL) {
		command[iterat++] = itr;
		itr = strtok(NULL, " ");
	}
	iterat = 0;
	
	/* Run command */
	runCommand(command);
    }
    return 0;
}