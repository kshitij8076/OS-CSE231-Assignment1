#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    
    printf("Parent is having ID %d\n", (int) getpid());
    int rc = fork();
    if ( rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if(rc == 0){
        printf("Child is having ID %d\n", (int) getpid());
        printf("My parent ID is %d\n", (int)getppid());
    }
    else{
        wait(NULL);
        printf("ID of P's Child is %d\n",rc);
    }
    return 0;
}
