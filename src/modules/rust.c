#include "common.h"

void change_rust_mirror(const char *mirror_config) {
    char path[512];
    snprintf(path, sizeof(path), "%s/.cargo/config.toml", getenv("HOME"));

    printf(COLOR_YELLOW "WARNING: This will overwrite ~/.cargo/config.toml. Proceed? (y/n): " COLOR_RESET);
    char confirm;
    if (scanf(" %c", &confirm) != 1 || (confirm != 'y' && confirm != 'Y')) {
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    backup_file(path);

    if (write_file_content(path, mirror_config) == 0) {
        printf(COLOR_GREEN);
        printf(get_msg(MSG_SUCCESS), "Rust (Cargo)");
        printf(COLOR_RESET "\n");
    } else {
        printf(COLOR_RED "%s" COLOR_RESET "\n", get_msg(MSG_FAILURE));
    }
}

void menu_rust() {
    int choice;
    print_header("Rust (Cargo) Mirror Configuration");
    printf("1. %s\n", get_msg(MSG_MIRROR_TSINGHUA));
    printf("2. %s\n", get_msg(MSG_MIRROR_USTC));
    printf("0. %s\n", get_msg(MSG_BACK));
    printf("%s", get_msg(MSG_ENTER_CHOICE));
    if (scanf("%d", &choice) != 1) {
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    const char *tsinghua =
        "[source.crates-io]\n"
        "replace-with = 'tuna'\n\n"
        "[source.tuna]\n"
        "registry = \"https://github.com/rust-lang/crates.io-index\"\n"
        "replace-with = 'tuna-index'\n\n"
        "[source.tuna-index]\n"
        "registry = \"https://mirrors.tuna.tsinghua.edu.cn/git/crates.io-index.git\"\n";

    const char *ustc =
        "[source.crates-io]\n"
        "replace-with = 'ustc'\n\n"
        "[source.ustc]\n"
        "registry = \"git://mirrors.ustc.edu.cn/crates.io-index\"\n";

    switch (choice) {
        case 1:
            change_rust_mirror(tsinghua);
            break;
        case 2:
            change_rust_mirror(ustc);
            break;
        default:
            break;
    }
}
