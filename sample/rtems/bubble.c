/**
 *  \file   bubble.c
 *  \brief  This file implements the BUBBLE search algorithm for RTEMS
 *
 *  Detailed description starts here.
 *
 *  \author  Aitor Viana Sanchez (avs), Aitor.Viana.Sanchez@esa.int
 *
 *  \internal
 *    Created:  12/03/09
 *   Revision:  $Id: bubble.c 1.4 12/03/09 avs Exp $
 *   Compiler:  gcc/g++
 *    Company:  European Space Agency (ESA-ESTEC)
 *  Copyright:  Copyright (c) 2009, Aitor Viana Sanchez
 *
 *  This source code is released for free distribution under the terms of the
 *  GNU General Public License as published by the Free Software Foundation.
 * =====================================================================================
 */

/*-----------------------------------------------------------------------------
 *  RTEMS configuration
 *-----------------------------------------------------------------------------*/
#include <rtems.h>

/*  Forward declaration */
rtems_task Init(rtems_task_argument ignored);

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MICROSECONDS_PER_TICK 1000
#define CONFIGURE_MAXIMUM_TASKS     10

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_HAS_OWN_INIT_TASK_TABLE


#define CONFIGURE_INIT_TASK_NAME            rtems_build_name( 'U', 'I', '1', ' ' )
#define CONFIGURE_INIT_TASK_STACK_SIZE      RTEMS_MINIMUM_STACK_SIZE
#define CONFIGURE_INIT_TASK_PRIORITY        1
#define CONFIGURE_INIT_TASK_ATTRIBUTES      RTEMS_DEFAULT_ATTRIBUTES
#define CONFIGURE_INIT_TASK_INITIAL_MODES   RTEMS_PREEMPT
#define CONFIGURE_INIT_TASK_ARGUMENTS       0

extern void __wrap_Init(void *ignored);
rtems_initialization_tasks_table Initialization_tasks[] = {
    {
        CONFIGURE_INIT_TASK_NAME,
        CONFIGURE_INIT_TASK_STACK_SIZE,
        CONFIGURE_INIT_TASK_PRIORITY,
        CONFIGURE_INIT_TASK_ATTRIBUTES,
        __wrap_Init,
        CONFIGURE_INIT_TASK_INITIAL_MODES,
        CONFIGURE_INIT_TASK_ARGUMENTS,
    }
};
#define CONFIGURE_INIT_TASK_TABLE Initialization_tasks

#define CONFIGURE_INIT_TASK_TABLE_SIZE  \
    sizeof(CONFIGURE_INIT_TASK_TABLE) / sizeof(rtems_initialization_tasks_table)

#define CONFIGURE_INIT
#if (__GNUC__ > 3)
#include <rtems/confdefs.h>
#else
#include <confdefs.h>
#endif
/*-----------------------------------------------------------------------------
 *  RTEMS Configuration END
 *-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

void bubble(int lista[], unsigned int num_elementos)
{
    unsigned int i, j;
    int temp;

    for(i = 0;i < num_elementos; i++)
    {
        for(j = 0;j < num_elementos-i; j++)
        {
            if(j + 1 == num_elementos)
                continue; 

            if(lista[j] > lista[j+1])
            {
                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

rtems_task Init(rtems_task_argument ignored)
{
    int lista[] = { 12, 3, 7, 5, 10, 32, 67, 39, 25, 1};
    int i = 0;

    printf("Original list:");
    for (i = 0; i < 10; i++)
        printf(" %d", lista[i]);
    printf("\n");

    bubble(lista, 10);

    printf("Ordered list:");
    for (i = 0; i < 10; i++)
        printf(" %d", lista[i]);
    printf("\n");
}


