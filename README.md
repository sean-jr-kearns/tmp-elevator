# tmp-elevator
This project represents a possible implementation of an elevator. To provide 
details on personal interactions with various languages the initial solution 
is a prototype in python under `./prototypes` and the core implementation 
is with c++17.

## Assumptions
There are several assumptions associated with the project and can be found below.

### System Specific
The user has `sudo` access for installations and is operating on a `Linux x64_64`
machine. 

**Note** these requirements could be resovled by developing/deploying within a container.

### Elevator Specific
The elevator project implementation itself has some built-in assumptions as well:

- Floor travel time is fixed at 10 seconds
- 3 arguments are expected for the executable
- Ordered inputs for the executable are:

| name | type | example |
| --- | --- | --- |
| number of floors | int | 12 |
| starting floor | int | 4 |
| floors to traverse | string | 1,2,6,15,77 |

- Only valid floors to traverse are provided as inputs
- Floors traversed will be in the order that they were received (e.g. FIFO)
- An elevator will not move if it has not received an input command
- Floor travel time also includes floor settling time
- No elevator capacity, fire safety, or building security settings are considered
- No elevator button input commands are considered (e.g. stream of input commands)
- No total travel time optimization has been implemented

## Getting Started
To get started making changes and building/deploying this project locally follow the steps in this section.

### Prerequisites
Although possible to build os/arch agnostic or with a containerized development
and deployment environment it will be assumed here that `Linux x86_64` is used.
Below are the required commands to install pre-reqs (e.g. `Ubuntu 22.04`).

```bash
sudo apt-get install build-essential cmake g++ Python3.10
sudo apt-get install gdb
sudo apt-get install cppcheck valgrind
pip3 install conan
pip3 show conan
conan profile detect
```

### Verifying installation requirements
Below are commands to sanity check installations occurred as expected.

```bash
g++ --version
cppcheck --version
valgrind --version
python3 --version
gdb --version
conan --version
```

One can make changes in the future to their conan profile here `~/.conan2/profiles/default`.

### Static Analysis
To run static analysis on this project execute the following:

```bash
cd ~/{project-root}/src
cppcheck --enable=all --inconclusive --std=c++17 --output-file=./reports/cppcheck_report.txt .
```

Validate in this projects reports directory that `cppcheck_report.txt` is empty

### Dynamic Analysis
To run dynamic analysis on this project execute the following:

```bash
cd ~/{project-root}/deploy
valgrind --leak-check=full --show-leak-kinds=all \
         --track-origins=yes --log-file=../reports/valgrind_report.txt \
         ./bin/main 100 12 1,2,12,17,99 
```

On completion a report like below should be produced in this projects `reports` directory

```log
==27536== Memcheck, a memory error detector
==27536== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==27536== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==27536== Command: ./bin/main 100 12 1,2,12,17,99
==27536== Parent PID: 468
==27536== 
==27536== 
==27536== HEAP SUMMARY:
==27536==     in use at exit: 0 bytes in 0 blocks
==27536==   total heap usage: 29 allocs, 29 frees, 82,347 bytes allocated
==27536== 
==27536== All heap blocks were freed -- no leaks are possible
==27536== 
==27536== For lists of detected and suppressed errors, rerun with: -s
==27536== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### Build
Now, to build the project execute the following commands from the project's root directory (e.g. `~/{project-root}`).

```bash
conan create . -o with_tests=True --build=missing
```

Then verify that the local conan cache has the package.

```bash
conan list
```

```log
Found 2 pkg/version recipes matching * in local cache
Local Cache
  elevator
    elevator/1.0.0
```

### Install
Once verified install the package locally to execute.

```
cd ~/{package-root}/deploy 
conan install --requires elevator/${VERSION} --deployer-package elevator/${VERSION}
```

The deployment should look similar to this

![deployment](./files/images/deployment-example.jpg)

### Run
From the `deploy` directory execute the program with the following command. Positional arguments are `number_of_floors`, `staring_floor`, and `floors_to_traverse`.

```bash
./bin/main 15 12 1,2,12,17
[2025-07-18 16:59:09.013] [info] Executing elevator program ./bin/main, params 4
[2025-07-18 16:59:09.014] [info] Elevator constructor called.
[2025-07-18 16:59:09.014] [info] Traveling between floors 12 and 1
[2025-07-18 16:59:09.014] [info] Took 110 to reach floor 1
[2025-07-18 16:59:09.014] [info] Traveling between floors 12 and 2
[2025-07-18 16:59:09.014] [info] Took 100 to reach floor 2
[2025-07-18 16:59:09.014] [info] Traveling between floors 12 and 12
[2025-07-18 16:59:09.014] [info] Took 0 to reach floor 12
[2025-07-18 16:59:09.014] [info] Traveling between floors 12 and 17
[2025-07-18 16:59:09.014] [info] Took 50 to reach floor 17
[2025-07-18 16:59:09.014] [info] 370 12, 1, 2, 12, 17
[2025-07-18 16:59:09.014] [info] Elevator destructor called.
```

## Not Implemented
Below are features that may add value to the project over time:

- Runner access/instantiation
- Token/secret management (e.g. docker/gitlab/conan registry)
- `gitlab-ci.yml` (e.g. conan/docker deployment)
- `gitlab pages` (user guide documentation)
- `gcovr` report generation 
- Doxygen comments are added for cpp, but not generated into a document
- OS/ARCH agnostic deployment
- Elevator stream of inputs (from floors and buttons)
    - See `~/{project-root}/prototypes/elevator-prototype.ipynb` for more details
- Elevator configuration file
- Elevator interface/execution improvements (e.g. arg names aren't defined but could be from bash/docker-entrypoint.d)
- Visual representation of the elevator exists but with a gRPC interface and a react frontend users could start to visualize the elevator