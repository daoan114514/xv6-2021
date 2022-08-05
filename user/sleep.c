#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if(argc < 2){
        fprintf(2,"you should pass an argument");
        exit(1);
    }
    int n = atoi(argv[0]);
    sleep(n);
    exit(0);
}