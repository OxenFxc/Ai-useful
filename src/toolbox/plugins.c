#include "common.h"
#include <dirent.h>

typedef struct {
    char name[256];
    char title[256];
    char desc[512];
} PluginInfo;

static void get_plugin_info(const char *filename, PluginInfo *info) {
    strcpy(info->name, filename);
    strcpy(info->title, filename);
    strcpy(info->desc, "No description available.");

    char path[512];
    snprintf(path, sizeof(path), "./plugins/%s", filename);
    FILE *fp = fopen(path, "r");
    if (fp) {
        char line[1024];
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "# Title:", 8) == 0) {
                sscanf(line + 8, " %[^\n]", info->title);
            } else if (strncmp(line, "# Description:", 14) == 0) {
                sscanf(line + 14, " %[^\n]", info->desc);
            }
        }
        fclose(fp);
    }
}

void menu_plugins() {
    DIR *d;
    struct dirent *dir;
    PluginInfo plugins[64];
    int count = 0;

    print_header("Plugin Manager");
    d = opendir("./plugins");
    if (d) {
        while ((dir = readdir(d)) != NULL && count < 64) {
            if ((dir->d_type == DT_REG || dir->d_type == DT_LNK) && dir->d_name[0] != '.') {
                get_plugin_info(dir->d_name, &plugins[count]);
                printf("%d. %s (%s)\n   - %s\n", count + 1, plugins[count].title, plugins[count].name, plugins[count].desc);
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
        // Quoting the path to handle spaces safely
        snprintf(cmd, sizeof(cmd), "\"./plugins/%s\"", plugins[choice - 1].name);
        run_command(cmd);
    }
}
