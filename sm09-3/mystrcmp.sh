#!/bin/bash

function myrun {
	cmd="./mystrcmp_tb $1 $2"
	echo -e "$cmd: \t $(bash -c "$cmd")"
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
#myrun ' ' 'aaa'
#myrun aaa ''
#myrun '' ''
myrun aaa aaab
myrun aaa aaac
myrun aaab aaa
myrun aaac aaa
