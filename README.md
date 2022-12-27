# AttDef

[![sampctl](https://img.shields.io/badge/sampctl-AttDef-2f2f2f.svg?style=for-the-badge)](https://github.com/ZantetsukenGT/AttDef)

<!--
* Follow [Semantic Versioning](https://semver.org/)
-->

## Installation FOR DEVELOPMENT OR CONTRIBUTIONS. Otherwise you're looking for the [latest release.](https://github.com/ZantetsukenGT/AttDef/releases/latest)

Clone the project or download the project in a zip archive:

```bash
git clone https://github.com/ZantetsukenGT/AttDef attdef
#linux
cd ./attdef
#windows
cd .\attdef
```

Modify the pawn.json file whether you need an `open.mp`, `0.3.7 R2`, `0.3DL` or an `UGMP` server. `open.mp` is recommended and is the default.

Fetch the needed libraries/dependencies, make sure you have [sampctl version 1.11.0 installed, manual installation recommended](https://github.com/Southclaws/sampctl/wiki/Windows#installing-manually) (the following cmd will fetch plugins as well):

```bash
sampctl ensure
```

### If using open.mp

You need to delete `server.cfg` and run the following command to generate a `config.json` file:

```bash
#linux
./samp03svr --default-config

#windows
.\samp-server.exe --default-config
```

Then in the `plugins/` folder:

1. Delete the `streamer` plugin, its unused.
2. Move `pawnraket` and `sscanf` to the `components/` folder.

Then in the `scriptfiles/` folder:

1. Make a copy of the `AttDefDatabase.db.example` file and rename it to `AttDefDatabase.db` or the server won't start properly.

Then in the `config.json` file:

1. In the `"pawn"."legacy_plugins"` array, add `"samp_bcrypt"` if you're in windows or `"samp_bcrypt.so"` if you're in linux.
2. In the `"pawn"."main_scripts"` array, remove `"test 1"` and add `"attdef"`.
3. In the `"rcon"."password"` property, change it from the default `changeme`.

## Build

Will generate the attdef.amx file needed to run the server:

```bash
#Will build with debug symbols -d3 flag (debug symbols included, development and for crashdetect to output useful info)
sampctl build
#or
sampctl build main
```

```bash
#Will build with optimizations and no debug symbols, mainly for release builds
sampctl build release
```

## Usage

Then use your preferred way to start the server and keep it alive on user logout, 'screen' for linux is recommended.

You can also start it the old way:

```bash
#linux start, will persist over logouts
screen -S mySampScreen ./samp03svr

#dettach from the server output with CTRL + A, and then press D 

#later that day...
#linux cmd to return to the mySampScreen screen
screen -R mySampScreen
#you can kill it with CTRL + C

#windows
.\samp-server.exe
```


## Collaboration and Pull Requests

This project is open for collaboration, following a few guidelines:

1. Your proposed changes must compile without any warnings, const correctness warnings caused by dependencies ensured by sampctl are fine, warnings caused by YSI includes are fine, warnings caused by legacy dependencies (basically your code) are not.
2. Before making your pull request, delete the dependencies folder and run `sampctl ensure` and `sampctl build` and check for further warnings and functionality remains as intended.
3. Your code *preferably* has to be formatted through [vscode](https://code.visualstudio.com/)'s `xaver.clang-format` extension, it will use the formatting rules present in the `.clang-format` file, and applying the actual formatting with `Alt + Shift + F`, for the formatting to work you need to set the file language specify in the extension's settings the path of the `clang-format.exe` file bundled in [the clang C++ compiler](https://github.com/brechtsanders/winlibs_mingw/releases/download/12.2.0-14.0.6-10.0.0-ucrt-r2/winlibs-x86_64-posix-seh-gcc-12.2.0-llvm-14.0.6-mingw-w64ucrt-10.0.0-r2.7z); obtained from [https://winlibs.com/](https://winlibs.com/) (Win64, UCRT runtime), all of this will help to keep a consistent code style throughout the project.
4. Due to the pawn compiler's limitations, after formatting, some adjustments need to be made manually or you will find cryptic and useless compiler errors.
5. String literals need to be modified into 1-liners.
6. Pawn Tags cannot have a space between the `Tag` and the `:`, example: (Tag: good, Tag : bad).
7. The formatter adds a NewLine character after the keyword `public`, remove it so that the keyword and the function name is in the same line.
8. Macros which make use of `%0` or any number really, will be separated as `% 0` and need to be joined again.
