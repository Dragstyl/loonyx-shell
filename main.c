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
	FILE *readfile;
	char *string;
	if(command[1] == NULL) {
		printf("No parameters specified\n");
		return;
	}
	else if(strcmp(command[1], "-a") == 0) {
		strcpy(string, *command+3);
		if(!(readfile = fopen(command[2], "a"))) {
			printf("Error opening file or filename invalid\n");
			return;
		}
		if(readfile) {
			fprintf(readfile, "%s", string);
			fclose(readfile);
		}
	}
	else {
		if(!(readfile = fopen(command[1], "w"))) {
			printf("Error\n");
			return;
		}
		if(readfile) {
			strcpy(string, *command+2);

		}
	}
}

void list(char *command[]) {

}

void wordCount(char *command[]) {
	FILE *readfile;
	int characters;
	int words = 0;
	int lines = 0;
	int longest = 0;
	if(command[1] == NULL) {
		printf("No parameter specified\n");
		return;
	}
	/* Line count */
	else if(strcmp(command[1], "-l") == 0) {
		if(!(readfile = fopen(command[2], "r"))) {
			printf("Filename invalid\n");
			return;
		}
		if(readfile) {
			while((characters = getc(readfile)) != EOF) {
				if(characters == '\n' || characters == '\0')
					lines++;
			}
		}
		printf("%d\n", lines);
		fclose(readfile);

		return;
	}
	/* Word Count */
	else if(strcmp(command[1], "-w") == 0) {
		if(!(readfile = fopen(command[2], "r"))) {
			printf("Filename invalid\n");
			return;
		}
		if(readfile) {
			while((characters = getc(readfile)) != EOF) {
				if(characters == ' ' || characters == '\n' || characters == '\0')
					words++;
			}
		}
		printf("%d\n", words);
		fclose(readfile);
		return;
	}
	/* Byte Count */
	else if(strcmp(command[1], "-c") == 0) {
		
	}
	/* Longest Line */
	else if(strcmp(command[1], "-L") == 0) {
		if(!(readfile = fopen(command[2], "r"))) {
			printf("Filename invalid\n");
			return;
		}
		if(readfile) {
			while((characters = getc(readfile)) != EOF) {
				if(characters == '\n'){

				}
					
			}
		}
	}

	else {
		printf("Something went wrong, possible wrong parameter. See \"man wc\"\n");
		return;
	}
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
	else if(strcmp(command[0], "tee") == 0)
		tee(command);
	else if(strcmp(command[0], "ls") == 0)
		list(command);
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

	/* Initalize or reset command */
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