#include "common.h"

void handle_category(MenuCategory *cat) {
    int choice;
    while (1) {
        print_header(get_msg(cat->title_msg_id));
        for (int i = 0; i < cat->num_options; i++) {
            printf("%d. %s\n", i + 1, get_msg(cat->options[i].title_msg_id));
        }
        printf("0. %s\n", get_msg(MSG_BACK));
        printf("%s", get_msg(MSG_ENTER_CHOICE));

        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (choice == 0) break;
        if (choice > 0 && choice <= cat->num_options) {
            cat->options[choice - 1].func();
        } else {
            printf(COLOR_RED "%s" COLOR_RESET "\n", get_msg(MSG_INVALID_CHOICE));
        }
    }
}

void print_main_menu() {
    print_header(get_msg(MSG_MAIN_TITLE));
    for (int i = 0; i < num_categories; i++) {
        printf("%d. %s\n", i + 1, get_msg(categories[i].title_msg_id));
    }
    printf("%d. %s\n", num_categories + 1, get_msg(MSG_LANG_SELECT));
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

        if (choice == 0) {
            printf("Exiting. Have a nice day!\n");
            return 0;
        }

        if (choice > 0 && choice <= num_categories) {
            handle_category(&categories[choice - 1]);
        } else if (choice == num_categories + 1) {
            current_lang = (current_lang == LANG_EN) ? LANG_CN : LANG_EN;
            save_config();
        } else {
            printf(COLOR_RED "%s" COLOR_RESET "\n", get_msg(MSG_INVALID_CHOICE));
        }
    }
    return 0;
}
