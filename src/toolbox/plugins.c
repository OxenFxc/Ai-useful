#include "common.h"
#include <dirent.h>

void menu_plugins() {
    DIR *d;
    struct dirent *dir;
    char *plugins[64];
    int count = 0;

    print_header("Plugin Manager");
    d = opendir("./plugins");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG || dir->d_type == DT_LNK) {
                plugins[count] = strdup(dir->d_name);
                printf("%d. %s\n", count + 1, plugins[count]);
                count++;
            }
        }
        closedir(d);
    }

    if (count == 0) {
        printf("No plugins found in ./plugins directory.\n");
    }

    printf("0. %s\n", get_msg(MSG_BACK));
    printf("%s", get_msg(MSG_ENTER_CHOICE));

    int choice;
    if (scanf("%d", &choice) != 1) {
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (choice > 0 && choice <= count) {
        char cmd[1024];
        snprintf(cmd, sizeof(cmd), "./plugins/%s", plugins[choice - 1]);
        run_command(cmd);
    }

    for (int i = 0; i < count; i++) free(plugins[i]);
}
