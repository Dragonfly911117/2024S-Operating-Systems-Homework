## How to build

- Environment & Requirement: 
  - Linux Kernel 6.6.22-1-lts
  - GCC Version: 13.2.1 20230801
  - CMake 3.27
  - GNU Make: 4.4.1
  
  ```bash
  build_dir=<build_directory>
  
  cmake -B $(build_dir)
  cmake --build $(build_dir)
  ```

  The built binary files will be located at `$(PROJECT_ROOT)/bin/`.

  Note: The script does **not** (un)install the modules.

## Team members and responsibility

110590034: code, doc

110590035: code, doc

110590048: code, doc

110590066: code, doc

