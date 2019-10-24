# Pushover

gcc -Wall pushover.c -o pushover.out

valgrind --tool=memcheck --leak-check= full ./pushover.out