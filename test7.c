#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


void primeOrNot(int number){
	
	int i, flag = 0;

	for (i = 2; i <= number / 2; ++i) {

        if (number % i == 0) {
            flag = 1;
            break;
        }
    } 
	
	if (number == 1) {
        printf("1 is neither prime nor composite.\n\n");
    }
	
    else {
		if (flag == 0) { 
			printf("%d is a prime number\n\n", number); 
		} 
		else { 
			printf("%d is not a prime number\n\n", number); 
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
    int number = 0;

		if(signal(SIGINT,sigint_handler) == SIG_ERR){

			perror("signal1");
			exit(1);

		}
		
		pipe(fd);
		
		if (fork() != 0)
		{

			close(fd[0]);
			printf("Enter number : "); 
			scanf("%d", &number);
			write(fd[1], &number, sizeof(number));
			close(fd[1]);
			wait(NULL);
		}
		else
		{   
			close(fd[1]);
			read(fd[0], &number, sizeof(number));
			primeOrNot(number);
			close(fd[0]);
			exit(EXIT_SUCCESS);

		}
		
	return EXIT_SUCCESS;
}




