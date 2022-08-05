#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    int p[2];
    int buf[64];
    int cnt = 34;

    for(int i = 0; i < 34; i++){
        buf[i] = i+2;
    }

    while(cnt){
        pipe(p);
        write(p[1], buf, cnt*sizeof(int));
        close(p[1]);
        if(fork()){
            wait(0);
            exit(0);
        }

        int prime[2];
        int n[64];
        cnt = 0;
        
        read(p[0], prime, sizeof(int));
        printf("prime %d\n", prime[0]);
        while(read(p[0], n+cnt, sizeof(int))){
            if(n[cnt]%prime[0]){
                cnt++;
            }
        }
        memcpy(buf, n, cnt*sizeof(int));
        close(p[0]);
    }
    exit(0);
}