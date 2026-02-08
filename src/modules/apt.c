#include "common.h"

static void apply_apt_mirror(const char *mirror_url) {
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
    const char *match_path = "/ubuntu/";
    if (access("/etc/debian_version", F_OK) == 0 && access("/etc/os-release", F_OK) == 0) {
        FILE *os_fp = fopen("/etc/os-release", "r");
        if (os_fp) {
            char line[256];
            while (fgets(line, sizeof(line), os_fp)) {
                if (strstr(line, "ID=debian")) { match_path = "/debian/"; break; }
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
    const char *base_url = (access("/etc/debian_version", F_OK) == 0) ? "debian/" : "ubuntu/";
    char urls[3][256];
    snprintf(urls[0], 256, "https://mirrors.tuna.tsinghua.edu.cn/%s", base_url);
    snprintf(urls[1], 256, "https://mirrors.aliyun.com/%s", base_url);
    snprintf(urls[2], 256, "https://mirrors.ustc.edu.cn/%s", base_url);

    MirrorSite sites[] = {
        {(char*)get_msg(MSG_MIRROR_TSINGHUA), urls[0]},
        {(char*)get_msg(MSG_MIRROR_ALIYUN), urls[1]},
        {(char*)get_msg(MSG_MIRROR_USTC), urls[2]}
    };

    select_mirror_and_apply(get_msg(MSG_APT_MENU), sites, 3, apply_apt_mirror);
}
