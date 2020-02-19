# Pushover

This program is written in C on Linux OS. For more info, read projetTutore_2015_2016.pdf

## Compile the program

```sh
make
```

## Verify if data is correcly been free

```sh
valgrind --tool=memcheck --leak-check= full ./PushOver
```
