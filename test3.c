#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void){
	
	int pipefds[2];
	int buffer;
	
	if(pipe(pipefds) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	int nombor;
	
	printf("Enter N :");
    scanf("%d",&nombor);
	
	printf("writing a number to pipe...\n");
	write(pipefds[1], &nombor, sizeof(nombor));
	printf("Done.\n\n");
	
	printf("reading number from pipe...\n");
	read(pipefds[0], &buffer, sizeof(buffer));
	printf("Done.\n\n");
	
	printf("Number from pipe : %d\n", buffer);
	
	return EXIT_SUCCESS;

}
