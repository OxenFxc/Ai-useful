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

// Utility functions
int run_command(const char *cmd);
int backup_file(const char *filepath);
int write_file_content(const char *filepath, const char *content);
void print_header(const char *title);
void clear_input_buffer();

// Module functions
void menu_apt();
void menu_pip();
void menu_npm();
void menu_toolbox();

#endif
