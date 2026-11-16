#!/bin/bash

devDirectory="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

compilerDirectory="$devDirectory/compiler-v3.10.11/linux"
runtimeDirectory=$(readlink -f "$devDirectory/../runtime_linux")
amxOutputDirectory="$runtimeDirectory/gamemodes"

cd $compilerDirectory

./pawncc \
	$devDirectory/gamemodes/attdef.pwn \
	-D$devDirectory/gamemodes \
	-o$amxOutputDirectory/attdef.amx \
	-d3 \
	-O1 \
	-\;+ \
	-\(+ \
	-\\+ \
	-Z+ \
	-i$devDirectory/legacy \
	-i$devDirectory/modules \
	-i$devDirectory \
	-i$devDirectory/dependencies/omp-stdlib \
	-i$devDirectory/dependencies/samp-stdlib \
	-i$devDirectory/dependencies/pawn-stdlib \
	-i$devDirectory/dependencies/Pawn.RakNet/src \
	-i$devDirectory/dependencies/YSI-Includes \
	-i$devDirectory/dependencies/md-sort \
	-i$devDirectory/dependencies/code-parse.inc \
	-i$devDirectory/dependencies/indirection \
	-i$devDirectory/dependencies/amx_assembly \
	-i$devDirectory/dependencies/samp-bcrypt/include \
	-i$devDirectory/dependencies/gBugFix \
	-i$devDirectory/dependencies/MapFix \
	-i$devDirectory/dependencies/progress2 \
	-i$devDirectory/dependencies/samp-dyn-dialog-pages \
	-i$devDirectory/dependencies/samp-geoip \
	-i$devDirectory/dependencies/samp-weapon-config \
	-i$devDirectory/dependencies/sscanf


echo ""
echo "======================="
echo ""
echo "Compile script finished: check the '$amxOutputDirectory' folder."
echo "The next step is to start the server: '$runtimeDirectory/omp-server'"
