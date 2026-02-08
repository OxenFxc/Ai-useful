#include "common.h"

static void apply_pip_mirror(const char *mirror_url) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "pip config set global.index-url %s", mirror_url);
    if (run_command(cmd) == 0) {
        printf(COLOR_GREEN);
        printf(get_msg(MSG_SUCCESS), mirror_url);
        printf(COLOR_RESET "\n");
    } else {
        printf(COLOR_RED "%s" COLOR_RESET "\n", get_msg(MSG_FAILURE));
    }
}

void menu_pip() {
    MirrorSite sites[] = {
        {get_msg(MSG_MIRROR_TSINGHUA), "https://pypi.tuna.tsinghua.edu.cn/simple"},
        {get_msg(MSG_MIRROR_ALIYUN), "https://mirrors.aliyun.com/pypi/simple/"},
        {get_msg(MSG_MIRROR_USTC), "https://pypi.mirrors.ustc.edu.cn/simple/"}
    };
    select_mirror_and_apply(get_msg(MSG_PIP_MENU), sites, 3, apply_pip_mirror);
}
