import subprocess
import sys
import os

def make_dir_list(files, dir_list, path):
    for e in files:
        if not os.path.isfile(os.path.join(path,e)):
            dir_list.append(e)

def test_command(command, tests, tests_cat, succ_tests, succ_tests_cat, output, return_value):
 if command != "":
           tests[0] += 1
           tests_cat[0] += 1
           cmd = command.split()
           cmd.insert(0, './42sh') #getting from 'cmd' to './42sh cmd'
           # if no ouput specified or if it matches
           if (output[0] == "" or subprocess.check_output(cmd) == output[0]):
               # if the return value matches the expected one (0 by default) 
               if (subprocess.call(cmd,stdout=subprocess.PIPE, \
                        stderr=subprocess.PIPE) == return_value[0]):
                   if (err_out == "" or subprocess.call(cmd,stdout=subprocess.PIPE, \
                           stderr=subprocess.STDOUT) == err_output):
                        print(command[:-1] + ': SUCCESS')
                        succ_tests[0] += 1
                        succ_tests_cat[0] += 1
                   else:
                       print(command[:-1] + ': FAILURE -> Unexpected error output')
               else:
                   print(command[:-1] + ': FAILURE -> Unexpected return value')
           else:
               print(command[:-1] + ': FAILURE -> Unexpected output')
           output[0] = ""
           err_output[0] = ""
           return_value[0] = -1

#Variables used during test with test category, command to execute,
#expected output and expected return value
categories = []
files = os.listdir('tests')
#extracting directories from files list
make_dir_list(files, categories, 'tests')
succ_tests = [0]
succ_tests_cat = [0]
tests = [0]
tests_cat = [0]
 
command = ""
output = [""]
err_output = [""]
return_value = [-1]

for category in categories:
    print('[' + category + ']')
    #Opening the file in read only
    test_file = open("tests/" + category + "/tests", "r")
    #test_list is the content of test_file line by line
    test_list = test_file.readlines()
    test_file.close()
    for line in test_list:
        if line == "\n": #command to execute?
            test_command(command, tests, tests_cat, succ_tests, succ_tests_cat, output, return_value)
            command = ""
        elif line[:4] == "CMD=":
            command = line[4:]
        elif line[:3] == "RV=":
            return_value[0] = int(line[3:])
        elif line[:3] == "OP=":
            output[0] = line[3:]
        elif line[:4] == "EOP=":
            err_output[0] = line[4:]

    print('\n' + category + ' -> Successful tests : '\
            + str(succ_tests_cat[0]) + '/' + str(tests_cat[0]))
    tests_cat[0] = 0
    succ_tests_cat[0] = 0

print('\nGlobal results -> Successful tests : '\
        + str(succ_tests[0]) + '/' + str(tests[0]))
