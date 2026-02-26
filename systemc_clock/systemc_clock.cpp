#include <systemc>

SC_MODULE(mod_clock)
{
    // A port to access clock.
    sc_core::sc_port<sc_core::sc_signal_in_if<bool>> clk;
    // Constructor.
    SC_CTOR(mod_clock)
    {
        // Register process.
        SC_THREAD(thread);
        // Static sensitive to clock.
        sensitive << clk;
        // Dont run during initialization (wait for one delta cycle).
        dont_initialize();
    };

    // Define the process.
    void thread()
    {
        while (true) {
            // print current clock value.
            std::cout << sc_core::sc_time_stamp() << ", value = " << clk->read() << std::endl;
            // Wait for next clock value change.
            sc_core::wait();
        }
    };
};

int sc_main(int, char*[])
{
    // 10s period, 2s true, 8s false, start at 10s, start at false.
    sc_core::sc_clock clk_a("clk_a", 10, sc_core::SC_SEC, 0.2, 10, sc_core::SC_SEC, false);
    // Instantiate module.
    mod_clock clock_a("clock_a");
    // Bind port.
    clock_a.clk(clk_a);
    // // Run simulation for 31 s.
    sc_core::sc_start(31, sc_core::SC_SEC);
    sc_core::sc_stop();
    return 0;
}
