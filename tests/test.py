import subprocess
import sys
#Opening the file in read only
test_file = open("tests/tests", "r")
#test_list is the content of test_file line by line
test_list = test_file.readlines()

#Variables used during test with test category, command to execute,
#expected output and expected return value
succ_tests = 0
tests = 0
category = "" 
command = ""
output = ""
return_value = -1

for line in test_list:
    
    if line == "\n": #command to execute?
        if command != "":
           tests += 1
           cmd = command.split()
           cmd.insert(0, './42sh') #getting from 'cmd' to './42sh cmd'
           # if no ouput specified or if it matches
           if (output == "" or subprocess.check_output(cmd) == output):
               # if the return value matches the expected one (0 by default) 
               if (subprocess.call(cmd,stdout=subprocess.PIPE, \
                        stderr=subprocess.PIPE) == return_value):
                   print(command[:-1] + ': SUCCESS')
                   succ_tests += 1
               else:
                   print(command[:-1] + ': FAILURE -> Unexpected return value')
           else:
               print(command[:-1] + ': FAILURE -> Unexpected output')
           command = ""
           output = ""
           return_value = -1

    elif line[:4] == "CMD=":
        command = line[4:]
    elif line[:3] == "RV=":
        return_value = int(line[3:])
    elif line[:3] == "OP=":
        output = line[3:]
    elif line[:4] == "CAT=":
        if category != "":
            print(category + ' -> Successful tests : ' + str(succ_tests) +\
                    '/' + str(tests))
        category = line[4:-1]
        tests = 0
        succ_tests = 0

if category != "":
    print(category + '-> Successful tests : ' + str(succ_tests) + '/' + str(tests))
test_file.close()
