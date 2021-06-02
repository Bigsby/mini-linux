#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <linux/reboot.h>
#include <sys/syscall.h>
#include <sys/sysinfo.h>
#include <linux/fcntl.h>
#include <dirent.h>
#include <stdlib.h>

void quit()
{
    syscall(SYS_reboot, LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2, LINUX_REBOOT_CMD_POWER_OFF, 0);
}

char dTypeDisplay(char d_type)
{
    switch (d_type)
    {
        case DT_BLK:
            return 'b';
        case DT_CHR:
            return 'c';
        case DT_DIR:
            return 'd';
        case DT_FIFO:
            return 'f';
        case DT_LNK:
            return 'l';
        case DT_REG:
            return '-';
        case DT_SOCK:
            return 's';
        case DT_UNKNOWN:
            return 'u';
        default:
            return 'U';
    }
}

void ls(const char *directory)
{
    struct dirent *item;
    DIR *pDir;
    pDir = opendir(strlen(directory) > 0 ? directory : ".");
    if (pDir == NULL)
    {
        printf("No directory '%s'\n", directory);
        return;
    }
    while ((item = readdir(pDir)) != NULL)
        printf("%c %s\n", dTypeDisplay(item->d_type), item->d_name);
    closedir(pDir);
}

void cd(const char *directory)
{
    chdir(directory);
}

void info()
{
    struct sysinfo info;
    syscall(SYS_sysinfo, &info);
    printf("Uptime:\t\t%ld\tseconds\n", info.uptime);
    printf("Total RAM:\t%ld\tbytes\n", info.totalram);
    printf("Free RAM:\t%ld\tbytes\n", info.freeram);
    printf("Proc count:\t%d\n", info.procs);
}

void splash()
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

void usage()
{
    printf("\033[1;37mBigsby Linux v0.0.2\033[0m\n\n");
    printf("Available commads:\n");
    printf("\tinfo\t\tdisplay system information\n");
    printf("\tls\t\tlist filesystem content\n");
    printf("\tclear\t\tclear screen\n");
    printf("\thelp\t\tprint this help\n");
    printf("\tquit\t\texit system\n");
}

void handleCommand(char *input)
{
    if (input[strlen(input) - 1] == '\n')
        input[strlen(input) - 1] = '\0';

    char *command = strtok(input, " ");
    if (command != NULL)
    {
        int commandLength = strlen(command);
        if (strcmp(command, "quit") == 0)
            quit();
        else if (strcmp(command, "cd") == 0)
            cd(input + commandLength + 1);
        else if (strcmp(command, "info") == 0)
            info();
        else if (strcmp(command, "ls") == 0)
            ls(input + commandLength + 1);
        else if (strcmp(command, "help") == 0)
            usage();
        else if (strcmp(command, "clear") == 0)
            clearScreen();
        else if (strlen(command) > 1)
            printf("Unknown command: %s", command);

    }
}

int main()
{
    clearScreen();
    splash();
    printf("Welcome to Bigsby Linux\n\n");
    usage();
    int go = 1;
    char input[50], currentDir[100];
    while (1)
    {
        printf("%s > ", getcwd(currentDir, 100));
        fgets(input, 50, stdin);
        handleCommand(input);
    }
}
