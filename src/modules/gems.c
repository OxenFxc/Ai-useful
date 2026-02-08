#include "common.h"

static void apply_gems_mirror(const char *mirror_url) {
    char cmd[1024];
    // Remove default and add new
    snprintf(cmd, sizeof(cmd), "gem sources --add %s --remove https://rubygems.org/", mirror_url);
    if (run_command(cmd) == 0) {
        printf(COLOR_GREEN);
        printf(get_msg(MSG_SUCCESS), mirror_url);
        printf(COLOR_RESET "\n");
    } else {
        printf(COLOR_RED "%s" COLOR_RESET "\n", get_msg(MSG_FAILURE));
    }
}

void menu_gems() {
    MirrorSite sites[] = {
        {(char*)get_msg(MSG_MIRROR_TSINGHUA), "https://mirrors.tuna.tsinghua.edu.cn/rubygems/"},
        {(char*)get_msg(MSG_MIRROR_ALIYUN), "https://mirrors.aliyun.com/rubygems/"}
    };
    select_mirror_and_apply("RubyGems Source Configuration", sites, 2, apply_gems_mirror);
}
