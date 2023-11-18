#include <sys/wait.h>  
#include <stdlib.h>  
#include <stdio.h>
#include <unistd.h>  

const int N = 1;
int main(void) {
    pid_t pids[N];
    int i;
  
    for (i = N; i >= 0; --i) {
        pids[i] = fork();
        if (pids[i] == 0) {
            sleep(i+1);
            _exit(0);
        }
        else printf("Child %d started\n", pids[i]);
    }
    if (!pids[0]) return 0;
    for (i = N; i >= 0; --i) {
        sleep(3);
        printf("Child %d stopped\n", wait(NULL));
    }
    return 0;
}  