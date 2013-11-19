import subprocess, sys, os, time, signal, datetime

def timeout_test(cmd, timeout):
    start_time = datetime.datetime.now()
    try:
        process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if process.returncode:
            return False
        while process.poll() is None:
            time.sleep(0.1)
            current_time = datetime.datetime.now()
            if (current_time - start_time).seconds > timeout:
                os.kill(process.pid, signal.SIGKILL)
                os.waitpid(-1, os.WNOHANG)
                return False
        return True
    except subprocess.CalledProcessError:
        return False

def make_dir_list(files, dir_list, path):
    for e in files:
        if not os.path.isfile(os.path.join(path,e)):
            dir_list.append(e)
def get_percentage(a, b):
    perc_str = str( (float(a)/float(b)) * 100)
    perc_str = perc_str[:5]
    return perc_str

def test_command(command, tests, tests_cat, succ_tests, succ_tests_cat, output, return_value, \
        c_categories, err_out):
    if command != "":
        tests[0] += 1
        tests_cat[0] += 1
        cmd = command.split()
        cmd.insert(0, './42sh') #getting from 'cmd' to './42sh cmd'
        try:
               if timeout < 0 or timeout_test(cmd, timeout):
                    # if no ouput specified or if it matches
                    if (output[0] == "" or \
                            subprocess.check_output(cmd, stderr=subprocess.PIPE) == output[0]):
                        # if the return value matches the expected one (0 by default)
                        if (subprocess.call(cmd,stdout=subprocess.PIPE, \
                              stderr=subprocess.PIPE) == return_value[0]):
                            if (err_out[0] == "" or subprocess.call(cmd,stdout=subprocess.PIPE, \
                                       stderr=subprocess.STDOUT) == err_output):
                                if not c_categories and not final:
                                    print(command[:-1] + ': \033[1;32mSUCCESS\033[1;m')
                                succ_tests[0] += 1
                                succ_tests_cat[0] += 1
                            else:
                                if not c_categories and not final:
                                    print(command[:-1] + \
                                            ': F\033[1;31mFAILURE -> Unexpected error output\033[1;m')

                        else:
                            if not c_categories and not final:
                                print(command[:-1] + \
                                        ': \033[1;31mFAILURE -> Unexpected return value\033[1;m')
                    else:
                        if not c_categories and not final:
                            print(command[:-1] + \
                                    ': \033[1;31mFAILURE -> Unexpected output\033[1;m')
               else:
                    if not c_categories and not final:
                         print(command[:-1] + \
                                ': \033[1;31mFAILURE -> Timeout\033[1;m')
        except subprocess.CalledProcessError as error:
            if error.returncode == return_value:
                if not c_categories and not final:
                    print(command[:-1] + ': \033[1;32mSUCCESS\033[1;m')
                    succ_tests[0] += 1
                    succ_tests_cat[0] += 1
            else:
                if not c_categories and not final:
                    print(command[:-1] + \
                        ': \033[1;31mFAILURE -> Unexpected return value\033[1;m')
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
timeout = -1

for option in options:
    if option == "-c" or option == "--categories":
        c_categories = True
        e_categories = False
    elif option == "-e" or option == "--select":
        e_categories = True
    elif option == "-f" or option == "--final":
        final = True
        e_categories = False
    elif option == "-n" or option == "--number":
        number = True
        e_categories = False
    elif option == "-t" or option == "--time":
        timeout = -2
    elif timeout == -2:
        timeout = float(option)
    elif e_categories:
        categories.append(option)

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

test_files = []

for category in categories:
    if not final and not c_categories:
        print('\n\033[1;34m[' + category + ']\033[1;m')
    test_files = os.listdir("tests/" + category)
    for p_test_file in test_files:
        if p_test_file[:4] == "test":
            #Opening the file in read only
            test_file = open("tests/" + category + "/" + p_test_file)
            #test_list is the content of test_file line by line
            test_list = test_file.readlines()
            test_file.close()
            for line in test_list:
                if line == "\n": #command to execute?
                    test_command(command, tests, tests_cat, succ_tests, \
                            succ_tests_cat, output, return_value, c_categories, err_output)
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
            print('\033[1;34m' + category + ' -> Successful tests : '\
                    + str(succ_tests_cat[0]) + '/' + str(tests_cat[0]) + '\033[1;m')
        else:

            print('\033[1;34m' + category + ' -> Successful tests : '\
                    + get_percentage(succ_tests_cat[0], tests_cat[0]) + '%\033[1;m')
    tests_cat[0] = 0
    succ_tests_cat[0] = 0
if number:
    print('\033[1;44m\nGlobal results -> Successful tests : '\
        + str(succ_tests[0]) + '/' + str(tests[0]) + '\033[1;m')
else:
    print('\033[1;44m\nGlobal results -> Successful tests : '\
            + get_percentage(succ_tests[0], tests[0]) + '%\033[1;m')
