#include <systemc>

SC_MODULE(signal_detect_event)
{
    // Defines two signal channels
    sc_core::sc_signal<int> s1, s2;
    // Constructor.
    SC_CTOR(signal_detect_event)
    {
        // Register processes.
        SC_THREAD(producer_s1);
        SC_THREAD(producer_s2);
        // Consumer sensitive to (s1 OR s2)
        SC_THREAD(consumer_s1_or_s2);
        // same as: sensitive << s1.default_event();
        // same as: sensitive << s2.value_changed_event();
        sensitive << s1 << s2;
        // Consumer initialization is delayed by one cycle.
        dont_initialize();
    }

    // Define the producer for s1.
    void producer_s1()
    {
        int v = 1;
        while (true) {
            // Write to s1.
            s1.write(v++);
            sc_core::wait(2, sc_core::SC_SEC);
        }
    }
    void producer_s2()
    {
        int v = 1;
        while (true) {
            // Write to s2.
            s2 = v++;
            sc_core::wait(3, sc_core::SC_SEC);
        }
    }

    // Define the consumer.
    void consumer_s1_or_s2()
    {
        while (true) {
            if (s1.event() == true && s2.event() == true) {
                // Both triggered.
                std::cout << sc_core::sc_time_stamp() << ": s1 & s2 triggered" << std::endl;
            } else if (s1.event() == true) {
                // Only s1 triggered.
                std::cout << sc_core::sc_time_stamp() << ": s1 triggered" << std::endl;
            } else {
                // Only s2 triggered.
                std::cout << sc_core::sc_time_stamp() << ": s2 triggered" << std::endl;
            }
            sc_core::wait();
        }
    }
};

int sc_main(int, char*[])
{
    signal_detect_event signal_de_a("signal_de_a");
    sc_core::sc_start(7, sc_core::SC_SEC);
    sc_core::sc_stop();
    return 0;
}
