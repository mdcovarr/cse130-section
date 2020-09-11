"""
    Test script used to check example .c files in the example/ directory
"""
import os
import glob
from subprocess import check_call, check_output
import subprocess

CWD = os.path.dirname(os.path.realpath(__file__))
TEST_DIR  = 'tests'
CAT_OUT = 'cat-out.txt'
DOG_OUT = 'dog-out.txt'
DOG_BINARY = 'dog'


def get_test_files(test_dir):
    """
    Function used to get all test .c scripts
    :param test_dir: directory to get all .c files
    :return test_files: list of test files
    """
    test_files = glob.glob(test_dir, recursive=True)

    return test_files


def run_dog(filename):
    """
    Funcion used to run dog executable with an argument
    :param filename: the text or binary file we are reading
    :return status: exit status
    """
    command = './{0} {1} > {2}'.format(DOG_BINARY, filename, DOG_OUT)
    try:
        status = check_call(command, shell=True)
    except subprocess.CalledProcessError as e:
        return e.returncode

    return status

def run_cat(filename):
    """
    Funcion used to run cat command with an argument
    :param filename: the text or binary file we are reading
    :return status: exit status
    """
    command = 'cat {0} > {1}'.format(filename, CAT_OUT)
    try:
        status = check_call(command, shell=True)
    except subprocess.CalledProcessError as e:
        return e.returncode

    return status

def check_test():
    """
    Function used to determine if output matches between gcc and basic interpreter
    :param out: output of executable
    :param my_out: output of interpreter
    :return: True if both outputs are the same, False otherwise
    """
    command = 'diff {0} {1} 1>/dev/null'.format(DOG_OUT, CAT_OUT)
    try:
        status = check_call(command, shell=True)
    except subprocess.CalledProcessError as e:
        status = e.returncode

    if status == 0:
        return True
    else:
        return False


def print_red(status):
    """
    Print status string as color red
    :param status: string representation of status
    :return: string in red color
    """
    return "\033[91m {}\033[00m".format(status)


def print_green(status):
    """
    Print status string as color green
    :param status: string representation of status
    :return: string in green color
    """
    return "\033[92m {}\033[00m".format(status)


def handle_tests(file_list):
    """
    Function used to handle executing all test scripts
    :param file_list: list of test .c scripts
    :return None:
    """
    print('\n\n ------------ [ Running Tests ] ------------\n\n')
    i = 0

    for filename in file_list:
        c_output = run_cat(filename)
        my_output = run_dog(filename)

        filename = os.path.basename(filename)
        status = check_test()

        if status:
            exit_status = print_green('[pass]')
        else:
            exit_status = print_red('[fail]')

        print('{0}:\t{1}\t\t\t{2}'.format(i, filename, exit_status))

        i += 1

    os.remove(CAT_OUT)
    os.remove(DOG_OUT)


def main():
    """
        Main execution begins here.
    """
    # need to get all test files
    test_files = get_test_files(os.path.join(CWD, TEST_DIR, '*'))

    handle_tests(test_files)


if __name__ == '__main__':
    main()
