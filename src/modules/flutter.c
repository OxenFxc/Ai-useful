#include "common.h"

static void apply_flutter_mirror(const char *unused) {
    (void)unused;
    char path[512];
    snprintf(path, sizeof(path), "%s/.bashrc", getenv("HOME"));

    backup_file(path);

    // Check if already configured to avoid duplicates
    char check_cmd[1024];
    snprintf(check_cmd, sizeof(check_cmd), "grep -q \"FLUTTER_STORAGE_BASE_URL\" %s", path);
    if (system(check_cmd) == 0) {
        printf(COLOR_YELLOW "Flutter mirrors already configured in .bashrc" COLOR_RESET "\n");
        return;
    }

    FILE *fp = fopen(path, "a");
    if (fp) {
        fprintf(fp, "\n# Flutter Chinese Mirrors\n");
        fprintf(fp, "export PUB_HOSTED_URL=https://mirrors.tuna.tsinghua.edu.cn/dart-pub\n");
        fprintf(fp, "export FLUTTER_STORAGE_BASE_URL=https://mirrors.tuna.tsinghua.edu.cn/flutter\n");
        fclose(fp);
        printf(COLOR_GREEN "Successfully added Flutter mirrors to .bashrc. Please run 'source ~/.bashrc' to apply." COLOR_RESET "\n");
    } else {
        printf(COLOR_RED "Failed to open .bashrc" COLOR_RESET "\n");
    }
}

void menu_flutter() {
    print_header("Flutter Mirror Configuration");
    printf("1. Configure Tsinghua Mirrors\n");
    printf("0. %s\n", get_msg(MSG_BACK));
    printf("%s", get_msg(MSG_ENTER_CHOICE));

    int choice;
    if (scanf("%d", &choice) != 1) { clear_input_buffer(); return; }
    clear_input_buffer();

    if (choice == 1) apply_flutter_mirror(NULL);
}
