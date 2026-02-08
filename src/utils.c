#include "common.h"
#include <sys/stat.h>
#include <time.h>

int current_lang = LANG_CN; // Default to Chinese

static const char* messages[][2] = {
    [MSG_MAIN_TITLE] = {"Super Source Toolbox", "超级换源工具箱"},
    [MSG_APT_MENU] = {"APT Mirror (Debian/Ubuntu)", "APT 换源 (Debian/Ubuntu)"},
    [MSG_PIP_MENU] = {"Pip Mirror (Python)", "Pip 换源 (Python)"},
    [MSG_NPM_MENU] = {"NPM Registry (Node.js)", "NPM 换源 (Node.js)"},
    [MSG_GO_MENU] = {"Go Proxy", "Go 代理设置"},
    [MSG_RUST_MENU] = {"Rust (Cargo) Mirror", "Rust (Cargo) 换源"},
    [MSG_DOCKER_MENU] = {"Docker Registry", "Docker 换源"},
    [MSG_GITHUB_MENU] = {"GitHub Acceleration", "GitHub 加速"},
    [MSG_JVM_MENU] = {"JVM (Maven/Gradle)", "JVM (Maven/Gradle) 换源"},
    [MSG_FLUTTER_MENU] = {"Flutter/Dart", "Flutter/Dart 换源"},
    [MSG_DNS_MENU] = {"System DNS", "系统 DNS 设置"},
    [MSG_TOOLBOX_MENU] = {"Toolbox (System Info, Cleanup, etc.)", "工具箱 (系统信息, 清理等)"},
    [MSG_SPEED_TEST] = {"Run Mirror Speed Test", "运行镜像测速"},
    [MSG_AUTO_OPTIMIZER] = {"Auto-Optimizer", "自动优化 (镜像测速推荐)"},
    [MSG_EXIT] = {"Exit", "退出"},
    [MSG_ENTER_CHOICE] = {"Enter choice: ", "请输入选项: "},
    [MSG_INVALID_CHOICE] = {"Invalid choice.", "无效的选项。"},
    [MSG_BACK] = {"Back", "返回"},
    [MSG_EXECUTING] = {"Executing: %s", "正在执行: %s"},
    [MSG_BACKUP_TO] = {"Backing up %s to %s", "正在备份 %s 到 %s"},
    [MSG_SUCCESS] = {"Successfully changed mirror to %s", "成功更换源为 %s"},
    [MSG_FAILURE] = {"Failed to change mirror.", "更换源失败。"},
    [MSG_PERMISSION_DENIED] = {"Error: No write permission. Try running with sudo.", "错误：没有写入权限。请尝试使用 sudo。"},
    [MSG_CLEANUP_TITLE] = {"System Cleanup", "系统清理"},
    [MSG_SYSINFO_TITLE] = {"System Information", "系统信息"},
    [MSG_MIRROR_TSINGHUA] = {"Tsinghua University", "清华大学镜像源"},
    [MSG_MIRROR_ALIYUN] = {"Alibaba Cloud", "阿里云镜像源"},
    [MSG_MIRROR_USTC] = {"USTC", "中科大镜像源"},
    [MSG_MIRROR_TAOBAO] = {"Taobao (npmmirror)", "淘宝镜像源 (npmmirror)"},
    [MSG_MIRROR_OFFICIAL] = {"Official Registry", "官方源"},
    [MSG_RESTARTING_DOCKER] = {"Restarting Docker service...", "正在重启 Docker 服务..."},
    [MSG_LANG_SELECT] = {"Change Language (English/中文)", "切换语言 (English/中文)"},
    [MSG_CAT_OS] = {"OS Mirrors", "操作系统换源"},
    [MSG_CAT_DEV] = {"Development Environments", "开发环境换源"},
    [MSG_CAT_SERVICES] = {"Services & Acceleration", "服务与加速"},
    [MSG_CAT_TOOLBOX] = {"System Toolbox", "系统工具箱"},
    [MSG_PLUGINS] = {"Plugin Manager", "插件管理"}
};

const char* get_msg(int msg_id) {
    return messages[msg_id][current_lang];
}

void save_config() {
    char path[512];
    snprintf(path, sizeof(path), "%s/.super-source.conf", getenv("HOME"));
    FILE *fp = fopen(path, "w");
    if (fp) {
        fprintf(fp, "lang=%d\n", current_lang);
        fclose(fp);
    }
}

void load_config() {
    char path[512];
    snprintf(path, sizeof(path), "%s/.super-source.conf", getenv("HOME"));
    FILE *fp = fopen(path, "r");
    if (fp) {
        if (fscanf(fp, "lang=%d", &current_lang) != 1) {
            current_lang = LANG_CN;
        }
        fclose(fp);
    }
}

int run_command(const char *cmd) {
    printf(COLOR_BLUE);
    printf(get_msg(MSG_EXECUTING), cmd);
    printf(COLOR_RESET "\n");
    return system(cmd);
}

int backup_file(const char *filepath) {
    if (access(filepath, F_OK) == -1) {
        return 0; // File doesn't exist, no need to backup
    }

    char backup_path[512];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(backup_path, sizeof(backup_path), "%s.bak.%d%02d%02d_%02d%02d%02d",
             filepath, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
             tm.tm_hour, tm.tm_min, tm.tm_sec);

    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "cp %s %s", filepath, backup_path);
    printf(COLOR_YELLOW);
    printf(get_msg(MSG_BACKUP_TO), filepath, backup_path);
    printf(COLOR_RESET "\n");
    return system(cmd);
}

int write_file_content(const char *filepath, const char *content) {
    FILE *fp = fopen(filepath, "w");
    if (fp == NULL) {
        perror("fopen");
        return -1;
    }
    fprintf(fp, "%s", content);
    fclose(fp);
    return 0;
}

void print_header(const char *title) {
    printf("\n" COLOR_GREEN "=== %s ===" COLOR_RESET "\n", title);
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void select_mirror_and_apply(const char *title, MirrorSite *sites, int num_sites, void (*apply_func)(const char*)) {
    int choice;
    while (1) {
        print_header(title);
        for (int i = 0; i < num_sites; i++) {
            printf("%d. %s\n", i + 1, sites[i].name);
        }
        printf("0. %s\n", get_msg(MSG_BACK));
        printf("%s", get_msg(MSG_ENTER_CHOICE));

        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (choice == 0) break;
        if (choice > 0 && choice <= num_sites) {
            apply_func(sites[choice - 1].url);
            break;
        } else {
            printf(COLOR_RED "%s" COLOR_RESET "\n", get_msg(MSG_INVALID_CHOICE));
        }
    }
}

double test_mirror_speed(const char *url) {
    char cmd[1024];
    // Use curl to get total time. Redirect output to a temp file and read it.
    snprintf(cmd, sizeof(cmd), "curl -o /dev/null -s -w \"%%{time_total}\" --connect-timeout 2 --max-time 5 %s", url);

    FILE *fp = popen(cmd, "r");
    if (fp == NULL) return -1.0;

    double duration = -1.0;
    if (fscanf(fp, "%lf", &duration) != 1) duration = -1.0;
    pclose(fp);

    return duration;
}
