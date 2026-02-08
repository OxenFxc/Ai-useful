#include "common.h"

static void apply_github_proxy(const char *proxy_url) {
    char cmd[1024];
    if (strcmp(proxy_url, "UNSET") == 0) {
        snprintf(cmd, sizeof(cmd), "git config --global --unset http.proxy && git config --global --unset https.proxy");
        run_command(cmd);
        printf(COLOR_GREEN "GitHub proxy unset successfully." COLOR_RESET "\n");
    } else if (strcmp(proxy_url, "INFO") == 0) {
        printf("Note: To use GHProxy, prefix the URL: git clone https://mirror.ghproxy.com/https://github.com/user/repo\n");
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
    MirrorSite sites[] = {
        {"GHProxy (Info)", "INFO"},
        {"KubeProxy (gh.api.999888.xyz)", "http://gh.api.999888.xyz/"},
        {"Unset Proxy", "UNSET"}
    };
    select_mirror_and_apply(get_msg(MSG_GITHUB_MENU), sites, 3, apply_github_proxy);
}
