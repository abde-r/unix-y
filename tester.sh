#!/bin/bash

echo "Timing ls -lR:"
for i in {1..5}; do
    time ls -lR
    echo ""
done

echo "Timing your program:"
for i in {1..5}; do
    time ./ft_ls -lR
    echo ""
done
