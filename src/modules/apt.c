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
    // Determine the base path to match. Default to ubuntu if not found.
    const char *match_path = "/ubuntu/";
    if (access("/etc/debian_version", F_OK) == 0 && access("/etc/os-release", F_OK) == 0) {
        // Simple heuristic for Debian
        FILE *os_fp = fopen("/etc/os-release", "r");
        if (os_fp) {
            char line[256];
            while (fgets(line, sizeof(line), os_fp)) {
                if (strstr(line, "ID=debian")) {
                    match_path = "/debian/";
                    break;
                }
            }
            fclose(os_fp);
        }
    }

    if (strstr(source_file, ".sources")) {
        snprintf(cmd, sizeof(cmd), "sed -i 's|URIs: https\\?://[^/ ]*%s|URIs: %s|g' %s",
                 match_path, mirror_url, source_file);
    } else {
        snprintf(cmd, sizeof(cmd), "sed -i 's|https\\?://[^/ ]*%s|%s|g' %s",
                 match_path, mirror_url, source_file);
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

    const char *base_url;
    // Again, heuristic for Debian
    if (access("/etc/debian_version", F_OK) == 0) {
        base_url = "debian/";
    } else {
        base_url = "ubuntu/";
    }

    char mirror_full[256];
    switch (choice) {
        case 1:
            snprintf(mirror_full, sizeof(mirror_full), "https://mirrors.tuna.tsinghua.edu.cn/%s", base_url);
            change_apt_mirror(mirror_full);
            break;
        case 2:
            snprintf(mirror_full, sizeof(mirror_full), "https://mirrors.aliyun.com/%s", base_url);
            change_apt_mirror(mirror_full);
            break;
        case 3:
            snprintf(mirror_full, sizeof(mirror_full), "https://mirrors.ustc.edu.cn/%s", base_url);
            change_apt_mirror(mirror_full);
            break;
        default:
            break;
    }
}
