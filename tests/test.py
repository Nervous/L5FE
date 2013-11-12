import subprocess

#Opening the file in read only
test_file = open("tests", "r")
#test_list is the content of test_file line by line
test_list = test_file.readlines()

for line in test_list:
    print(line)

#Calls "echo test" in the shell
subprocess.call(["echo", "test"])
# if "echo test" 
if "test\n" == subprocess.check_output(["echo", "test"]):
    print(True)
else:
    print(False)

test_file.close()
