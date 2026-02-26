// Learn with Examples, 2020, MIT license
#include <systemc>

SC_MODULE(PROCESS)
{
    // Declare a clock.
    sc_core::sc_clock clk;
    // Constructor instantiate a clock with 1sec periodicity
    SC_CTOR(PROCESS)
        : clk("clk", 1, sc_core::SC_SEC)
    {
        SC_METHOD(method); // Register a method.
        SC_THREAD(thread); // Register a thread.
        SC_CTHREAD(cthread, clk); // Register a clocked thread,
    }

    // Define the method member function.
    void method(void)
    {
        // No while loop here as the process cannot be suspended.
        std::cout << "method triggered @ " << sc_core::sc_time_stamp() << std::endl;
        // Trigger after 1 sec
        sc_core::next_trigger(sc_core::sc_time(1, sc_core::SC_SEC));
    }

    // Define the thread member function,
    void thread()
    {
        // infinite loop make sure it never exits.
        while (true) {
            std::cout << "thread triggered @ " << sc_core::sc_time_stamp() << std::endl;
            // Wait 1 sec before execute again
            sc_core::wait(1, sc_core::SC_SEC);
        }
    }

    // Define the cthread member function
    void cthread()
    {
        // Infinite loop
        while (true) {
            std::cout << "cthread triggered @ " << sc_core::sc_time_stamp() << std::endl;
            // Wait for next clk event, which comes after 1 sec.
            sc_core::wait();
        }
    }
};

int sc_main(int, char*[])
{
    // Initialize module
    PROCESS process("process");
    std::cout << "execution phase begins @ " << sc_core::sc_time_stamp()
              << std::endl;
    // Run simulation for 2 second
    sc_core::sc_start(2, sc_core::SC_SEC);
    std::cout << "execution phase ends @ " << sc_core::sc_time_stamp() << std::endl;
    return 0;
}
