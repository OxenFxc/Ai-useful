# Super Source Toolbox

Super Source Toolbox is a modular, C-based utility designed to optimize your development environment by switching package manager sources to faster mirrors (primarily Chinese domestic mirrors), managing system DNS settings, and performing network diagnostics.

It features an interactive menu system, automatic mirror speed testing, and a plugin architecture for easy extensibility.

## Features

### Package Manager Mirrors
Switch sources for a wide variety of package managers and tools:
- **APT**: Debian and Ubuntu (supports traditional `sources.list` and DEB822 format).
- **Docker**: Registry mirrors.
- **Pip**: Python package index.
- **Go**: GOPROXY settings.
- **NPM**: Node.js package manager.
- **Maven / Gradle**: Java build tools.
- **Flutter**: Dart/Flutter SDK.
- **Composer**: PHP dependency manager.
- **RubyGems**: Ruby package manager.
- **Rust (Cargo)**: Rust crate registry.
- **GitHub**: Acceleration for git operations.

### System Tools
- **DNS Management**: Switch system DNS to public providers (e.g., AliDNS, Google DNS).
- **Network Diagnostics**: Check public/local IP, ping tests.
- **System Info**: View system details.
- **Clean**: System cleanup utilities.

### Advanced Features
- **Auto-Optimizer**: Automatically benchmarks available mirrors and selects the fastest one.
- **Plugins**: Extend functionality by placing shell scripts in the `plugins/` directory.
- **Bilingual Support**: Fully localized interface in English and Chinese.

## Installation

### Prerequisites
- A Linux system (optimized for Ubuntu 24.04, but compatible with other Debian-based distros).
- `gcc` and `make` for compilation.

### Building from Source

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/super-source.git
   cd super-source
   ```

2. Compile the project:
   ```bash
   make
   ```

This will generate the `super-source` executable.

## Usage

### Interactive Mode
Run the tool with `sudo` privileges to modify system configuration files:

```bash
sudo ./super-source
```

Navigate the menu by entering the corresponding number for the desired category or action.

### Command Line Arguments

- **Run Auto-Optimizer**: Automatically find and apply the fastest mirrors.
  ```bash
  sudo ./super-source --auto
  ```

- **Show Help**:
  ```bash
  ./super-source --help
  ```

- **Show Version**:
  ```bash
  ./super-source --version
  ```

## Contributing

Contributions are welcome! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for details on how to contribute to this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
