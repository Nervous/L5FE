set(exec_source_files
    exec.h
    exec_andor.c
    exec_command.c
    exec_compound.c
    exec_dogroup.c
    exec_fork.c
    exec_if.c
    exec_input.c
    exec_list.c
    exec_pipeline.c
    exec_redir.c
    exec_simplecommand.c
    exec_shellcommand.c
    exec_until.c
    exec_while.c
    variable.c
    variable.h
    exec_funcdec.c
)

add_library(exec ${exec_source_files})
