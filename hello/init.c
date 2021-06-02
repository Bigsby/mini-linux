#include <stdio.h>
#include <unistd.h>
#include <string.h>

void printUsage()
{
    printf("Welcome to Bigsby Linux\n\n");

    printf("To quit just enter 'quit'\n");
}

int main()
{
    printUsage();
    int go = 1;
    char input[50];
    while (go)
    {
        printf("> ");
        fgets(input, 50, stdin);
        if (strncmp(input, "quit", 4) == 0)
            go = 0;
    }
}
