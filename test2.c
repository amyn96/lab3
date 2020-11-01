#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

/*int main(void){
	
	int pipefds[2];
	int buffer;
	
	if(pipe(pipefds) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	int nombor = 22;
	
	printf("writing a number to pipe...\n");
	write(pipefds[1], &nombor, sizeof(nombor));
	printf("Done.\n\n");
	
	printf("reading number from pipe...\n");
	read(pipefds[0], &buffer, sizeof(buffer));
	printf("Done.\n\n");
	
	prinf("Number from pipe : %d\n", buffer);
	
	return EXIT_SUCCESS;

}*/

void primeOrNot(int val){
	
	int i, flag = 0;

	for (i = 2; i <= val / 2; ++i) {

        if (val % i == 0) {
            flag = 1;
            break;
        }
    } 
	
	if (val == 1) {
        printf("1 is neither prime nor composite.\n\n");
    }
	
    else {
		if (flag == 0) { 
			printf("%d is a prime number\n\n", val); 
		} 
		else { 
			printf("%d is not a prime number\n\n", val); 
		} 
	}
}

void sigint_handler(int sig){
    printf("Dont do that!!!! \n\n");
}


int main(void)
{
	void sigint_handler(int sig);
    int fd[2];
    int val = 0;




    // fork() returns 0 for child process, child-pid for parent process.
	while(1){
		if(signal(SIGINT,sigint_handler) == SIG_ERR){

			perror("signal1");
			exit(1);

		}
		pipe(fd);
		if (fork() != 0)
		{

			close(fd[0]);
			printf("Enter a number : "); 
			scanf("%d", &val);
			write(fd[1], &val, sizeof(val));
			close(fd[1]);
		}
		else
		{  
			close(fd[1]);
			read(fd[0], &val, sizeof(val));
			primeOrNot(val);
			close(fd[0]);
		}
	}
    return EXIT_SUCCESS;
}
