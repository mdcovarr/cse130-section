# Week-2 Section :)
Creating scripts to show examples of how to utilize
differnt functions and system calls in C

## Example Scripts
```bash
cse130-section/week-2/open-demo.c
cse130-section/week-2/read-demo.c
cse130-section/week-2/write-demo.c
```

## Build
I created a Makefile to make it easy to build either of the example scripts

`open-demo.c, read-demo.c, wirte-demo.c`

In order to build either of these scripts you will need to modify the
`TARGET` variable in the `Makefile`

For Example if you want to compile `open-demo.c`
you need to make sure that in `Makefile` you have the following
configuration:
```bash
TARGET = open-demo
```

For Example if you want to compile `write-demo.c`
you need to make sure that in `Makefile` you have the following
configuration:
```bash
TARGET = write-demo
```

## Help
If you need help with modification what target's have been implemented
you can reference the `help` documentation for the `Makefile` by running
command:
```bash
make help
```