#include <stdio.h>
#include <unistd.h>
#include <string.h>

void printSplash()
{
    printf(" ___ _         _         \n");
    printf("| _ |_)__ _ __| |__ _  _ \n");
    printf("| _ \\ / _` (_-< '_ \\ || |\n");
    printf("|___/_\\__, /__/_.__/\\_, |\n");
    printf("      |___/         |__/\n");
}

void clearScreen()
{
    printf("\033[2J");
    printf("\033[0;0f");
}

void printUsage()
{
    printf("\033[1;37mBigsby Linux v0.0.1\033[0m\n\n");
    printf("Available commads:\n");
    printf("\tclear\t\tclear screen\n");
    printf("\thelp\t\tprint this help\n");
    printf("\tquit\t\texit system\n");
}

int main()
{
    clearScreen();
    printSplash();
    printf("Welcome to Bigsby Linux\n\n");
    printUsage();
    int go = 1;
    char command[50];
    while (go)
    {
        printf("> ");
        fgets(command, 50, stdin);
        if (strncmp(command, "quit", 4) == 0)
            go = 0;
        else if (strncmp(command, "help", 4) == 0)
            printUsage();
        else if (strncmp(command, "clear", 4) == 0)
            clearScreen();
        else if (strlen(command) > 1)
            printf("Unknown command: %s", command);
    }
}
