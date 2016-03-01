/*  =========================================================================
    blink_selftest.c - run selftests

    Runs all selftests.

    -------------------------------------------------------------------------
    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is part of the Blink Project.                            
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
    =========================================================================
*/

#include "blink_classes.h"

typedef struct {
    const char *testname;
    void (*test) (bool);
} test_item_t;

static test_item_t
all_tests [] = {
#ifdef BLINK_BUILD_DRAFT_API
    { "blink_led", blink_led_test },
#endif // BLINK_BUILD_DRAFT_API
    {0, 0}          //  Sentinel
};

//  -------------------------------------------------------------------------
//  Test whether a test is available.
//  Return a pointer to a test_item_t if available, NULL otherwise.
//

test_item_t *
test_available (const char *testname)
{
    test_item_t *item;
    for (item = all_tests; item->test; item++) {
        if (streq (testname, item->testname))
            return item;
    }
    return NULL;
}

//  -------------------------------------------------------------------------
//  Run all tests.
//

static void
test_runall (bool verbose)
{
    test_item_t *item;
    printf ("Running blink selftests...\n");
    for (item = all_tests; item->test; item++)
        item->test (verbose);

    printf ("Tests passed OK\n");
}

int
main (int argc, char **argv)
{
    bool verbose = false;
    test_item_t *test = 0;
    int argn;
    for (argn = 1; argn < argc; argn++) {
        if (streq (argv [argn], "--help")
        ||  streq (argv [argn], "-h")) {
            puts ("blink_selftest.c [options] ...");
            puts ("  --verbose / -v         verbose test output");
            puts ("  --number / -n          report number of tests");
            puts ("  --list / -l            list all tests");
            puts ("  --test / -t [name]     run only test 'name'");
            puts ("  --continue / -c        continue on exception (on Windows)");
            return 0;
        }
        if (streq (argv [argn], "--verbose")
        ||  streq (argv [argn], "-v"))
            verbose = true;
        else
        if (streq (argv [argn], "--number")
        ||  streq (argv [argn], "-n")) {
            puts ("1");
            return 0;
        }
        else
        if (streq (argv [argn], "--list")
        ||  streq (argv [argn], "-l")) {
            puts ("Available tests:");
            puts ("    blink_led");
            return 0;
        }
        else
        if (streq (argv [argn], "--test")
        ||  streq (argv [argn], "-t")) {
            argn++;
            if (argn >= argc) {
                fprintf (stderr, "--test needs an argument\n");
                return 1;
            }
            test = test_available (argv [argn]);
            if (!test) {
                fprintf (stderr, "%s not valid, use --list to show tests\n", argv [argn]);
                return 1;
            }
        }
        else
        if (streq (argv [argn], "--continue")
        ||  streq (argv [argn], "-c")) {
#ifdef _MSC_VER
            //  When receiving an abort signal, only print to stderr (no dialog)
            _set_abort_behavior (0, _WRITE_ABORT_MSG);
#endif
        }
        else {
            printf ("Unknown option: %s\n", argv [argn]);
            return 1;
        }
    }
    if (test) {
        printf ("Running blink test '%s'...\n", test->testname);
        test->test (verbose);
    }
    else
        test_runall (verbose);

    return 0;
}
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/
