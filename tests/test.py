import subprocess
import sys
import os

def make_dir_list(files, dir_list, path):
    for e in files:
        if not os.path.isfile(os.path.join(path,e)):
            dir_list.append(e)
def get_percentage(a, b):
    perc_str = str( (a/b) * 100)
    perc_str = perc_str[:5]
    return perc_str

def test_command(command, tests, tests_cat, succ_tests, succ_tests_cat, output, return_value, \
        c_categories):
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
                        if not c_categories and not final:
                            print(command[:-1] + ': SUCCESS')
                        succ_tests[0] += 1
                        succ_tests_cat[0] += 1
                   else:
                       if not c_categories and not final:
                            print(command[:-1] + ': FAILURE -> Unexpected error output')
               else:
                   if not c_categories and not final:
                       print(command[:-1] + ': FAILURE -> Unexpected return value')
           else:
               if not c_categories and not final:
                   print(command[:-1] + ': FAILURE -> Unexpected output')
           output[0] = ""
           err_output[0] = ""
           return_value[0] = -1
#OPTIONS
options = sys.argv[1:]
number = False
c_categories = False
e_categories = False
categories = []
final = False
o_all = False

for option in options:
    if e_categories:
        categories.append(option)
    elif option == "-c" or option == "--categories":
        c_categories = True
    elif option == "-e" or option == "--select":
        e_categories = True
    elif option == "-f" or option == "--final":
        final = True
    elif option == "-n" or option == "--number":
        number = True

if categories == []:
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
    if not final:
        print('[' + category + ']')
    #Opening the file in read only
    test_file = open("tests/" + category + "/tests", "r")
    #test_list is the content of test_file line by line
    test_list = test_file.readlines()
    test_file.close()
    for line in test_list:
        if line == "\n": #command to execute?
            test_command(command, tests, tests_cat, succ_tests, succ_tests_cat, output, return_value, \
                    c_categories)
            command = ""
        elif line[:4] == "CMD=":
            command = line[4:]
        elif line[:3] == "RV=":
            return_value[0] = int(line[3:])
        elif line[:3] == "OP=":
            output[0] = line[3:]
        elif line[:4] == "EOP=":
            err_output[0] = line[4:]
    if not final:
        if number:
            print('\n' + category + ' -> Successful tests : '\
                    + str(succ_tests_cat[0]) + '/' + str(tests_cat[0]))
        else:

            print('\n' + category + ' -> Successful tests : '\
                    + get_percentage(succ_tests_cat[0], tests_cat[0]) + '%')
    tests_cat[0] = 0
    succ_tests_cat[0] = 0

if number:
    print('\nGlobal results -> Successful tests : '\
        + str(succ_tests[0]) + '/' + str(tests[0]))
else:

    print('\nGlobal results -> Successful tests : '\
            + get_percentage(succ_tests[0], tests[0]) + '%')
