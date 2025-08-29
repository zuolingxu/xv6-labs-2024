#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

int
main(int argc, char *argv[])
{
  // your code here.  you should write the secret to fd 2 using write
  // (e.g., write(2, secret, 8)

  char secret[8];
  char *end = sbrk(PGSIZE*32);
  int flag;
  for (int i = 0; i < 32; i++) {
    flag = 1;
    for (int j = 0; j < 7; j++) {
      char c = end[32+j];
      if ((c >= 'a' && c <= 'f') || c == '.' || c == '/') {
        secret[j] = c;
      } else {
        flag = 0;
        break;
      }
    }
    if (flag) break;
    end += PGSIZE;
  }
  secret[7] = '\0';
  write(2, secret, 8);


  exit(1);
}
