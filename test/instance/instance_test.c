#include <dark/darktest.h>

#include <dark/darkstar.h>
#include <deep/deepnova.h>

int main()
{
    Dark_Allocator* allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("instance_construct/destruct")
    {
        Dark_Entropy entropy = dark_entropy_seed();

        Dark_Allocator* const os_allocator = dark_os_allocator_new();

        //deep_surface_initialise(os_allocator, &entropy, NULL, NULL);
        //deep_surface_shutdown();

        //dark_os_allocator_delete(os_allocator);
    }
    //--------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
