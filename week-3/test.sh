#!/usr/bin/env bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

usage() {
    echo -e "\n\nUsage: test.sh [arguments] \n"
    echo -e "test.sh - Script used to run a variety of tests to test dog executable"

    echo -e "Optional Arguments:\n"
    echo -e "\t-h, --help\t\t\t"
    echo -e "\t\tDisplay this help menu"

    echo -e "\tone"
    echo -e "\t\tRuns one test function"

    echo -e "\ttwo"
    echo -e "\t\tRuns two test function"

    echo -e "\tthree"
    echo -e "\t\tRuns three test function"

    echo -e "\t-a, --all"
    echo -e "\t\tRuns all test functions"
}

check_test() {
    RET_VAL=$?
    TEST=$1

    if [[ $RET_VAL -eq 0 ]];then
        echo -e "${TEST}\t\t${GREEN}PASS${NC}"
    else
        echo -e "${TEST}\t\t${RED}FAIL${NC}"
    fi
}

test_one() {
    cat tests/file.txt > out.cat
    ./dog tests/file.txt > out.dog
    diff out.cat out.dog

    check_test "test_one"
}

test_two() {
    cat tests/file.txt - < tests/file2.bin > out.cat
    ./dog - tests/file.txt < tests/file2.bin > out.dog
    diff out.cat out.dog

    check_test "test_two"
}

test_three() {
    # Step 1: run cat and output to a file
    cat tests/zero.bin > out.cat
    # Step 2: run dog and output to a file
    ./dog tests/zero.bin > out.dog
    # check to see if dog output differs from cat
    diff out.cat out.dog

    # determine if test passed or failed
    check_test "test_three"
}


while [ "$1" != "" ]; do
    case $1 in
        one)
            test_one
            ;;
        two)
            test_two
            ;;
        three)
            test_three
            ;;
        -a | --all)
            test_one
            test_two
            test_three
            ;;
        -h | --help)
            usage
            exit
            ;;
        *)
            usage
            exit 1
    esac
    shift
done
