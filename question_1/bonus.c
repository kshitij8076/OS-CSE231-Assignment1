#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int factorial(int n){
    if(n == 0) return 1;
    return n * factorial(n-1);
}

void fibonacci(int n){
    int first = 0;
    int second = 1;
    for(int i = 0;i<n;i++){
    	
        printf("%d " ,first);
    	int temp = first;
    	first = second ;
    	second = second + temp;
    	}
    	printf("\n");
    
}

int main() {
    __pid_t pid = fork();
    int fact = 0;
    if(pid < 0 ){
        fprintf(stderr,"Fork Failed\n");
        exit(1);
    }
    else if(pid == 0){
        wait(NULL);
        fact = factorial(4);
        printf("I am child %d and factorial of 4 is %d\n",(int) getpid(),fact);
        exit(1);
    }
    else{
        
        printf("I am parent %d and fibonnaci upto 16 is  ",(int) getpid());
        fibonacci(16);
    }
    return 1;
}
