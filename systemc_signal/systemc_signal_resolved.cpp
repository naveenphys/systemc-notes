#include "systemc.h"
#include <vector>

SC_MODULE(signal_resolved)
{
    // Introduce events.
    sc_core::sc_event e1, e2;
    // Declare a resolved signal channel.
    sc_core::sc_signal_resolved rv1;
    // Declare a vector of possible 4-level logic values.
    std::vector<sc_dt::sc_logic> levels {
        sc_dt::sc_logic_0, // Boolean false.
        sc_dt::sc_logic_1, // Boolean true.
        sc_dt::sc_logic_Z, // High impedence.
        sc_dt::sc_logic_X // Unknown state.
    };
    // Constructor.
    SC_CTOR(signal_resolved)
    {
        // Register processes.
        SC_THREAD(writer1);
        SC_THREAD(writer2);
        SC_THREAD(consumer);
    };

    // Define writer1
    void writer1()
    {
        // Start with initial value.
        int idx = 0;
        while (true) {
            // Write to the resolved signal.
            std::cout << "writer1 writes: " << levels[idx % 4] << " @ " << sc_core::sc_time_stamp() << std::endl;
            rv1.write(levels[idx % 4]);
            idx++;
            e1.notify();
            // Writes every 1 s.
            sc_core::wait(1, sc_core::SC_SEC);
        }
    };

    // Define writer2
    void writer2()
    {
        // Start with initial value.
        int idx = 0;
        while (true) {
            // Write to the resolved signal.
            std::cout << "writer2 writes: " << levels[(idx / 4) % 4] << " @ " << sc_core::sc_time_stamp() << std::endl;
            rv1.write(levels[(idx / 4) % 4]);
            idx++;
            e2.notify();
            // Writes every 1 s.
            sc_core::wait(1, sc_core::SC_SEC);
        }
    };

    // Define consumer.
    void consumer()
    {
        // sc_core::wait(sc_core::SC_ZERO_TIME);
        while (true) {
            sc_core::wait(e1 & e2);
            // Read after e1 and e2 notifications are recieved.
            std::cout << "consumer read: " << rv1.read() << " @ " << sc_core::sc_time_stamp() << std::endl;
            // sc_core::wait(1, sc_core::SC_SEC);
        }
    };
};

int sc_main(int, char*[])
{
    // Create an instance of the module.
    signal_resolved sig_res("sig_res");
    // Start the simulation.
    sc_core::sc_start(10, sc_core::SC_SEC);
    // Stop the simulation.
    sc_core::sc_stop();
    return 0;
}
