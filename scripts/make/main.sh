#!/bin/bash

function build() {
	#simple for now
	g++ src/*.cpp -o alang.compiler -Iinclude -std=c++23
}

for callback in $@; do
	$callback
done
