#include <systemc>

SC_MODULE(sensitivity)
{
    // Events for inter-process triggering.
    sc_core::sc_event e1, e2;
    SC_CTOR(sensitivity)
    {
        // Register processes
        SC_THREAD(trigger_1);
        SC_THREAD(trigger_2);
        SC_THREAD(catch_1or2_dyn);
        SC_THREAD(catch_1or2_static);
        // Static sensitivity for the preceeding process,
        // Can only "OR" of the triggers
        sensitive << e1 << e2;
    }
    void trigger_1()
    {
        // Delay trigger by a delta cycle, make sure catcher is ready.
        sc_core::wait(sc_core::SC_ZERO_TIME);
        while (true) {
            // Trigger e1
            e1.notify(2, sc_core::SC_SEC);
            // Dynamic sensitivity, re-trigger after 2 s
            sc_core::wait(3, sc_core::SC_SEC);
        }
    }

    // Delay trigger by a delta cycle.
    void trigger_2()
    {
        sc_core::wait(sc_core::SC_ZERO_TIME);
        while (true) {
            // Trigger e2
            e2.notify(2, sc_core::SC_SEC);
            // Dynamic sensitivity, re - trigger after 3 s
            sc_core::wait(3, sc_core::SC_SEC);
        }
    }
    void catch_1or2_dyn()
    {
        while (true) {
            // Dynamic sensitivity
            sc_core::wait(e1 | e2);
            std::cout << "Dynamic sensitivty: e1 or e2 @ " << sc_core::sc_time_stamp() << std::endl;
        }
    }
    void catch_1or2_static(void)
    {
        while (true) {
            // static sensitivity
            sc_core::wait();
            std::cout << "Static sensitivity: e1 or e2 @ " << sc_core::sc_time_stamp() << std::endl;
        }
    }
};

int sc_main(int, char*[])
{
    sensitivity sens_a("sens_a");
    sc_core::sc_start(15, sc_core::SC_SEC);
    sc_core::sc_stop();
    return 0;
}
