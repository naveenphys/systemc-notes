#include <systemc>

SC_MODULE(signal_read_write)
{
    // Declare a signal.
    sc_core::sc_signal<int> s;
    // Constructor.
    SC_CTOR(signal_read_write)
    {
        // Register processes.
        SC_THREAD(readwrite);
    }

    // Define readwrite.
    void readwrite()
    {
        // Write to the signal.
        s.write(3);
        std::cout << "s = " << s << "; " << s.read() << std::endl;
        sc_core::wait(sc_core::SC_ZERO_TIME);
        std::cout << "after delta_cycle, s = " << s << std::endl;

        s = 4;
        s = 5;
        int tmp = s;
        std::cout << "s = " << tmp << std::endl;
        sc_core::wait(sc_core::SC_ZERO_TIME);
        std::cout << "after delta_cycle, s = " << s.read() << std::endl;
    }
};

int sc_main(int, char*[])
{
    signal_read_write signal_a("signal_a");
    signal_a.s = -1;
    sc_core::sc_start();
    sc_core::sc_stop();
    return 0;
}
