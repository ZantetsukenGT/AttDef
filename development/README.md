# AttDef

## If you just want to run the server, you're looking for the [latest release](https://github.com/ZantetsukenGT/AttDef/releases/latest), you may also want to read the [Runtime prerequisites](#runtime-prerequisites) and [Actually running the server](#actually-running-the-server) sections

# Table of Contents

- [Repository layout](#repository-layout)
- [Build prerequisites](#build-prerequisites)
- [Runtime prerequisites](#runtime-prerequisites)
  - [Linux](#linux)
  - [Windows](#windows)
- [How to build](#how-to-build)
  - [Debug and release builds](#debug-and-release-builds)
  - [Adding or updating a dependency](#adding-or-updating-a-dependency)
- [Moving from sampctl](#moving-from-sampctl)
- [Just before running the server](#just-before-running-the-server)
  - [Scriptfiles](#scriptfiles)
  - [config.json](#configjson)
- [Actually running the server](#actually-running-the-server)
- [Collaboration](#collaboration)

# Repository layout

```
attdef/
├── development/              gamemode source code and everything needed to compile it
│   ├── gamemodes/            attdef.pwn, the entry point of the gamemode
│   ├── legacy/               legacy gamemode modules from early developers
│   ├── modules/              gamemode modules, reorganization from me
│   ├── dependencies/         third party includes (YSI, sscanf, Pawn.RakNet, etc), bundled
│   ├── compiler-v3.10.11/    the pawncc compiler, for linux and windows, bundled
│   ├── build-for-linux.sh    compiles the gamemode on linux
│   └── build-for-windows.cmd compiles the gamemode on windows
├── runtime_linux/            a ready to use open.mp server for linux
└── runtime_windows/          a ready to use open.mp server for windows
```

# Build prerequisites

Nothing needs to be installed to compile the gamemode: the compiler (`pawncc` v3.10.11) and every include the gamemode depends on are already part of the repository.

- [Git](https://git-scm.com/), only if you want to clone the repository instead of downloading it as a zip archive.
- On Linux, `pawncc` is a 32bit program, so you need the same 32bit libraries the server needs, see [Runtime prerequisites - Linux](#linux).

# Runtime prerequisites
## Linux
If you're planning to run the server on a Linux machine, keep in mind that omp-server is still a 32bit process as of now.

You may need to install the i386 architecture and install the 32bit version of the C++ Standard Library runtime, the installation procedure may vary depending on your distro:

If your package manager is APT (Debian, Ubuntu, etc), you can achieve this by running:

```bash
dpkg --add-architecture i386 && apt-get update && apt-get install libstdc++6:i386 libatomic1:i386
```

If you're unsure, research how to do this on your machine!

## Windows
If you're planning to run the server on a Windows machine, you **may or may not** need to install the [MVSC runtimes.](https://www.techpowerup.com/download/visual-c-redistributable-runtime-package-all-in-one/)

# How to build

Clone the project or download the project in a zip archive:

```bash
git clone https://github.com/ZantetsukenGT/AttDef attdef
```

Run the build script for your platform. The scripts locate everything relative to their own folder, so you can run them from anywhere (on Windows you can also just double-click `build-for-windows.cmd`):

```bash
#linux
cd ./attdef/development/
./build-for-linux.sh

#windows
cd .\attdef\development\
.\build-for-windows.cmd
```

The compiled `attdef.amx` file is written straight into the server's `gamemodes/` folder:

- Linux: `runtime_linux/gamemodes/attdef.amx`
- Windows: `runtime_windows/gamemodes/attdef.amx`

## Debug and release builds

The scripts build with the `-d3` flag (debug symbols included, useful for development and for crashdetect to output useful info).

For a release build without debug symbols, change `-d3` to `-d0` in the build script before running it.

## Adding or updating a dependency

Dependencies are plain folders inside `development/dependencies/`, there is no sampctl involved anymore:

1. Copy the library (or its new version) into `development/dependencies/`, check the existing dependencies to know how to install things correctly.
2. If it's a new library, add its include folder as an `-i` flag to **both** `build-for-linux.sh` and `build-for-windows.cmd`, so the two platforms keep building the same way; again, follow the existing lines as examples to know how to do it correctly.
3. If the library comes with a plugin or component, put the `.so` file in `runtime_linux/` and the `.dll` file in `runtime_windows/` (`plugins/` or `components/`, depending on what the library is).

At any rate if you're not adding new dependencies none of this is required.

# Moving from sampctl

This project used to be built with [sampctl](https://github.com/Southclaws/sampctl), which has been removed completely, now every dependency is pinned to keep things simple since there's no need for further dependency updates.

# Just before running the server

The `runtime_linux/` and `runtime_windows/` folders already contain a configured open.mp server, the plugins and components are in place, so there isn't much left to do.

## Scriptfiles

In the `scriptfiles/` folder:

1. If there's no `AttDefDatabase.db` file, make a copy of the `AttDefDatabase.db.example` file and rename it to `AttDefDatabase.db` or the server won't start properly.

## config.json

In the `config.json` file:

1. In the `"rcon"."password"` property, change it from the default.

It is recommended to use the `config.json` customizations from the [latest release](https://github.com/ZantetsukenGT/AttDef/releases/latest)

# Actually running the server
Use your preferred way to start the server, from inside the runtime folder:

```bash
#On Windows
cd .\runtime_windows
.\omp-server.exe

#On Linux
cd ./runtime_linux
./omp-server
```

This works fine until you need to log off, on Windows, the process will stay alive as long as the machine is turned on and in Linux the process will be terminated.

Hint: research how to configure the process as a service in your operating system of choice.

# Collaboration

This project is open for collaboration, create a fork, start from [How to build](#how-to-build) and make a pull request!
