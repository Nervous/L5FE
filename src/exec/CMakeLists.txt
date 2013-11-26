set(exec_source_files
    exec.h
    variable.h
    function.h
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
    function.c
    exec_funcdec.c
    exec_pipe.c
    exec_builtin.c
    exec_expand.c
)

add_library(exec ${exec_source_files})
