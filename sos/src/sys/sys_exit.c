/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <stdio.h>
#include <stdlib.h>
#include <sel4/sel4.h>
#include <utils/util.h>

#include "execinfo.h" /*for backtrace()*/

static void sos_abort(void)
{
    printf("SOS aborted\n");

    /* Printout backtrace*/
    void *array[10] = {NULL};
    int size = 0;

    size = backtrace(array, 10);
    if (size) {

        printf("Backtracing stack PCs:  ");

        for (int i = 0; i < size; i++) {
            printf("0x%p  ", array[i]);
        }
        printf("\n");
    }
    while (1)
        ; /* We don't return after this */
}

long
sys_exit(UNUSED va_list ap)
{
    abort();
    return 0;
}

long
sys_rt_sigprocmask(UNUSED va_list ap)
{
    ZF_LOGV("Ignoring call to %s\n", __FUNCTION__);
    return 0;
}

long
sys_gettid(UNUSED va_list ap)
{
    ZF_LOGV("Ignoring call to %s\n", __FUNCTION__);
    return 0;
}

long
sys_getpid(UNUSED va_list ap)
{
    ZF_LOGV("Ignoring call to %s\n", __FUNCTION__);
    return 0;
}

long
sys_tgkill(UNUSED va_list ap)
{
    ZF_LOGV("%s assuming self kill\n", __FUNCTION__);
    sos_abort();
    return 0;
}

long sys_tkill(UNUSED va_list ap)
{
    ZF_LOGV("%s assuming self kill\n", __FUNCTION__);
    sos_abort();
    return 0;
}

long
sys_exit_group(UNUSED va_list ap)
{
    ZF_LOGV("Ignoring call to %s", __FUNCTION__);
    return 0;
}
