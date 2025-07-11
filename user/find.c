#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char*
fmtname(char *path)
{
    char *p;
    // Find first character after last slash.
    for(p=path+strlen(path); p >= path && *p != '/'; p--) ;

    return p + 1; // Return the name after the last slash
}

void
find(char *path, char* filename)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    if((fd = open(path, O_RDONLY)) < 0){
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
    }

    if(strcmp(fmtname(path), filename) == 0)
        printf("%s\n", path);

    if (st.type == T_DIR) {
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
            printf("find: path too long\n");
            close(fd);
            return;
        }    
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';
        
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = '\0';

            if(stat(buf, &st) < 0){
            printf("find: cannot stat %s\n", buf);
            continue;
            }

            char* cur_file = fmtname(buf);
            if (cur_file[0] == '.' && (cur_file[1] == '\0' || (cur_file[1] == '.' && cur_file[2] == '\0')))
                continue; // Skip "." and ".."
            find (buf, filename);
        }
    }
    close(fd);
}

int main(int argc, char *argv[]){
    if (argc < 2) {
        fprintf(2, "Usage: find <directory> <filename>\n");
        exit(1);
    }
    if (argc < 3) {
        find(".", argv[1]);
        exit(1);
    }

    char *path = argv[1];
    char *filename = argv[2];
    find(path, filename);
    return 0;
}