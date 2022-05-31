
/*
#include <sys/stat.h>
#include <sys/types.h>

int mkdir(const char *path, mode_t mode); : path로 한 dir 만듬, mode는 권한 지정
- mkdir 에러 종류
ENONET - 상위 디렉터리가 없는경우
ENOTDIR - 상위 디렉터리가 디렉터리가아니라 파일인경우
EEXIST - 이미 존재하는경우
EPERM : 변경 권한이없는경우

mode_t umask(mode_t mask); : ps의 umask를 mask로 변경, 이전의 umask 반환, 절대 실패 x
 * umask : ps 속성으로 8진수 보통 022, mode(파일,dir 권한)가 그대로 사용되지 않고 umask 적용된 결과가 사용됨.
        open(), mkdir()시 mode & ~umask한게 실제 권한으로 사용됨  
                  rwx rwx rwx
    mode    777 : 111 111 111
    umask   022 : 000 010 010
    real    755 : 111 101 101
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    int i;

    if (argc < 2){
        fprintf(stderr, "%s : no argument\n", argv[0]);
        exit(1);
    }
    for (i=1; i < argc; i++){
        if (mkdir(argv[i], 0777) <0){
            perror(argv[i]);
            exit(1);
        }
    }
    exit(0);
}