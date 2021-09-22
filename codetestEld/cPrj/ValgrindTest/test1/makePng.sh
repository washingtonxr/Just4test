#!/bin/bash
python ~/Documents/SSD_dir/GithubResources/gprof2dot/gprof2dot.py -f callgrind -n10 -s cachegrind.out.53213 > valgrind.dot
dot -Tpng valgrind.dot -o valgrind.png
