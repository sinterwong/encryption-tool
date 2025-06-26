# EncryptionTool

EncryptionTool is a command-line utility for encrypting and decrypting files using AES encryption. It leverages the Crypto++ library for cryptographic operations.

## Prerequisites

Before you begin, ensure you have the following installed:

*   **CMake** (version 3.10 or higher)
*   **C++20 compatible compiler** (e.g., GCC, Clang, MSVC)

The following libraries are included as Git submodules in the `3rdparty` directory and will be built automatically with the project:

*   **Crypto++**: For cryptographic algorithms. (via `cryptopp-cmake`)
*   **gflags**: For command-line flag parsing in the `cryptor` tool.
*   **googletest**: For unit testing.

## Building the Project

1.  **Clone the repository (if you haven't already):**
    ```bash
    git clone --recurse-submodules <repository-url>
    cd encryption-tool
    ```
    If you have already cloned the repository without the submodules, you can initialize them:
    ```bash
    git submodule update --init --recursive
    ```

2.  **Configure the project using CMake:**
    Create a build directory and run CMake from there:
    ```bash
    mkdir build
    cd build
    cmake ..
    ```

    **Build Options:**
    You can customize the build using the following CMake options (passed with `-D<OPTION_NAME>=<VALUE>`):
    *   `CMAKE_BUILD_TYPE`: Specifies the build type (e.g., `Debug`, `Release`, `RelWithDebInfo`). Defaults to `RelWithDebInfo`.
    *   `BUILD_ENCRYPTION_TOOL_TESTS`: Set to `ON` to build unit tests (e.g., `cmake -DBUILD_ENCRYPTION_TOOL_TESTS=ON ..`). Defaults to `OFF`.
    *   `BUILD_ENCRYPTION_TOOLS`: Set to `ON` to build the `cryptor` command-line tool (e.g., `cmake -DBUILD_ENCRYPTION_TOOLS=ON ..`). Defaults to `ON`.

    For example, to build with tools and tests enabled:
    ```bash
    cmake -DBUILD_ENCRYPTION_TOOLS=ON -DBUILD_ENCRYPTION_TOOL_TESTS=ON ..
    ```

3.  **Build the project:**
    After configuration, run the build command:
    ```bash
    cmake --build .
    ```
    Or, on systems with Makefiles:
    ```bash
    make
    ```

    The build output will be located in the `build/<target_arch>` directory (e.g., `build/x86_64/bin` for executables and `build/x86_64/lib` for libraries).

## Tool Usage (`cryptor`)

The `cryptor` tool allows you to encrypt and decrypt files. It is located at `build/<target_arch>/bin/tools/cryptor` if `BUILD_ENCRYPTION_TOOLS` is enabled.

**Synopsis:**
```bash
./build/<target_arch>/bin/tools/cryptor --mode=<encrypt|decrypt> --input=<path> --output=<path> [options...]
```

**Required Flags:**

*   `--mode=<encrypt|decrypt>`: Operation mode.
*   `--input=<path>`: Path to the input file.
*   `--output=<path>`: Path to the output file.

**Key/IV Management Options (Choose one):**

*   `--generate_key`: Generate a new random key and IV.
*   `--key_file=<path>` and `--iv_file=<path>`: Use an existing key and IV from the specified files. The key and IV files should contain the raw binary data.
*   `--commit=<hash>`: Use a 40-character SHA-1 Git commit hash to derive the key and IV.

**Optional Flags:**

*   `--save_key=<path>`: If `--generate_key` is used, save the generated key to this file.
*   `--save_iv=<path>`: If `--generate_key` is used, save the generated IV to this file.
*   `--show_hash`: Display the SHA256 hash of the output file after the operation.

**Examples:**

1.  **Encrypt a file with a generated key:**
    ```bash
    ./build/x86_64/bin/tools/cryptor --mode=encrypt --input=mydata.txt --output=mydata.enc --generate_key --save_key=key.bin --save_iv=iv.bin
    ```

2.  **Decrypt a file using a saved key and IV:**
    ```bash
    ./build/x86_64/bin/tools/cryptor --mode=decrypt --input=mydata.enc --output=mydata.dec --key_file=key.bin --iv_file=iv.bin
    ```

3.  **Encrypt a file using a commit hash:**
    ```bash
    ./build/x86_64/bin/tools/cryptor --mode=encrypt --input=sensitive.doc --output=sensitive.enc --commit=0a053c18fa5d73b5fc9f2e06855c5640e052263b
    ```

## Unit Testing

Unit tests are provided to verify the functionality of the encryption library.

1.  **Enable Tests During CMake Configuration:**
    When configuring CMake, set the `BUILD_ENCRYPTION_TOOL_TESTS` option to `ON`:
    ```bash
    cd build # (or create it if it doesn't exist)
    cmake -DBUILD_ENCRYPTION_TOOL_TESTS=ON ..
    ```

2.  **Build the Project:**
    ```bash
    cmake --build .
    ```

3.  **Run the Tests:**
    After install, the test executable `main` will be located in `install/tests/`.
    Navigate to your build directory and run it:
    ```bash
    cd install/
    ./tests/main
    ```


This README provides a comprehensive guide to setting up, building, using, and testing the EncryptionTool.
