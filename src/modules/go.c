#include "common.h"

void change_go_proxy(const char *proxy_url) {
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
    int choice;
    print_header("Go Proxy Configuration");
    printf("1. Goproxy.cn (Qiniu)\n");
    printf("2. Goproxy.io\n");
    printf("3. %s (Aliyun)\n", get_msg(MSG_MIRROR_ALIYUN));
    printf("0. %s\n", get_msg(MSG_BACK));
    printf("%s", get_msg(MSG_ENTER_CHOICE));
    if (scanf("%d", &choice) != 1) {
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    switch (choice) {
        case 1:
            change_go_proxy("https://goproxy.cn");
            break;
        case 2:
            change_go_proxy("https://goproxy.io");
            break;
        case 3:
            change_go_proxy("https://mirrors.aliyun.com/goproxy/");
            break;
        default:
            break;
    }
}
