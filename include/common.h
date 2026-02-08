#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"

// Language IDs
#define LANG_EN 0
#define LANG_CN 1

extern int current_lang;

// Message IDs
enum {
    MSG_MAIN_TITLE,
    MSG_APT_MENU,
    MSG_PIP_MENU,
    MSG_NPM_MENU,
    MSG_GO_MENU,
    MSG_RUST_MENU,
    MSG_DOCKER_MENU,
    MSG_GITHUB_MENU,
    MSG_TOOLBOX_MENU,
    MSG_SPEED_TEST,
    MSG_EXIT,
    MSG_ENTER_CHOICE,
    MSG_INVALID_CHOICE,
    MSG_BACK,
    MSG_EXECUTING,
    MSG_BACKUP_TO,
    MSG_SUCCESS,
    MSG_FAILURE,
    MSG_PERMISSION_DENIED,
    MSG_CLEANUP_TITLE,
    MSG_SYSINFO_TITLE,
    MSG_MIRROR_TSINGHUA,
    MSG_MIRROR_ALIYUN,
    MSG_MIRROR_USTC,
    MSG_MIRROR_TAOBAO,
    MSG_MIRROR_OFFICIAL,
    MSG_RESTARTING_DOCKER,
    MSG_LANG_SELECT,
    MSG_CAT_OS,
    MSG_CAT_DEV,
    MSG_CAT_SERVICES,
    MSG_CAT_TOOLBOX,
    MSG_PLUGINS
};

// Generic Menu structures for decoupling
typedef void (*MenuFunc)();

typedef struct {
    int title_msg_id;
    MenuFunc func;
} ModuleOption;

typedef struct {
    int title_msg_id;
    ModuleOption *options;
    int num_options;
} MenuCategory;

// Generic Mirror structure
typedef struct {
    const char *name;
    const char *url;
} MirrorSite;

// Utility functions
int run_command(const char *cmd);
int backup_file(const char *filepath);
int write_file_content(const char *filepath, const char *content);
void print_header(const char *title);
void clear_input_buffer();
double test_mirror_speed(const char *url);
const char* get_msg(int msg_id);
void save_config();
void load_config();

// Generic selection UI
void select_mirror_and_apply(const char *title, MirrorSite *sites, int num_sites, void (*apply_func)(const char*));

// Registry exports
extern MenuCategory categories[];
extern int num_categories;

// Module functions (to be refactored into registry)
void menu_apt();
void menu_pip();
void menu_npm();
void menu_docker();
void menu_toolbox();
void show_sysinfo();
void menu_rust();
void menu_go();
void menu_github();
void menu_plugins();

#endif
