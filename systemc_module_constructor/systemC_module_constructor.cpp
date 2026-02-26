// Include the systemC header file.
#include <systemc>

// Define a systemC module
// Approach 0: Modules without simulation processes doesn't need SC_CTOR or SC_HAS_PROCESS
SC_MODULE(module_a)
{
    module_a(::sc_core::sc_module_name module_name)
        : sc_core::sc_module(module_name)
    {
        std::cout << name() << ": constructor" << std::endl;
    };
};

// Approach 1: Basic constructor with member function defined inside class.
SC_MODULE(module_b)
{
    // Constructor taking only module name.
    SC_CTOR(module_b)
    {
        // Register member function to systemC simulation kernel.
        SC_METHOD(print_name);
    };
    // Function with no arguments.
    void print_name() { std::cout << name() << ": constructor" << std::endl; };
};

// Approach 2: Basic constructor with member function defined outside class.
SC_MODULE(module_c)
{
    SC_CTOR(module_c)
    {
        // Register member function to systemC simulation kernel.
        SC_METHOD(print_name);
    };
    // Declare the function.
    void print_name();
};

// Function definition outside class body.
void module_c::print_name()
{
    std::cout << name() << ": constructor" << std::endl;
};

// Approach 3: Constructor with additional arguments.
SC_MODULE(module_d)
{
    const int i;
    SC_CTOR(module_d) = delete;
    // Define a constructor with an additional argument.
    // Note that there must be one and only one argument of the
    // kind sc_module_name
    // SC_HAS_PROCESS is recommended.
    module_d(::sc_core::sc_module_name module_name, int i)
        : sc_core::sc_module(module_name)
        , i(i)
    {
        // Register member function to systemC simulation kernel.
        SC_METHOD(print_name);
    };
    // Function with no arguments.
    void print_name() { std::cout << name() << ": constructor" << std::endl; };
};

// Approach 4: Constructor with additional arguments using SC_HAS_PROCESS.
// SC_MODULE(module_e)
// {
//     int i;
//     SC_CTOR(module_e) {};
//     // Define a constructor with an additional argument.
//     SC_HAS_PROCESS(module_e);
//     // Function with no arguments.
//     void print_name() { std::cout << name() << ": constructor " << i << std::endl; };
// };

int sc_main(int, char*[])
{
    module_a mod_a("module_a.mod_a");
    module_b mod_b("module_b:mod_b");
    module_c mod_c("module_c:mod_c");
    module_d mod_d1("module_d:mod_d1", 1);
    module_d mod_d2("module_d:mod_d2", 2);
    // module_e mod_e("module_e:mod_e");

    // Start the simulation.
    sc_core::sc_start();
    return 0;
}
