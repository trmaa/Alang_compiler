#!/bin/bash

function build() {
	g++ src/*.cpp -o alang.comp -Iinclude -std=c++23
}

for callback in $@; do
	$callback
done
