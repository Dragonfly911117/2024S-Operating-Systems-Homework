## How to build

- Requirement: CMake 3.27(or above)

  ```bash
  build_dir=<build_directory>

  cmake -B $(build_dir>
  cmake --build $(build_dir)
  ```

  The built binary files will be located at `$(PROJECT_ROOT)/bin/applications`.
- For the kernel modules, one need to explicitly told CMake to build the target `mkm`(**M**ake **K**ernel **M**odule)
  or `ckm`(**C**lean **K**ernel **M**odule)

  ```bash
   cmake --build $(build_dir) --target mkm
  ```

  The built kernel modules will be located at `$(PROJECT_ROOT)/bin/kernel_modules`.

    - Note: The script does **not** (un)install the modules.

## Team members and responsibility

110590034: code, doc

110590035: code, doc

110590048: code, doc

110590066: code, doc
