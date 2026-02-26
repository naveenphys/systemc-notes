// Include the systemC header file.
#include <systemc>

// Define a SystemC module.
// Approach 1: SystemC module as a struct.
struct module_a : public sc_core::sc_module {
    // name() returns the object name, which is provided during instantization.
    SC_CTOR(module_a) { std::cout << name() << ": constructor" << std::endl; }
};

// Approach 2: SystemC module as a class.
class module_b : public sc_core::sc_module {
    // Constructor must have public access.
public:
    // constructor needs to be defined as a public function.
    // name() returns the object name, which is provided during instantization.
    SC_CTOR(module_b) { std::cout << name() << ": constructor" << std::endl; }
};

// Approach 3: Using the macro `SC_MODULE`
SC_MODULE(module_c) {
    // name() returns the object name, which is provided during instantization.
    SC_CTOR(module_c) { std::cout << name() << ": constructor" << std::endl;
}
}
;

// systemC entry point
int sc_main(int, char*[])
{
    // In C++ class name can be used as a type.
    module_a m_a("module_a");
    module_b m_b("module_b");
    module_c m_c("module_c");

    // Starts the simulation.
    sc_core::sc_start();

    return 0;
}
