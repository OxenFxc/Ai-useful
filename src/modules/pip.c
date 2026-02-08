#include "common.h"

void change_pip_mirror(const char *mirror_url) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "pip config set global.index-url %s", mirror_url);

    if (run_command(cmd) == 0) {
        printf(COLOR_GREEN);
        printf(get_msg(MSG_SUCCESS), mirror_url);
        printf(COLOR_RESET "\n");
    } else {
        printf(COLOR_RED "%s" COLOR_RESET "\n", get_msg(MSG_FAILURE));
    }
}

void menu_pip() {
    int choice;
    print_header(get_msg(MSG_PIP_MENU));
    printf("1. %s\n", get_msg(MSG_MIRROR_TSINGHUA));
    printf("2. %s\n", get_msg(MSG_MIRROR_ALIYUN));
    printf("3. %s\n", get_msg(MSG_MIRROR_USTC));
    printf("0. %s\n", get_msg(MSG_BACK));
    printf("%s", get_msg(MSG_ENTER_CHOICE));
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
