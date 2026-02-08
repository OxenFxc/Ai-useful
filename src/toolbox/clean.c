#include "common.h"

void system_cleanup() {
    print_header(get_msg(MSG_CLEANUP_TITLE));
    printf("Performing APT cleanup...\n");
    run_command("sudo apt-get autoremove -y");
    run_command("sudo apt-get autoclean");

    printf("Cleaning journal logs older than 3 days...\n");
    run_command("sudo journalctl --vacuum-time=3d");

    printf(COLOR_GREEN "Cleanup complete!" COLOR_RESET "\n");
}

void run_speed_test() {
    print_header(get_msg(MSG_SPEED_TEST));
    const char *mirrors[] = {
        "https://mirrors.tuna.tsinghua.edu.cn",
        "https://mirrors.aliyun.com",
        "https://mirrors.ustc.edu.cn",
        "https://registry.npmmirror.com"
    };
    int n = sizeof(mirrors) / sizeof(mirrors[0]);

    for (int i = 0; i < n; i++) {
        printf("Testing %s... ", mirrors[i]);
        fflush(stdout);
        double speed = test_mirror_speed(mirrors[i]);
        if (speed >= 0) {
            printf(COLOR_GREEN "%.3fs" COLOR_RESET "\n", speed);
        } else {
            printf(COLOR_RED "Timeout/Error" COLOR_RESET "\n");
        }
    }
}

void menu_toolbox() {
    int choice;

    while (1) {
        print_header(get_msg(MSG_TOOLBOX_MENU));
        printf("1. %s\n", get_msg(MSG_SYSINFO_TITLE));
        printf("2. %s\n", get_msg(MSG_CLEANUP_TITLE));
        printf("3. %s\n", get_msg(MSG_SPEED_TEST));
        printf("0. %s\n", get_msg(MSG_BACK));
        printf("%s", get_msg(MSG_ENTER_CHOICE));
        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            break;
        }
        clear_input_buffer();

        if (choice == 1) {
            show_sysinfo();
        } else if (choice == 2) {
            system_cleanup();
        } else if (choice == 3) {
            run_speed_test();
        } else if (choice == 0) {
            break;
        }
    }
}
