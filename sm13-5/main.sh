#!/bin/bash

if [ -x ./main ]
then
	./main
	./main 77 3 77 88 99 0 88 0764 06
	./main 77 4 66 77 88 99 0 88 0764 06
	./main 77 3 77 88 99 0 88 0764 0
else
	echo task.uid task.gid_count task.gids[] stb.st_uid stb.st_gid stb.st_mode access
	echo "run make"
fi
