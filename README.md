# Tiny coverage
This is a small source repository to simplify the code coverage tasks on
embedded systems.

#Directory structure

- `gcov`: code coverage library
- `sample/rtems`: sample code for RTEMS operating system
- `gdb`: gdb script to automate the code coverage counters retrieval

#Usage

Let us take the sample code inside `sample/rtems`. This folder contains two
files. One file `bubble.c` that is the software we want to profile and, a
`wrapper.c` that wraps the main function to ensure the code coverage counters
are transmitted back to the host.

In the case of RTEMS, the `main` function is called `Init`. The wrapper method
`__wrap_Init()` wraps that function to ensure `__gcov_exit()` is called when
finished.

```c
extern void __real_Init(void *ignored);

#define real_function   __real_Init

void __wrap_Init(void *ignored)
{

    printf("%s: Coverage initialized\n", __func__);
    /*	call the real funcion	*/
    real_function(ignored);

    /*  send out the coeverage info. after several seconds  */
    __gcov_exit();

    /*  Delete the RTEMS init task  */
    printf("rtems_task_delete\n");
    rtems_task_delete( RTEMS_SELF );

}
```

##Profiling in 3 steps

**First**, we need to compile the source files on which we want to perform the code
coverage. For that we'll include the flags `-ftest-coverage` and
`-fprofile-arcs` to tell GCC to instrument the code.

```
${CROSS-COMPILE}-gcc -qleon2 -c sample/bubble.c -ftest-coverage -fprofile-arcs
```

where `CROSS-COMPILE` is the prefix for your GCC cross compiler (in this case
        would be spar-rtems-)

**Second**, compile the rest of our project and wrap if necessary our application
entry point. In this case the `Init` function.

```
${CROSS-COMPILE}-gcc -g -o bubble bubble.o sample/wrapper.c  gcov/* -Xlinker --wrap -Xlinker Init -I./gcov
```

**Third**, we can use GDB to connect to our embedded hardware and let it receive the
coverage profile information.

The following code is an example of a possible GDB script that could be used.

```
tar extended-remote :10001
load bubble.cov

b base.c:85  # break on coverage_helper_breakme() function
commands 1
    silent
    set $filename = tmp->info->filename
    set $dataBegin = buffer
    set $dataEnd = buffer + sizeInBytes
    eval "dump binary memory %s 0x%lx 0x%lx", $dataBegin, $dataEnd, $filename 
    eval "echo dump binary memory %s 0x%lx 0x%lx", $dataBegin, $dataEnd, $filename 
    echo \n
    c
end
c

```

Now, just use GDB to connect to your target hardware and execute your
application

```
gdb -x gdb/automate_coverage.gdb bubble
```

You should have received .gcda files with the information about the code
coverage that you can now process with `lcov` at will.
