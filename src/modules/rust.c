#include "common.h"

static void apply_rust_mirror(const char *mirror_config) {
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
    const char *tsinghua =
        "[source.crates-io]\nreplace-with = 'tuna'\n\n"
        "[source.tuna]\nregistry = \"https://github.com/rust-lang/crates.io-index\"\n"
        "replace-with = 'tuna-index'\n\n"
        "[source.tuna-index]\nregistry = \"https://mirrors.tuna.tsinghua.edu.cn/git/crates.io-index.git\"\n";

    const char *ustc =
        "[source.crates-io]\nreplace-with = 'ustc'\n\n"
        "[source.ustc]\nregistry = \"git://mirrors.ustc.edu.cn/crates.io-index\"\n";

    MirrorSite sites[] = {
        {get_msg(MSG_MIRROR_TSINGHUA), tsinghua},
        {get_msg(MSG_MIRROR_USTC), ustc}
    };
    select_mirror_and_apply(get_msg(MSG_RUST_MENU), sites, 2, apply_rust_mirror);
}
