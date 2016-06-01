/*
 * ==================================================================
 *    This file has been automatically generated, do not modified
 * ==================================================================
 */

#include <stdio.h>
#include <rtems.h>
#include "gcov_public.h"

extern void __real_Init(void *ignored);

//void __wrap_Init(void *ignored)

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


