#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


//Trim the extra newline character that fgets takes in

void trim_newline(char *str){
	str[strcspn(str, "\n")] = '\0';
}


int main(){
	char filename[100];
	char output[100];

	printf("Enter C/C++ filename: ");
	fgets(filename, sizeof(filename), stdin);
	trim_newline(filename);

	//check if file exists
	if (access(filename, F_OK) != 0)
	{
		printf("ERR: File does not exist.\n");
		return 1;
	}

	printf("Enter output binary name: ");
	fgets(output, sizeof(output), stdin);
	trim_newline(output);


	//determine compiler
	const char *compiler = strstr(filename, ".cpp") ? "g++" : "gcc";

	//compile
	char compile_cmd[256];
	snprintf(compile_cmd, sizeof(compile_cmd), "%s \"%s\" -o \"%s\" -Wall", compiler, filename, output);
	printf("Compiling with %s\n", compile_cmd);

	int compile_status = system(compile_cmd);

	if (compile_status == 0)
	{
		printf("Compilation successful. Running the program:\n\n");
		char run_cmd[128];
		snprintf(run_cmd, sizeof(run_cmd), "./%s", output);
		system(run_cmd);
		
		// Optional: Clean up the binary
		remove(output);
	} else {
		printf("Compilation failed. Quitting zrunner.\n");
	}
	
	return 0;

}
