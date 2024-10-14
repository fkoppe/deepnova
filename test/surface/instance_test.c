#include <dark/darktest.h>

#include <deep/deepnova.h>

#include <deep/surface/instance_struct.h>

int main()
{
    Dark_Allocator* allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("instance_construct/destruct")
    {
        Deep_Instance instance;

        deep_instance_construct(allocator, &instance);
        deep_instance_destruct(&instance);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("instance_new/delete")
    {
        Deep_Instance* const instance = deep_instance_new(allocator);
        deep_instance_delete(instance);
    }
    //--------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
