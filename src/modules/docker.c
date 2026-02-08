#include "common.h"

void change_docker_mirror(const char *mirror_url) {
    const char *config_path = "/etc/docker/daemon.json";

    if (access("/etc/docker", W_OK) == -1) {
        printf(COLOR_RED "%s (/etc/docker)" COLOR_RESET "\n", get_msg(MSG_PERMISSION_DENIED));
        return;
    }

    backup_file(config_path);

    char content[1024];
    snprintf(content, sizeof(content), "{\n  \"registry-mirrors\": [\"%s\"]\n}\n", mirror_url);

    if (write_file_content(config_path, content) == 0) {
        printf(COLOR_GREEN);
        printf(get_msg(MSG_SUCCESS), mirror_url);
        printf(COLOR_RESET "\n");
        printf("%s\n", get_msg(MSG_RESTARTING_DOCKER));
        run_command("systemctl restart docker");
    } else {
        printf(COLOR_RED "%s" COLOR_RESET "\n", get_msg(MSG_FAILURE));
    }
}

void menu_docker() {
    int choice;
    print_header(get_msg(MSG_DOCKER_MENU));
    printf("1. %s\n", get_msg(MSG_MIRROR_ALIYUN));
    printf("2. Azure China\n");
    printf("3. Baidu Cloud\n");
    printf("0. %s\n", get_msg(MSG_BACK));
    printf("%s", get_msg(MSG_ENTER_CHOICE));
    if (scanf("%d", &choice) != 1) {
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    switch (choice) {
        case 1:
            change_docker_mirror("https://mirrors.aliyun.com");
            break;
        case 2:
            change_docker_mirror("https://dockerhub.azk8s.cn");
            break;
        case 3:
            change_docker_mirror("https://mirror.baidubce.com");
            break;
        default:
            break;
    }
}
