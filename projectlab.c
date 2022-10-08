#include  <stdio.h>
#include  <string.h>
#include <stdlib.h>
#include  <sys/types.h>
#include <time.h>


#define   MAX_COUNT  6

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(int);               /* parent process prototype */

void  main(void)
{
	pid_t  pid;
	pid = fork();
	if (pid == 0) {
		ChildProcess();
	}
	else if (pid > 0) {
		pid_t pid2 = fork();
		if (pid < 0) {
			printf("Fork failed");
		}
		else if (pid2 == 0) {
			ChildProcess();
		}
		else if (pid > 0) {
			int status1;
			int status2;
			pid_t id1 = wait(&status1);
			ParentProcess(id1);
			pid_t id2 = wait(&status2);
			ParentProcess(id2);
		}
	}
	else {
		printf("Fork failed");
	}
}

void  ChildProcess(void)
{
	int   i;
	int randomNumber = rand() % (30) + 1;
	srand(getpid());
	for (i = 1; i <= randomNumber; i++) {
		int sleepTime = rand() % (10) + 1;
		printf("Child Pid: %d is going to sleep!%d\n", getpid(), sleepTime);
		sleep(sleepTime);
		printf("Child Pid: %d is awake!\nWhere is my Parent: %d!\n", getpid(), getppid());
	}
	exit(0);
}

void  ParentProcess(int val)
{
	printf("Child Pid: %d has completed\n", val);
}