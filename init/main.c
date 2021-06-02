#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <linux/reboot.h>
#include <sys/syscall.h>
#include <sys/sysinfo.h>
#include <linux/fcntl.h>
#include <dirent.h>

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

void printFileSystem()
{
    struct dirent *item;
    DIR *pDir;
    pDir = opendir(".");
    while ((item = readdir(pDir)) != NULL)
        printf("%c %s\n", dTypeDisplay(item->d_type), item->d_name);

    closedir(pDir);
}

void printSysInfo()
{
    struct sysinfo info;
    syscall(SYS_sysinfo, &info);
    printf("Uptime:\t\t%ld\tseconds\n", info.uptime);
    printf("Total RAM:\t%ld\tbytes\n", info.totalram);
    printf("Free RAM:\t%ld\tbytes\n", info.freeram);
    printf("Proc count:\t%d\n", info.procs);
}

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
    printf("\033[1;37mBigsby Linux v0.0.2\033[0m\n\n");
    printf("Available commads:\n");
    printf("\tinfo\t\tdisplay system information\n");
    printf("\tls\t\tlist filesystem content\n");
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
    while (1)
    {
        printf("> ");
        fgets(command, 50, stdin);
        if (strncmp(command, "quit", 4) == 0)
            quit();
        else if (strncmp(command, "info", 4) == 0)
            printSysInfo();
        else if (strncmp(command, "ls", 2) == 0)
            printFileSystem();
        else if (strncmp(command, "help", 4) == 0)
            printUsage();
        else if (strncmp(command, "clear", 4) == 0)
            clearScreen();
        else if (strlen(command) > 1)
            printf("Unknown command: %s", command);
    }
}
