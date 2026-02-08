#include "common.h"

void system_cleanup() {
    print_header("System Cleanup");
    printf("Performing APT cleanup...\n");
    run_command("sudo apt-get autoremove -y");
    run_command("sudo apt-get autoclean");

    printf("Cleaning journal logs older than 3 days...\n");
    run_command("sudo journalctl --vacuum-time=3d");

    printf(COLOR_GREEN "Cleanup complete!" COLOR_RESET "\n");
}

void menu_toolbox() {
    int choice;
    void show_sysinfo(); // Forward declaration

    while (1) {
        print_header("Toolbox");
        printf("1. Show System Info\n");
        printf("2. System Cleanup\n");
        printf("0. Back\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            break;
        }
        clear_input_buffer();

        if (choice == 1) {
            show_sysinfo();
        } else if (choice == 2) {
            system_cleanup();
        } else if (choice == 0) {
            break;
        }
    }
}
