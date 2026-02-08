#include "common.h"

static void apply_maven_mirror(const char *unused) {
    (void)unused;
    char path[512];
    snprintf(path, sizeof(path), "%s/.m2", getenv("HOME"));
    run_command("mkdir -p ~/.m2");

    strcat(path, "/settings.xml");
    backup_file(path);

    const char *content =
        "<settings>\n"
        "  <mirrors>\n"
        "    <mirror>\n"
        "      <id>aliyunmaven</id>\n"
        "      <mirrorOf>*</mirrorOf>\n"
        "      <name>Aliyun Maven</name>\n"
        "      <url>https://maven.aliyun.com/repository/public</url>\n"
        "    </mirror>\n"
        "  </mirrors>\n"
        "</settings>\n";

    if (write_file_content(path, content) == 0) {
        printf(COLOR_GREEN "Maven mirror configured to Aliyun." COLOR_RESET "\n");
    }
}

static void apply_gradle_mirror(const char *unused) {
    (void)unused;
    char path[512];
    snprintf(path, sizeof(path), "%s/.gradle", getenv("HOME"));
    run_command("mkdir -p ~/.gradle");

    strcat(path, "/init.gradle");
    backup_file(path);

    const char *content =
        "allprojects {\n"
        "    repositories {\n"
        "        maven { url 'https://maven.aliyun.com/repository/public' }\n"
        "        maven { url 'https://maven.aliyun.com/repository/google' }\n"
        "        maven { url 'https://maven.aliyun.com/repository/jcenter' }\n"
        "    }\n"
        "}\n";

    if (write_file_content(path, content) == 0) {
        printf(COLOR_GREEN "Gradle mirror configured to Aliyun." COLOR_RESET "\n");
    }
}

void menu_jvm() {
    int choice;
    while (1) {
        print_header("JVM (Maven/Gradle) Mirror Configuration");
        printf("1. Configure Maven (Aliyun)\n");
        printf("2. Configure Gradle (Aliyun)\n");
        printf("0. %s\n", get_msg(MSG_BACK));
        printf("%s", get_msg(MSG_ENTER_CHOICE));
        if (scanf("%d", &choice) != 1) { clear_input_buffer(); break; }
        clear_input_buffer();
        if (choice == 1) apply_maven_mirror(NULL);
        else if (choice == 2) apply_gradle_mirror(NULL);
        else if (choice == 0) break;
    }
}
