#include "common.h"

void print_main_menu() {
    print_header("Super Source Toolbox");
    printf("1. APT Mirror (Debian/Ubuntu)\n");
    printf("2. Pip Mirror (Python)\n");
    printf("3. NPM Registry (Node.js)\n");
    printf("4. Toolbox (System Info, Cleanup, etc.)\n");
    printf("0. Exit\n");
    printf("Enter choice: ");
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
                menu_toolbox();
                break;
            case 0:
                printf("Exiting. Have a nice day!\n");
                return 0;
            default:
                printf(COLOR_RED "Invalid choice." COLOR_RESET "\n");
                break;
        }
    }
    return 0;
}
