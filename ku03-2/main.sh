#!/bin/bash

echo 10 5 |./main
echo 10 2147483600 |./main
echo 10 -2147483600 |./main
echo 120 5 |./main
echo -120 5 |./main
echo 1 100 |./main
echo 1 -100 |./main

