#!/bin/bash

function myrun {
	echo -e "$1"
	bash -c "$1"
	echo
}

myrun "./main 2 3"
myrun "./main 0xCAFEBABE 0xDEADBEEF"
myrun "./main"
myrun "./main 0xCAFEBABECAFEBABE 0xDEADBEEFDEADBEEF"
myrun "./main 0x10000000000 0x10000000000"
