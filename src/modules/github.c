#include "common.h"

void set_github_proxy(const char *proxy_url) {
    char cmd[1024];
    if (proxy_url == NULL) {
        snprintf(cmd, sizeof(cmd), "git config --global --unset http.proxy && git config --global --unset https.proxy");
        run_command(cmd);
        printf(COLOR_GREEN "GitHub proxy unset successfully." COLOR_RESET "\n");
    } else {
        snprintf(cmd, sizeof(cmd), "git config --global http.proxy %s && git config --global https.proxy %s", proxy_url, proxy_url);
        if (run_command(cmd) == 0) {
            printf(COLOR_GREEN "GitHub proxy set to %s" COLOR_RESET "\n", proxy_url);
        } else {
            printf(COLOR_RED "Failed to set GitHub proxy." COLOR_RESET "\n");
        }
    }
}

void menu_github() {
    int choice;
    print_header("GitHub Acceleration");
    printf("1. Use GHProxy (https://ghproxy.com/)\n");
    printf("2. Use KubeProxy (https://gh.api.999888.xyz/)\n");
    printf("3. Unset Git Proxy\n");
    printf("0. %s\n", get_msg(MSG_BACK));
    printf("%s", get_msg(MSG_ENTER_CHOICE));
    if (scanf("%d", &choice) != 1) {
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    switch (choice) {
        case 1:
            printf("Note: To use GHProxy, prefix the URL: git clone https://mirror.ghproxy.com/https://github.com/user/repo\n");
            break;
        case 2:
            set_github_proxy("http://gh.api.999888.xyz/");
            break;
        case 3:
            set_github_proxy(NULL);
            break;
        default:
            break;
    }
}
