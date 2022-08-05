#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    int p[2];
    char buf[2];
    pipe(p);
    if(!fork()){
        read(p[0], buf, 1);
        printf("%d: received ping\n", getpid());
        write(p[0], "\n", 1);
        close(p[0]);
        close(p[1]);
    } else {
        write(p[1], "\n", 1);
        read(p[1], buf, 1);
        wait(0);
        printf("%d: received pong\n", getpid());
        close(p[0]);
        close(p[1]);
    }
    exit(0);
}