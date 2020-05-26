#!/bin/bash

./main "/////a//////////b/v/d/sad/we"
./main " //a /"
cat text.txt |xargs -n 1 ./main

