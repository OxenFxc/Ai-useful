#include "common.h"

static void apply_npm_mirror(const char *mirror_url) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "npm config set registry %s", mirror_url);
    if (run_command(cmd) == 0) {
        printf(COLOR_GREEN);
        printf(get_msg(MSG_SUCCESS), mirror_url);
        printf(COLOR_RESET "\n");
    } else {
        printf(COLOR_RED "%s" COLOR_RESET "\n", get_msg(MSG_FAILURE));
    }
}

void menu_npm() {
    MirrorSite sites[] = {
        {(char*)get_msg(MSG_MIRROR_TAOBAO), "https://registry.npmmirror.com"},
        {(char*)get_msg(MSG_MIRROR_OFFICIAL), "https://registry.npmjs.org/"}
    };
    select_mirror_and_apply(get_msg(MSG_NPM_MENU), sites, 2, apply_npm_mirror);
}
