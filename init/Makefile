mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(dir $(mkfile_path))

build: main.c
	gcc --static $< -o $(mkfile_dir)../builds/init/init
