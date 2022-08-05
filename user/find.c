#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char* fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  *(buf+strlen(p)) = 0;
  return buf;
}

void find(char* path, char* file){
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    //要找的文件名不能是.或..
    if(!strcmp(file,".") || !strcmp(file,"..")){
        fprintf(2, "find: cannot find .\n");
        return;
    }

    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("find: path too long\n");
    } else {
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if(stat(buf, &st) < 0){
                printf("find: cannot stat %s\n", buf);
                continue;
            }
            char name[512];
            strcpy(name, fmtname(buf));
            // 跳过.和..
            if(!strcmp(name,".") || !strcmp(name, "..")) continue;
            if(!strcmp(name, file))
                printf("%s\n", buf);
            if(st.type == T_DIR)
                find(buf, file);
        }
    }

    close(fd);
}

int main(int argc, char* argv[])
{
    find(argv[1], argv[2]);
    exit(0);
}