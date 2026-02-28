set -e

g++ -std=c++17 -Wall -g -o unit_tests unit_tests.cpp linked_list.cpp
./unit_tests

g++ -std=c++17 -Wall -g -o main mainSimple.cpp linked_list.cpp