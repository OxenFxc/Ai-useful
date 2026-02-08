#include "common.h"

void show_network_info() {
    print_header("Network Information");
    printf("Public IP: ");
    fflush(stdout);
    run_command("curl -s ifconfig.me || echo 'Failed to fetch'");

    printf("Local Interfaces:\n");
    run_command("ip -4 addr show | grep inet");

    printf("\nDNS Connectivity:\n");
    printf("Pinging AliDNS (223.5.5.5)... ");
    fflush(stdout);
    if (system("ping -c 1 -W 2 223.5.5.5 > /dev/null 2>&1") == 0) {
        printf(COLOR_GREEN "OK" COLOR_RESET "\n");
    } else {
        printf(COLOR_RED "FAIL" COLOR_RESET "\n");
    }

    printf("Pinging Google DNS (8.8.8.8)... ");
    fflush(stdout);
    if (system("ping -c 1 -W 2 8.8.8.8 > /dev/null 2>&1") == 0) {
        printf(COLOR_GREEN "OK" COLOR_RESET "\n");
    } else {
        printf(COLOR_RED "FAIL" COLOR_RESET "\n");
    }
}

void menu_network() {
    int choice;
    while (1) {
        print_header("Network Toolbox");
        printf("1. Show Network Info & Connectivity\n");
        printf("0. %s\n", get_msg(MSG_BACK));
        printf("%s", get_msg(MSG_ENTER_CHOICE));
        if (scanf("%d", &choice) != 1) { clear_input_buffer(); break; }
        clear_input_buffer();
        if (choice == 1) show_network_info();
        else if (choice == 0) break;
    }
}
