#!/bin/bash

function build() {
	local time=$(date +%s)

	mkdir -p objects

	local files=$(ls src/*.cpp)
	local file_count=$(ls src/*.cpp | wc -l)

	local file_index=1
	for file in $files; do
		echo -en "\033[1;31m Compiling: \033[31;0m$file"
		echo -e "\033[1;33m [$file_index/$file_count]" 

		g++ -c $file -o objects/$(basename $file .cpp).o -Iinclude/

		file_index=$((file_index + 1))
	done
	echo -en "\033[31;0m"

	echo -e "\033[1;33m Linking...\033[31;0m"

	g++ objects/*.o -o alang.compiler -std=c++23

	echo -e "Done in $(($(date +%s)-$time)) seconds."
}

for callback in $@; do
	$callback
done
