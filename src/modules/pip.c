#include "common.h"

void change_pip_mirror(const char *mirror_url) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "pip config set global.index-url %s", mirror_url);

    if (run_command(cmd) == 0) {
        printf(COLOR_GREEN "Successfully changed Pip mirror to %s" COLOR_RESET "\n", mirror_url);
    } else {
        printf(COLOR_RED "Failed to change Pip mirror." COLOR_RESET "\n");
    }
}

void menu_pip() {
    int choice;
    print_header("Pip Mirror Configuration");
    printf("1. Tsinghua University\n");
    printf("2. Alibaba Cloud\n");
    printf("3. USTC\n");
    printf("0. Back\n");
    printf("Enter choice: ");
    if (scanf("%d", &choice) != 1) {
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    switch (choice) {
        case 1:
            change_pip_mirror("https://pypi.tuna.tsinghua.edu.cn/simple");
            break;
        case 2:
            change_pip_mirror("https://mirrors.aliyun.com/pypi/simple/");
            break;
        case 3:
            change_pip_mirror("https://pypi.mirrors.ustc.edu.cn/simple/");
            break;
        default:
            break;
    }
}
