#include "common.h"

static void apply_composer_mirror(const char *mirror_url) {
    char cmd[1024];
    if (strcmp(mirror_url, "UNSET") == 0) {
        snprintf(cmd, sizeof(cmd), "composer config -g --unset repo.packagist");
        if (run_command(cmd) == 0) {
            printf(COLOR_GREEN "Composer mirror unset successfully." COLOR_RESET "\n");
        }
    } else {
        snprintf(cmd, sizeof(cmd), "composer config -g repo.packagist composer %s", mirror_url);
        if (run_command(cmd) == 0) {
            printf(COLOR_GREEN);
            printf(get_msg(MSG_SUCCESS), mirror_url);
            printf(COLOR_RESET "\n");
        } else {
            printf(COLOR_RED "%s" COLOR_RESET "\n", get_msg(MSG_FAILURE));
        }
    }
}

void menu_composer() {
    MirrorSite sites[] = {
        {(char*)get_msg(MSG_MIRROR_ALIYUN), "https://mirrors.aliyun.com/composer/"},
        {"Tencent Cloud", "https://mirrors.cloud.tencent.com/composer/"},
        {(char*)get_msg(MSG_MIRROR_OFFICIAL), "UNSET"}
    };
    select_mirror_and_apply("Composer Registry Configuration", sites, 3, apply_composer_mirror);
}
