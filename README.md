# Pushover

## Compile the program
```sh
gcc -Wall pushover.c -o pushover.out
```
## Verify if data is correcly been free
```sh
valgrind --tool=memcheck --leak-check= full ./pushover.out
```
