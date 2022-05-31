#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h> //directory entry

/*
#include <sys/types.h>
#include <dirent.h>
DIR *opendir(const char *path); : path 디렉터리 open 후 DIR 반환
struct dirent *readdir(DIR *d); : 디렉터리 스트림 d 읽어 struct dirent로 반환
int closedir(DIR *d); : 디렉터리 스트림 닫기
*/

static void do_ls(char *path);

int main(int argc, char *argv[]){
    int i;

    if (argc < 2){
        fprintf(stderr, "%s, no arguments\n", argv[0]);
        exit(1);
    }
    for (i = 1; i < argc; i++){
        do_ls(argv[i]);
    }
    exit(0);
}

static void do_ls(char *path){
    DIR *d;
    struct dirent *ent;

    d = opendir(path);
    if(!d){
        perror(path);
        exit(1);
    }
    while (ent = readdir(d)){
        printf("%s\n", ent->d_name);
    }
    closedir(d);
}