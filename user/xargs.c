#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"

const int BUFF_SIZE = 100;
char nextline[] = "\n\r\v";

int get_arg(char* buff, int max, int* last){
    int len = 0;
    for(; len < max - 1; len++){
        char ch;
        int j = 0; 
        while(read(0, &ch, 1) != 1) {
            if (j == 3){
                *last = 1;
                buff[len] = '\0';
                return len;
            }
            j++;
        }
        if(strchr(nextline, ch)){
            buff[len] = '\0';
            return len;
        }
        buff[len] = ch;
    }
    return len;
}

void run_cmd(char* exec_name, int argc, char* argv[]){

}

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Usage: xargs [command]\n");
        exit(1);
    }
    int last = 0;
    char* subcmd_argv[MAXARG];
    int subcmd_argc = 0;
    for (int i = 1; i < argc; i++)
        subcmd_argv[subcmd_argc++] = argv[i];

    while(1){  
        char buffer[BUFF_SIZE];
        int len = get_arg(buffer, BUFF_SIZE, &last);
        if (last)
            break;

        if(len != 0){
            subcmd_argv[subcmd_argc] = (char *)malloc(len);
            strcpy(subcmd_argv[subcmd_argc], buffer);
        } else {
            continue;
        }

        subcmd_argv[subcmd_argc + 1] = 0; // null-terminate the argument list
        if (fork() == 0){
            exec(subcmd_argv[0], subcmd_argv);
            exit(0);
        }
        wait(0);
        free((void *)subcmd_argv[subcmd_argc]);
    }
    exit(0);
    return 0;
}