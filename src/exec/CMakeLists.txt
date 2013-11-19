set(exec_source_files
    exec.h
    variable.h
    exec_andor.c
    exec_command.c
    exec_compound.c
    exec_dogroup.c
    exec_fork.c
    exec_if.c
    exec_input.c
    exec_list.c
    exec_pipeline.c
    exec_simplecommand.c
    exec_shellcommand.c
    exec_until.c
    exec_while.c
    exec_for.c
    exec_case.c
    variable.c
    exec_funcdec.c
    exec_pipe.c
)

add_library(exec ${exec_source_files})
