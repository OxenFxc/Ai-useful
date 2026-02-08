#include "common.h"

void change_npm_mirror(const char *mirror_url) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "npm config set registry %s", mirror_url);

    if (run_command(cmd) == 0) {
        printf(COLOR_GREEN);
        printf(get_msg(MSG_SUCCESS), mirror_url);
        printf(COLOR_RESET "\n");
    } else {
        printf(COLOR_RED "%s" COLOR_RESET "\n", get_msg(MSG_FAILURE));
    }
}

void menu_npm() {
    int choice;
    print_header(get_msg(MSG_NPM_MENU));
    printf("1. %s\n", get_msg(MSG_MIRROR_TAOBAO));
    printf("2. %s\n", get_msg(MSG_MIRROR_OFFICIAL));
    printf("0. %s\n", get_msg(MSG_BACK));
    printf("%s", get_msg(MSG_ENTER_CHOICE));
    if (scanf("%d", &choice) != 1) {
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    switch (choice) {
        case 1:
            change_npm_mirror("https://registry.npmmirror.com");
            break;
        case 2:
            change_npm_mirror("https://registry.npmjs.org/");
            break;
        default:
            break;
    }
}
