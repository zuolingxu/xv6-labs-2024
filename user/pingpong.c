#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    int pipeftc[2];
    pipe(pipeftc);
    int pipectf[2];
    pipe(pipectf);
    char ch = 'w';
    
    if (fork() == 0){
        char r;
        while(read(pipeftc[0], &r, 1) == 0) ;
        printf("%d: received ping\n", getpid());
        write(pipectf[1], (void *)&ch, 1);
    }
    else{
        char r;
        write(pipeftc[1], (void *)&ch, 1);
        while(read(pipectf[0], &r, 1) == 0) ;
        printf("%d: received pong\n", getpid());
        wait(0);
    }
    exit(0);
    return 0;
}