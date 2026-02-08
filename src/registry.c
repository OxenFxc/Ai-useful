#include "common.h"

static ModuleOption os_modules[] = {
    {MSG_APT_MENU, menu_apt}
};

static ModuleOption dev_modules[] = {
    {MSG_PIP_MENU, menu_pip},
    {MSG_NPM_MENU, menu_npm},
    {MSG_GO_MENU, menu_go},
    {MSG_RUST_MENU, menu_rust}
};

static ModuleOption service_modules[] = {
    {MSG_DOCKER_MENU, menu_docker},
    {MSG_GITHUB_MENU, menu_github}
};

static ModuleOption toolbox_modules[] = {
    {MSG_CAT_TOOLBOX, menu_toolbox},
    {MSG_PLUGINS, menu_plugins}
};

MenuCategory categories[] = {
    {MSG_CAT_OS, os_modules, sizeof(os_modules)/sizeof(os_modules[0])},
    {MSG_CAT_DEV, dev_modules, sizeof(dev_modules)/sizeof(dev_modules[0])},
    {MSG_CAT_SERVICES, service_modules, sizeof(service_modules)/sizeof(service_modules[0])},
    {MSG_CAT_TOOLBOX, toolbox_modules, sizeof(toolbox_modules)/sizeof(toolbox_modules[0])}
};

int num_categories = sizeof(categories) / sizeof(categories[0]);
