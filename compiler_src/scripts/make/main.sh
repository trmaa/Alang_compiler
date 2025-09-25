#!/bin/bash

function build() {
	local time=$(date +%s)

	mkdir -p compiler_build/objects

	local files=$(ls compiler_src/src/*.cpp)
	local file_count=$(ls compiler_src/src/*.cpp | wc -l)

	local file_index=1
	for file in $files; do
		echo -en "\033[1;31m Compiling: \033[31;0m$(basename $file)"
		echo -e "\033[1;33m [$file_index/$file_count]" 

		g++ -c $file -o compiler_build/objects/$(basename $file .cpp).o -Icompiler_src/include/

		file_index=$((file_index + 1))
	done
	echo -en "\033[31;0m"

	echo -e "\033[1;33m Linking...\033[31;0m"

	g++ compiler_build/objects/*.o -o compiler_build/alang.compiler -std=c++23

	echo -e "Done in $(($(date +%s)-$time)) seconds."
}

for callback in $@; do
	$callback
done
