#include <systemc>

SC_MODULE(buffer)
{
    // Declare signal.
    sc_core::sc_signal<int> s;
    // Declare a buffer.
    sc_core::sc_buffer<int> b;
    // Constructor.
    SC_CTOR(buffer)
    {
        // Register processes.
        SC_THREAD(writer);
        SC_THREAD(consumer_s);
        sensitive << s;
        dont_initialize();
        SC_THREAD(consumer_b);
        sensitive << b;
        dont_initialize();
    };

    // Define writer.
    void writer()
    {
        int val = 1;
        while (true) {
            // Write same value to channel twice.
            for (int i = 0; i < 2; ++i) {
                // Write to signal.
                s.write(val);
                // Write to buffer.
                b.write(val);
                // Wait for 1 s.
                sc_core::wait(1, sc_core::SC_SEC);
            }
            // Value change.
            val++;
        };
    };

    // Define consumer of signal.
    void consumer_s()
    {
        while (true) {
            std::cout << sc_core::sc_time_stamp() << ": consumer_s receives " << s.read() << std::endl;
            // Receives from signal.
            sc_core::wait();
        }
    }

    // Define consumer of buffer.
    void consumer_b()
    {
        while (true) {
            std::cout << sc_core::sc_time_stamp() << ": consumer_b receives " << b.read() << std::endl;
            // Receives from buffer.
            sc_core::wait();
        }
    }
};

int sc_main(int, char*[])
{
    // Create an instance of the module.
    buffer buffer_a("buffer_a");
    // Start the simulation.
    sc_core::sc_start(10, sc_core::SC_SEC);
    // Stop the simulation.
    sc_core::sc_stop();
    return 0;
}
