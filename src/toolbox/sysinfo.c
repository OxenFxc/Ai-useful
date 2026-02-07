#include "common.h"

void show_sysinfo() {
    print_header("System Information");
    run_command("uname -a");
    run_command("cat /etc/os-release | grep PRETTY_NAME");
    run_command("lscpu | grep 'Model name'");
    run_command("free -h");
    run_command("df -h /");
}
