#include <dark/darktest.h>

#include <dark/darkstar.h>
#include <deep/deepnova.h>

#include "stdio.h"

int main()
{
    Dark_Allocator* allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("handler")
    {
        Dark_Entropy entropy = dark_entropy_seed();

        deep_handler_initialise(allocator, &entropy, NULL, NULL);
        deep_handler_shutdown();
    }
    //--------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
