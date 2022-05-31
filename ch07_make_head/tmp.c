#include <unistd.h>

int main(int argc, char *argv[])
{
    char tmp = 'a';
    write(1, &tmp, 1);
}