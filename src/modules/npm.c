#include "common.h"

void change_npm_mirror(const char *mirror_url) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "npm config set registry %s", mirror_url);

    if (run_command(cmd) == 0) {
        printf(COLOR_GREEN "Successfully changed NPM registry to %s" COLOR_RESET "\n", mirror_url);
    } else {
        printf(COLOR_RED "Failed to change NPM registry." COLOR_RESET "\n");
    }
}

void menu_npm() {
    int choice;
    print_header("NPM Registry Configuration");
    printf("1. Taobao (Registry.npmmirror.com)\n");
    printf("2. Official Registry\n");
    printf("0. Back\n");
    printf("Enter choice: ");
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
