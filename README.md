# AttDef

[![sampctl](https://img.shields.io/badge/sampctl-AttDef-2f2f2f.svg?style=for-the-badge)](https://github.com/ZantetsukenGT/AttDef)

<!--
* Follow [Semantic Versioning](https://semver.org/)
-->

## Installation for development

Clone the project or download the project in a zip archive:

```bash
git clone https://github.com/ZantetsukenGT/AttDef
#linux
cd ./AttDef
#windows
cd .\AttDef
```

Modify the pawn.json file whether you need a 0.3.7 R2 server, a 0.3DL or an UGMP server.

Fetch the needed libraries/dependencies, make sure you have [sampctl](https://github.com/Southclaws/sampctl) installed (will fetch plugins as well):

```bash
#you can abbreviate 'package' as 'p'
sampctl package ensure
```

## Build

Will generate the attdef.amx file needed to run the server:

```bash
#Will build with debug symbols -d3 flag (debug symbols included, development and for crashdetect to output useful info)
sampctl package build
#or
sampctl package build dev
```

```bash
#Will build with optimizations and no debug symbols -o2 flag
sampctl package build main
```

## Usage

To start the server:

```bash
sampctl p run
```

Then use your preferred way to keep the server alive on server logout, 'screen' for linux is recommended:

```bash
#linux start, will persist over logouts
screen -S mySampScreen sampctl p run

#dettach from the server output with CTRL + A, and then press D 

#linux cmd to return to the mySampScreen screen
screen -R mySampScreen
#you can kill it with CTRL + C

#windows
sampctl p run
```

You can also start it the old way

```bash
#linux start, will persist over logouts
screen -S mySampScreen ./samp03svr

#dettach from the server output with CTRL + A, and then press D 

#linux cmd to return to the mySampScreen screen
screen -R mySampScreen
#you can kill it with CTRL + C

#windows
.\samp-server.exe
```


## Collaboration and Pull Requests

This project is open for collaboration, following a few guidelines:

1. Your proposed changes must compile without any warnings, const correctness warnings caused by dependencies ensured by sampctl are fine, warnings caused by YSI includes are fine, warnings caused by legacy dependencies (basically your code) are not.
2. Before making your pull request, delete the dependencies folder and run `sampctl p ensure` and `sampctl p build` and check for further warnings and functionality remains as intended.
3. Your code *preferably* has to be formatted through [vscode](https://code.visualstudio.com/)'s `xaver.clang-format` extension, it will use the formatting rules present in the `.clang-format` file, and applying the actual formatting with `Alt + Shift + F`, for the formatting to work you need to set the file language specify in the extension's settings the path of the `clang-format.exe` file bundled in [the clang C++ compiler](https://github.com/brechtsanders/winlibs_mingw/releases/download/11.2.0-14.0.0-9.0.0-ucrt-r7/winlibs-x86_64-posix-seh-gcc-11.2.0-llvm-14.0.0-mingw-w64ucrt-9.0.0-r7.7z); obtained from [https://winlibs.com/](https://winlibs.com/) (Win64, UCRT runtime), all of this will help to keep a consistent code style throughout the project.
3.1. Due to the pawn compiler's limitations, after formatting, some adjustments need to be made manually or you will find cryptic and useless compiler errors.
3.2. String literals need to be modified into 1-liners
3.3. Pawn Tags cannot have a space between the `Tag` and the `:`, example: (Tag: good, Tag : bad)
3.4. the formatter adds a NewLine character after the keyword `public`, remove it so that the keyword and the function name is in the same line. 
