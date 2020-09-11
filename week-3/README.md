## Week-3 Section
This week I showed you how to utilize a python to develope a script
in order to automate your testing process. In this directory there is a
`test.py` script that will test your `dog` implementation against the
`cat` command

## Requirements
```bash
python >= 3
```

## Testing (Python)
In order to utilize the test script you need to make sure that you include a
`dog` executable in this directory, thus there should be a `dog` script in
path:
```bash
cse130-section/week-3/dog
```

If you meet this requirement you can run the following to run tests:
```bash
python3 test.py
```

This will test the output of your executable agains the output of `cat`
for every file in the directory:
```bash
cse130-section/week-3/tests
```

Example output:
```bash
mdcovarr@cse130student:~/cse130-section/week-3$ ls
dog  Makefile  README.md  test.py  tests
mdcovarr@cse130student:~/cse130-section/week-3$ python3 test.py


 ------------ [ Running Tests ] ------------


0:      book.txt                         [pass]
1:      test.txt                         [pass]
2:      random.txt                       [pass]
3:      permissions.txt                  [pass]
mdcovarr@cse130student:~/cse130-section/week-3$
```

## Testing (Bash)
In order to utilzie the **test.sh** bash script you need to make sure
that you have a `dog` executable in the same directory.
You can add more tests as well by following the same paradigm of current
tests in the scripts. Test script can be ran with command:
```
./test.sh --all
```

For help on how to utilize the **test.sh** script, run
```
./test.sh --help
```

Sample Output
```
mdcovarr@cse130student:~/cse130-section/week-3$ ./test.sh --help


Usage: test.sh [arguments]

test.sh - Script used to run a variety of tests to test dog executable
Optional Arguments:

        -h, --help
                Display this help menu
        one
                Runs one test function
        two
                Runs two test function
        three
                Runs three test function
        -a, --all
                Runs all test functions
```

## Adding a new test file
Just add new text or binary file to the directory `tests` and the
`test.py` script will include the file in its list of tests when
comparing the output of your script and `cat`

## Useful Command Examples
#### scp (secure copy)
If you want to copy a file from your host to your Ubuntu VM
you can utilize **scp** command. The following command copies
file **FILE.txt** to the home directory username **USERNAME**
```
scp -P PORT FILE.txt USERNAME@IP:~/
```

Example:
```
scp -p 2100 DESIGN.pdf mdcovarr@127.0.0.1:~/ 
```

#### ssh-copy-id
If you want to use local keys available to authorize login to a
remote machine, in our case, remote connection to the Ubuntu VM
```
ssh-copy-id -P PORT USERNAME@IP
```

Example:
```
ssh-copy-id -P 2100 mdcovarr@127.0.0.1
```

Thus, next time you **ssh** into your VM you wont need to
enter your password :)

#### dd
Can be utilized to create binary files for testing
```
dd if=/dev/urandom of=NEW_BINARY_FILE bs=1024 count=10
```
this outputs a binary file to **NEW_BINARY_FILE** of size
1024 * 10 bytes
