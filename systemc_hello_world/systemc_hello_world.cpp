// The tutorial is taken from this website: https://learnsystemc.com/
// Learn with Examples, 2020, MIT license

// Include the SystemC header file. The 'systemc.h' header will
// be deprecated in future, so avoid using it.
#include <systemc>

// A normal C++ function.
inline void hello_standard()
{ // a normal c++ function
    std::cout << "Hello world using approach 1" << std::endl;
}

/*
 * SystemC module:
 * 1. It is the smallest container of functionality with state,
 *    behavior, and structure for hierarchical connectivity.
 * 2. It is a C++ class, which inherits a SystemC basic class: sc_module.
 * 3. It is the principle structural building block of SystemC, and is
 *    used to repsent a component in real systems.
 */

// Define a SystemC module. SystemC module inherits from sc_module.
struct hello_world : public sc_core::sc_module {
    // SystemC provides a macro (SC_CTOR) for convenience
    // when declaring or defining a constructor of a module.
    SC_CTOR(hello_world)
    {
        // Register a member function to the kernel.
        SC_METHOD(hello_SystemC);
    }
    // A function for SystemC simulation kernel, void inside () can be omitted.
    void hello_SystemC(void)
    {
        std::cout << "Hello world using approach 2" << std::endl;
    }
};

/* SystemC Entry point.
 * Q: Why not use the main() like in the standard C++ programs.
 * A: SystemC library has the main() function already defined, therefore
 * main() will call sc_main() and passes the command-line parameters.
 */
int sc_main(int, char*[])
{
    /*-------------Elaboration part start-------------------*/
    // Approach #1: Manually invoke a normal function.
    hello_standard();

    // Approach #2, Instantiate a SystemC module.
    // Good practice to use the instance name as the argument to
    // instance constructor.
    hello_world hw("hw");
    /*-------------Elaboration part finish-------------------*/

    // Let SystemC simulation kernel to invoke helloworld.hello2();
    sc_core::sc_start();

    return 0;
}
