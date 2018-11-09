/** @file debug_tools_test.c
 * 
 * @brief This file implements a few tests for the debug_tools macro.
 * 
 * @author Etienne Hamelin
 */

#include <stdio.h>

#include "debug_tools.h"

/**
 * @brief Fibonacci suite implemented using naive recursion. 
 */
int fibonacci(int n)
{
    TRACE_MSG("n = %d", n);
    
    if (n <= 1) {
        return 0;
    }
    else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

/**
 * @brief test harness
 */
int main(int argc, char** argv) 
{
    int x = 0xFFFF; 
    int y = 6;
    int z;
    double d = 1.234567e8;

    INFO("Below is the file name and compilation timestamp");
    INFO(FILE_INFO);
    INFO("This is an information message with params %d, %i, %f", x, y, d);
    WARNING("This is a warning");
    DEBUG("This is a debug information");
    ERROR("This is an error");

    TRACE();
    z = fibonacci(y);
    INFO("z = %d", z);
    INFO("This is the end of the test");
    return 0;
}
