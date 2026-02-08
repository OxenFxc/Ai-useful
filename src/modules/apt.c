#include "common.h"

void change_apt_mirror(const char *mirror_url) {
    const char *source_file = "/etc/apt/sources.list.d/ubuntu.sources";
    if (access(source_file, F_OK) == -1) {
        source_file = "/etc/apt/sources.list";
    }

    if (access(source_file, W_OK) == -1) {
        printf(COLOR_RED "Error: No write permission for %s. Try running with sudo." COLOR_RESET "\n", source_file);
        return;
    }

    backup_file(source_file);

    char cmd[1024];
    // Simple sed command to replace the URI.
    // For DEB822 format (ubuntu.sources), it looks for URIs: ...
    // For old format (sources.list), it looks for http://... or https://...

    if (strstr(source_file, "ubuntu.sources")) {
        snprintf(cmd, sizeof(cmd), "sed -i 's|URIs: https\\?://.*archive.ubuntu.com/ubuntu/|URIs: %s|g; s|URIs: https\\?://security.ubuntu.com/ubuntu/|URIs: %s|g' %s",
                 mirror_url, mirror_url, source_file);
    } else {
        snprintf(cmd, sizeof(cmd), "sed -i 's|https\\?://.*archive.ubuntu.com/ubuntu/|%s|g; s|https\\?://security.ubuntu.com/ubuntu/|%s|g' %s",
                 mirror_url, mirror_url, source_file);
    }

    if (run_command(cmd) == 0) {
        printf(COLOR_GREEN "Successfully changed APT mirror to %s" COLOR_RESET "\n", mirror_url);
        run_command("apt-get update");
    } else {
        printf(COLOR_RED "Failed to change APT mirror." COLOR_RESET "\n");
    }
}

void menu_apt() {
    int choice;
    print_header("APT Mirror Configuration");
    printf("1. Tsinghua University\n");
    printf("2. Alibaba Cloud\n");
    printf("3. USTC\n");
    printf("0. Back\n");
    printf("Enter choice: ");
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
