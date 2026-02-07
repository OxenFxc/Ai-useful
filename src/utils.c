#include "common.h"
#include <sys/stat.h>
#include <time.h>

int run_command(const char *cmd) {
    printf(COLOR_BLUE "Executing: %s" COLOR_RESET "\n", cmd);
    return system(cmd);
}

int backup_file(const char *filepath) {
    if (access(filepath, F_OK) == -1) {
        return 0; // File doesn't exist, no need to backup
    }

    char backup_path[512];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(backup_path, sizeof(backup_path), "%s.bak.%d%02d%02d_%02d%02d%02d",
             filepath, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
             tm.tm_hour, tm.tm_min, tm.tm_sec);

    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "cp %s %s", filepath, backup_path);
    printf(COLOR_YELLOW "Backing up %s to %s" COLOR_RESET "\n", filepath, backup_path);
    return system(cmd);
}

int write_file_content(const char *filepath, const char *content) {
    FILE *fp = fopen(filepath, "w");
    if (fp == NULL) {
        perror("fopen");
        return -1;
    }
    fprintf(fp, "%s", content);
    fclose(fp);
    return 0;
}

void print_header(const char *title) {
    printf("\n" COLOR_GREEN "=== %s ===" COLOR_RESET "\n", title);
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
