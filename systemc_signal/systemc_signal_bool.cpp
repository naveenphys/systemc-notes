#include "systemc.h"

SC_MODULE(signal_bool)
{
    // Declare signal bool,
    sc_core::sc_signal<bool> b;
    // Constructor.
    SC_CTOR(signal_bool)
    {
        SC_THREAD(writer);
        SC_THREAD(consumer);
        // Triggered by every value change.
        sensitive << b;
        dont_initialize();
        SC_THREAD(consumer_pos);
        // triggered by value change to true.
        sensitive << b.posedge_event();
        dont_initialize();
        SC_THREAD(consumer_neg);
        // Triggered by value change to false
        sensitive << b.negedge_event();
        dont_initialize();
    }

    // Define writer.
    void writer()
    {
        bool v = true;
        while (true) {
            // Write to channel.
            b.write(v);
            // Toggle value.
            v = !v;
            // Write every 1 s.
            sc_core::wait(1, sc_core::SC_SEC);
        }
    };

    // Define consumer (triggered on both edges).
    void consumer()
    {
        while (true) {
            // If new value is true
            if (b.posedge()) {
                std::cout << sc_core::sc_time_stamp() << ": consumer receives posedge, b = " << b << std::endl;
                // if new value is false
            } else {
                std::cout << sc_core::sc_time_stamp() << ": consumer receives negedge, b = " << b << std::endl;
            }
            // Wait for any value change in b, as it is ensitive to b.
            sc_core::wait();
        }
    }

    // Define consumer_pos (triggered on rising edge).
    void consumer_pos()
    {
        while (true) {
            std::cout << sc_core::sc_time_stamp() << ": consumer_pos receives posedge, b = " << b << std::endl;
            // Sensitive to positive edge of b.
            sc_core::wait();
        }
    };

    // Define consumer_neg (triggered on falling edge).
    void consumer_neg()
    {
        while (true) {
            std::cout << sc_core::sc_time_stamp() << ": consumer_neg receives negedge, b = " << b << std::endl;
            // Sensitive to negative edge of b.
            sc_core::wait();
        }
    };
};

int sc_main(int, char*[])
{
    // Create an instance of the module.
    signal_bool sig_bool("sig_bool");
    // Start the simulation.
    sc_core::sc_start(10, sc_core::SC_SEC);
    // Stop the simulation.
    sc_core::sc_stop();
    return 0;
}
