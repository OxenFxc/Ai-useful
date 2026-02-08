#include "common.h"

void menu_os() {
    int choice;
    while (1) {
        print_header(get_msg(MSG_CAT_OS));
        printf("1. %s\n", get_msg(MSG_APT_MENU));
        printf("0. %s\n", get_msg(MSG_BACK));
        printf("%s", get_msg(MSG_ENTER_CHOICE));
        if (scanf("%d", &choice) != 1) { clear_input_buffer(); break; }
        clear_input_buffer();
        if (choice == 1) menu_apt();
        else if (choice == 0) break;
    }
}

void menu_dev() {
    int choice;
    while (1) {
        print_header(get_msg(MSG_CAT_DEV));
        printf("1. %s\n", get_msg(MSG_PIP_MENU));
        printf("2. %s\n", get_msg(MSG_NPM_MENU));
        printf("3. Go Proxy\n");
        printf("4. Rust (Cargo) Mirror\n");
        printf("0. %s\n", get_msg(MSG_BACK));
        printf("%s", get_msg(MSG_ENTER_CHOICE));
        if (scanf("%d", &choice) != 1) { clear_input_buffer(); break; }
        clear_input_buffer();
        switch (choice) {
            case 1: menu_pip(); break;
            case 2: menu_npm(); break;
            case 3: menu_go(); break;
            case 4: menu_rust(); break;
            case 0: return;
        }
    }
}

void menu_services() {
    int choice;
    while (1) {
        print_header(get_msg(MSG_CAT_SERVICES));
        printf("1. %s\n", get_msg(MSG_DOCKER_MENU));
        printf("2. GitHub Acceleration\n");
        printf("0. %s\n", get_msg(MSG_BACK));
        printf("%s", get_msg(MSG_ENTER_CHOICE));
        if (scanf("%d", &choice) != 1) { clear_input_buffer(); break; }
        clear_input_buffer();
        switch (choice) {
            case 1: menu_docker(); break;
            case 2: menu_github(); break;
            case 0: return;
        }
    }
}

void print_main_menu() {
    print_header(get_msg(MSG_MAIN_TITLE));
    printf("1. %s\n", get_msg(MSG_CAT_OS));
    printf("2. %s\n", get_msg(MSG_CAT_DEV));
    printf("3. %s\n", get_msg(MSG_CAT_SERVICES));
    printf("4. %s\n", get_msg(MSG_CAT_TOOLBOX));
    printf("5. %s\n", get_msg(MSG_PLUGINS));
    printf("6. %s\n", get_msg(MSG_LANG_SELECT));
    printf("0. %s\n", get_msg(MSG_EXIT));
    printf("%s", get_msg(MSG_ENTER_CHOICE));
}

int main() {
    load_config();
    int choice;
    while (1) {
        print_main_menu();
        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: menu_os(); break;
            case 2: menu_dev(); break;
            case 3: menu_services(); break;
            case 4: menu_toolbox(); break;
            case 5: menu_plugins(); break;
            case 6:
                current_lang = (current_lang == LANG_EN) ? LANG_CN : LANG_EN;
                save_config();
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
