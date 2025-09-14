# AttDef

## If you just want to run the server, you're looking for the [latest release](https://github.com/ZantetsukenGT/AttDef/releases/latest), you may also want to read the [Runtime prerrequisites](#runtime-prerrequisites) and [Actually running the server](#actually-running-the-server) sections

# Table of Contents

- [Build prerrequisites](#build-prerrequisites)
- [Runtime prerrequisites](#runtime-prerrequisites)
  - [Linux](#linux)
  - [Windows](#windows)
- [How to build](#how-to-build)
- [Just before running the server](#just-before-running-the-server)
  - [Delete server.cfg](#delete-servercfg)
  - [Plugins and components](#plugins-and-components)
  - [Scriptfiles](#scriptfiles)
  - [config.json](#configjson)
- [Actually running the server](#actually-running-the-server)
  - [Setting up the server to automatically start](#setting-up-the-server-to-automatically-start)
- [Collaboration and Pull Requests](#collaboration-and-pull-requests)


# Build prerrequisites
Install the following in order to compile the gamemode:
- Git v2.39.x, because sampctl requires it
- [sampctl version 1.11.3 installed, manual installation recommended](https://github.com/Southclaws/sampctl/wiki/Windows#installing-manually)
  - Following [sampctl's config wiki](https://github.com/Southclaws/sampctl/wiki/Configuration), configure `git_username` and `github_token` within `config.json` or you may hit github's rate limits.
    - [`C:\Users\<User>\AppData\Roaming\sampctl`] on Windows
    - Possibly [`~/.sampctl`] on linux

# Runtime prerrequisites
## Linux
If you're planning to run the server on a Linux machine, keep in mind that omp-server is still a 32bit process as of now.

You may need to install the i386 architecture and install the 32bit version of the C++ Standard Library runtime, the installation procedure may vary depending on your distro:

If your package manager is APT (Debian, Ubuntu, etc), you can achieve this by running:

```bash
dpkg --add-architecture i386 && apt-get update && apt-get install libstdc++6:i386
```

If your package manager is pacman (Arch Linux), you can achieve this by running:

```bash
pacman -Syu lib32-gcc-libs
```

If you're unsure, research how to do this on your machine!

## Windows
If you're planning to run the server on a Windows machine, you **may or may not** need to install the [MVSC runtimes.](https://www.techpowerup.com/download/visual-c-redistributable-runtime-package-all-in-one/)

# How to build

Clone the project or download the project in a zip archive:

```bash
git clone https://github.com/ZantetsukenGT/AttDef attdef
#linux
cd ./attdef
#windows
cd .\attdef
```

Fetch the needed libraries/dependencies, the following command will fetch plugins as well:

```bash
sampctl ensure
```

Compile the gamemode to generate the attdef.amx file needed to run the server:

```bash
#Will build with debug symbols -d3 flag (debug symbols included, development and for crashdetect to output useful info)
sampctl build
#or
sampctl build dev
```

```bash
#Will build with optimizations and no debug symbols, mainly for release builds
sampctl build release
```

# Just before running the server

## Delete server.cfg

Since we are using open.mp, you need to delete the `server.cfg` file and run the following command to generate a `config.json` file:

```bash
#linux
./samp03svr --default-config

#windows
.\samp-server.exe --default-config
```

## Plugins and components

In the `plugins/` folder:

1. Delete the `streamer` plugin, its unused.
2. Delete the `SKY` plugin, having it present will prevent the gamemode from working at all.
3. Move `pawnraket` and `sscanf` to the `components/` folder.

## Scriptfiles

In the `scriptfiles/` folder:

1. Make a copy of the `AttDefDatabase.db.example` file and rename it to `AttDefDatabase.db` or the server won't start properly.

## config.json

In the `config.json` file:

1. In the `"pawn"."legacy_plugins"` array, add `"samp_bcrypt"` if you're in windows or `"samp_bcrypt"` if you're in linux.
2. In the `"pawn"."main_scripts"` array, remove `"test 1"` and add `"attdef"`.
3. In the `"rcon"."password"` property, change it from the default `changeme`.

It is recommended to use the `config.json` customizations from the [latest release](https://github.com/ZantetsukenGT/AttDef/releases/latest) 

# Actually running the server
Use your preferred way to start the server:

```bash
#On Windows
.\omp-server.exe

#On Linux
./omp-server
```

This works fine until you need to log off, on Windows, the process will stay alive as long as the machine is turned on and in Linux the process will be terminated.

## Setting up the server to automatically start

So, on Linux, using [`pm2`](https://pm2.io/) is recommended, it will help you in restarting the server upon crashes and start it automatically when you reboot your machine.

Just casually follow these steps:

1. Install [nvm](https://github.com/nvm-sh/nvm)
```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.3/install.sh | bash
```

2. Log off and log in again to complete the nvm installation

3. Install the latest version of NodeJS

```bash
nvm install node # "node" is an alias for the latest version
nvm use node
```

4. Install pm2
```bash
npm install pm2 -g
```

5. Tell pm2 to run on boot
```bash
#Run as root or use sudo
pm2 startup
```

6. Start your server with pm2
```bash
# very important to be inside the correct folder
cd path/to/server
pm2 start "./omp-server" --name myAttdef
pm2 save
```

You're done!

Other useful pm2 commands:

```bash
pm2 list
pm2 log myAttdef
pm2 stop myAttdef
pm2 restart myAttdef
pm2 delete myAttdef
pm2 describe myAttdef
```

## Collaboration

This project is open for collaboration, create a fork, start from [How to build](#how-to-build) and make a pull request!
