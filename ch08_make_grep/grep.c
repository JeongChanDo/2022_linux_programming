#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>


/*
정규표현식 규칙
. : 한 문자
* : 선형 패턴 0회 이상 반복
? : 생략가능
\ : 메타문자

libc에서 제공하는 정규표현식 API
#include <sys/types.h>
#include <regex.h>

int regcomp(regex_t *reg, const char *pattern,
     int flags); : pattern에 든 정규표현식 문자열을 regex_t로 반환, 결과는 reg에
void regfree(regex_t *reg); : regcomp로 확보한 메모리를 해제
int regexec(const regex_t *reg, const char *string, 
    size_t nmatch, regmatch_t pmatch[], int flags); : regex_t(패턴) + 문자열로 패턴찾음, 성공시 0 아니면 다른 값 반환
size_t regerror(int errcode, const regex_t *reg, 
    char *msgbuf, size_t msgbuf_size); : regcomp서 에러발생시 에러 코드 반환, 이 에러코드를 메시지로 변환
*/

static void do_grep(regex_t *pat, FILE *src);

int main(int argc, char *argv[])
{
    regex_t pat;
    int err;
    int i;
    
    if (argc < 2)
    {
        fputs("no pattern \n", stderr);
        exit(1);
    }

    err = regcomp(&pat, argv[1], REG_EXTENDED | REG_NOSUB | REG_NEWLINE);
    if (err != 0){
        char buf[1024];
        regerror(err, &pat, buf, sizeof buf);
        puts(buf);
        exit(1);
    }
    if (argc == 2){
        do_grep(&pat, stdin);
    }
    else {
        for (i = 2; i < argc; i++){
            FILE *f;
            
            f = fopen(argv[i], "r");
            if (!f){
                perror(argv[i]);
                exit(1);
            }
            do_grep(&pat, f);
            fclose(f);
        }
    }
    regfree(&pat);
    exit(0);
}


static void do_grep(regex_t *pat, FILE *src)
{
    char buf[4096];

    while (fgets(buf, sizeof buf, src))
    {
        if (regexec(pat, buf, 0, NULL, 0) == 0){
            fputs(buf, stdout);
        }
    }
}