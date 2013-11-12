import subprocess

#Opening the file in read only
test_file = open("tests", "r")
#test_list is the content of test_file line by line
test_list = test_file.readlines()

#Variables used during test with test category, command to execute,
#expected output and expected return value
category = "" 
command = ""
output = ""
return_value = -1

for line in test_list:
    if line != "\n":
        print(line)

#Calls "echo test" in the shell
subprocess.call(["echo", "test"])
# if "echo test" output is equal to "test\n", prints True 
if "test\n" == subprocess.check_output(["echo", "test"]):
    print(True)
else:
    print(False)

test_file.close()
