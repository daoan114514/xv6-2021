#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    int p[2];
    char buf[2];
    pipe(p);
    if(!fork()){
        close(p[1]);
        read(p[0], buf, 1);
        printf("%d: received ping\n", getpid());
        write(p[0], "\n", 1);
        close(p[0]);
    } else {
        close(p[0]);
        write(p[1], "\n", 1);
        wait(0);
        read(p[1], buf, 1);
        printf("%d: received pong\n", getpid());
        close(p[1]);
    }
    exit(0);
}