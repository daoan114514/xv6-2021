#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    int cnt = 0;
    char buf[512];
    char* newargv[32];

    newargv[0] = argv[1];
    newargv[1] = argv[2];
    newargv[3] = 0;

    while(read(0, buf+cnt, 1)){
        if(buf[cnt] == '\n'){
            if(!fork()){
                buf[cnt] = '\0';
                newargv[2] = buf;
                exec(argv[1], newargv);
            } else {
                wait(0);
                cnt = -1; 
            }
        }
        cnt++;
    }
    exit(0);
}