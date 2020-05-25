#!/bin/bash

function myrun {
#	cmd="./mystrcmp_tb "$1" "$2""
	echo -e ./mystrcmp_tb "$1" "$2"
	echo -ne "\t"; ./mystrcmp_tb "$1" "$2"
}

myrun aaa aaa
myrun aaa aab
myrun aaa aac
myrun aab aaa
myrun aac aaa
myrun aaa aa
myrun aa aaa
myrun aaa baa
myrun aaa caa
myrun baa aaa
myrun caa aaa
myrun aaa aaab
myrun aaa aaac
myrun aaab aaa
myrun aaac aaa
echo
myrun "" ""
myrun "" "a"
myrun "a" ""
