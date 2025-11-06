# Sapienta
An engine to solve for reality.

**Velaris** - A 2D steady-state simulator of flight mechanics.

## Build Requirements
- Install Eigen locally at `~/libs/eigen-5.0.0`.
- Configure CMake with `-DCMAKE_PREFIX_PATH=~/libs/eigen-5.0.0` to ensure the project locates Eigen during the build.
- On WSL or Linux, install Qt tooling via `sudo apt install qt6-base-dev qt6-base-dev-tools`.