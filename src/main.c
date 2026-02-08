#include "common.h"

void print_main_menu() {
    print_header(get_msg(MSG_MAIN_TITLE));
    printf("1. %s\n", get_msg(MSG_APT_MENU));
    printf("2. %s\n", get_msg(MSG_PIP_MENU));
    printf("3. %s\n", get_msg(MSG_NPM_MENU));
    printf("4. %s\n", get_msg(MSG_DOCKER_MENU));
    printf("5. %s\n", get_msg(MSG_TOOLBOX_MENU));
    printf("6. %s\n", get_msg(MSG_LANG_SELECT));
    printf("0. %s\n", get_msg(MSG_EXIT));
    printf("%s", get_msg(MSG_ENTER_CHOICE));
}

int main() {
    int choice;
    while (1) {
        print_main_menu();
        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1:
                menu_apt();
                break;
            case 2:
                menu_pip();
                break;
            case 3:
                menu_npm();
                break;
            case 4:
                menu_docker();
                break;
            case 5:
                menu_toolbox();
                break;
            case 6:
                current_lang = (current_lang == LANG_EN) ? LANG_CN : LANG_EN;
                break;
            case 0:
                printf("Exiting. Have a nice day!\n");
                return 0;
            default:
                printf(COLOR_RED "%s" COLOR_RESET "\n", get_msg(MSG_INVALID_CHOICE));
                break;
        }
    }
    return 0;
}
