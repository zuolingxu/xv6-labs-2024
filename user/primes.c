#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

const int MAX_PRIME = 280;
void primes(int, int, int, int) __attribute__((noreturn));

void primes(int prime, int pipe_read, int pipe_p_read, int pipe_p_write){
    printf("prime %d\n", prime);
    close(pipe_p_write);
    close(pipe_p_read);
    int pipe_write = -1;

    int sub_proc = 0;
    int next = prime;
    while(next != -1){
        if (next % prime != 0) {
            if (sub_proc == 0) { 
                int pipeptc[2];
                if(pipe(pipeptc) < 0){
                    printf("pipe error\n");
                    exit(1);
                }
                pipe_write = pipeptc[1];
                
                if (fork() == 0){
                    primes(next, pipeptc[0], pipe_read, pipe_write);
                } else {
                    close(pipeptc[0]);
                    sub_proc = 1;
                }
            } else {
                write(pipe_write, (void *)&next, sizeof(next));
            }
        }
        while(read(pipe_read, (void *)&next, sizeof(next)) == 0) ;
    }
    write(pipe_write, (void *)&next, sizeof(next));
    close(pipe_write);
    close(pipe_read);
    if (sub_proc) {
        wait(0);
    } 
    exit(0);
}

int main(){
    printf("prime 2\n");
    int pipeptc[2];
    if(pipe(pipeptc) < 0){
        printf("pipe error\n");
        exit(1);
    }
    int pipe_write = pipeptc[1];

    if(fork() == 0){
        primes(3, pipeptc[0], -1, pipe_write);
    }
    close(pipeptc[0]);

    for(int i = 4; i <= MAX_PRIME; i ++){
        if(i % 2 != 0){
            write(pipe_write, (void *)&i, sizeof(i));
        }
    }
    // pass an end number to sub-process (if not passed, the sub-process will not exit)
    int end = -1;
    write(pipe_write, (void *)&end, sizeof(end));
    close(pipe_write);
    wait(0);
    exit(0);
}