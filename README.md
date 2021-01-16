# CS744-PA3-Custom-Malloc

- **Subject** - Design and Engineering of Computing Systems (CS 744)

- **Assignment 4** - Memory allocation and management in C
    - Write custom memory management logic in `mm1.c` and `mm2.c`.
    - Refer [PA3 - Problem Statement.pdf](./PA3%20-%20Problem%20Statement.pdf) for the complete problem statement.

- **Team Members**
    - 203050054 - Fenil Mehta
    - 203050110 - Vipin Mahawar


### Installing dependencies

```sh
# 32 bit environment (i.e. "-m32" flag) is required because address space
# in 64 bit environment will be too huge to perform the stress test.

# Use one of the below two commands depending on the version of gcc installed to install 32 bit libraries.
sudo apt install gcc-multilib
# OR
sudo apt install gcc-9-multilib

# This will fix the error:
#     /usr/include/stdio.h:27:10: fatal error: bits/libc-header-start.h: No such file or directory
```


### Compiling and Evaluating the solution

- Refer [README](./PA_3_handout/README) for instructions
- Below is the simplified version of the above instructions

    ```sh
    # Change the working directory
    cd "PA_3_handout"

    # Compile the program:
    #     mm1.c ---> mdriver1
    #     mm2.c ---> mdriver2
    make

    # Evaluate mm1.c (mdriver1)
    for i in $(echo "short1-bal.rep short2-bal.rep short3-bal.rep binary-bal.rep cp-decl-bal.rep random-bal.rep realloc-bal.rep");
    do
    echo -e "\n----------------- Working on ${i} -----------------"
    ./mdriver1 -V -f "traces/${i}"
    done

    # Evaluate mm2.c (mdriver2)
    for i in $(echo "short1-bal.rep short2-bal.rep short3-bal.rep binary-bal.rep cp-decl-bal.rep random-bal.rep realloc-bal.rep");
    do
    echo -e "\n----------------- Working on ${i} -----------------"
    ./mdriver2 -V -f "traces/${i}" 2>&1
    done
    ```

