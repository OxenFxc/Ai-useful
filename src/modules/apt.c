#include "common.h"

void change_apt_mirror(const char *mirror_url) {
    const char *source_file = "/etc/apt/sources.list.d/ubuntu.sources";
    if (access(source_file, F_OK) == -1) {
        source_file = "/etc/apt/sources.list";
    }

    if (access(source_file, W_OK) == -1) {
        printf(COLOR_RED "%s (%s)" COLOR_RESET "\n", get_msg(MSG_PERMISSION_DENIED), source_file);
        return;
    }

    backup_file(source_file);

    char cmd[1024];
    // Generic regex to match any existing mirror URL for ubuntu
    if (strstr(source_file, "ubuntu.sources")) {
        snprintf(cmd, sizeof(cmd), "sed -i 's|URIs: https\\?://[^/ ]*/ubuntu/|URIs: %s|g' %s",
                 mirror_url, source_file);
    } else {
        snprintf(cmd, sizeof(cmd), "sed -i 's|https\\?://[^/ ]*/ubuntu/|%s|g' %s",
                 mirror_url, source_file);
    }

    if (run_command(cmd) == 0) {
        printf(COLOR_GREEN);
        printf(get_msg(MSG_SUCCESS), mirror_url);
        printf(COLOR_RESET "\n");
        run_command("apt-get update");
    } else {
        printf(COLOR_RED "%s" COLOR_RESET "\n", get_msg(MSG_FAILURE));
    }
}

void menu_apt() {
    int choice;
    print_header(get_msg(MSG_APT_MENU));
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
            change_apt_mirror("https://mirrors.tuna.tsinghua.edu.cn/ubuntu/");
            break;
        case 2:
            change_apt_mirror("https://mirrors.aliyun.com/ubuntu/");
            break;
        case 3:
            change_apt_mirror("https://mirrors.ustc.edu.cn/ubuntu/");
            break;
        default:
            break;
    }
}
