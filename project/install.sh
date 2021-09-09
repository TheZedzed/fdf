#!/bin/sh
cd fdf
echo "make fclean..."
make fclean
echo "make bonus 2 times...."
make bonus
make bonus
valgrind ./fdf test_maps/t2.fdf
