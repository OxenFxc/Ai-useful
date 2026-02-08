#include "common.h"

static void apply_dns(const char *dns_ips) {
    const char *path = "/etc/resolv.conf";
    if (access(path, W_OK) == -1) {
        printf(COLOR_RED "Error: No write permission for %s. Try running with sudo." COLOR_RESET "\n", path);
        return;
    }

    backup_file(path);

    FILE *fp = fopen(path, "w");
    if (fp) {
        fprintf(fp, "# Configured by Super Source Toolbox\n");
        char *ips = strdup(dns_ips);
        char *token = strtok(ips, ",");
        while (token != NULL) {
            fprintf(fp, "nameserver %s\n", token);
            token = strtok(NULL, ",");
        }
        free(ips);
        fclose(fp);
        printf(COLOR_GREEN "DNS configured successfully." COLOR_RESET "\n");
    } else {
        printf(COLOR_RED "Failed to open %s" COLOR_RESET "\n", path);
    }
}

void menu_dns() {
    print_header("DNS Configuration");
    printf("1. AliDNS (223.5.5.5, 223.6.6.6)\n");
    printf("2. DNSPod (119.29.29.29)\n");
    printf("3. Google DNS (8.8.8.8, 8.8.4.4)\n");
    printf("0. %s\n", get_msg(MSG_BACK));
    printf("%s", get_msg(MSG_ENTER_CHOICE));

    int choice;
    if (scanf("%d", &choice) != 1) { clear_input_buffer(); return; }
    clear_input_buffer();

    switch (choice) {
        case 1: apply_dns("223.5.5.5,223.6.6.6"); break;
        case 2: apply_dns("119.29.29.29"); break;
        case 3: apply_dns("8.8.8.8,8.8.4.4"); break;
        default: break;
    }
}
