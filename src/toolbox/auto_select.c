#include "common.h"

typedef struct {
    const char *name;
    const char *url;
    double speed;
} BenchmarkResult;

void run_auto_optimizer() {
    print_header("Auto-Optimizer (Benchmarking Mirrors)");

    BenchmarkResult results[] = {
        {"Tsinghua", "https://mirrors.tuna.tsinghua.edu.cn", -1.0},
        {"Aliyun", "https://mirrors.aliyun.com", -1.0},
        {"USTC", "https://mirrors.ustc.edu.cn", -1.0},
        {"Baidu", "https://mirror.baidubce.com", -1.0},
        {"Netease", "https://mirrors.163.com", -1.0}
    };
    int n = sizeof(results) / sizeof(results[0]);

    printf("Benchmarking %d mirrors, please wait...\n", n);

    int best_index = -1;
    double min_time = 999.0;

    for (int i = 0; i < n; i++) {
        printf("Testing %-10s... ", results[i].name);
        fflush(stdout);
        results[i].speed = test_mirror_speed(results[i].url);
        if (results[i].speed >= 0) {
            printf(COLOR_GREEN "%.3fs" COLOR_RESET "\n", results[i].speed);
            if (results[i].speed < min_time) {
                min_time = results[i].speed;
                best_index = i;
            }
        } else {
            printf(COLOR_RED "Timeout/Error" COLOR_RESET "\n");
        }
    }

    if (best_index != -1) {
        printf("\n" COLOR_GREEN "Recommendation: %s is the fastest mirror (%.3fs)" COLOR_RESET "\n",
               results[best_index].name, results[best_index].speed);
        printf("You should choose %s in the respective configuration menus.\n", results[best_index].name);
    } else {
        printf("\n" COLOR_RED "Failed to benchmark any mirrors. Please check your network connection." COLOR_RESET "\n");
    }
}
