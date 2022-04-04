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

