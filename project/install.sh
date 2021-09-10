#!/bin/sh
cd fdf
make fclean
make bonus
valgrind ./fdf test_maps/t2.fdf
