#include "common.h"

static void apply_go_proxy(const char *proxy_url) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "go env -w GOPROXY=%s,direct", proxy_url);
    if (run_command(cmd) == 0) {
        printf(COLOR_GREEN);
        printf(get_msg(MSG_SUCCESS), proxy_url);
        printf(COLOR_RESET "\n");
    } else {
        printf(COLOR_RED "%s" COLOR_RESET "\n", get_msg(MSG_FAILURE));
    }
}

void menu_go() {
    MirrorSite sites[] = {
        {"Goproxy.cn (Qiniu)", "https://goproxy.cn"},
        {"Goproxy.io", "https://goproxy.io"},
        {(char*)get_msg(MSG_MIRROR_ALIYUN), "https://mirrors.aliyun.com/goproxy/"}
    };
    select_mirror_and_apply(get_msg(MSG_GO_MENU), sites, 3, apply_go_proxy);
}
