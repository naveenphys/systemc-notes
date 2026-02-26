#include <systemc>

SC_MODULE(initialization)
{
    // Event for inter-process trigger
    sc_core::sc_event e;
    SC_CTOR(initialization)
    {
        SC_THREAD(trigger);
        SC_THREAD(catcher_1);
        SC_THREAD(catcher_2);
        SC_THREAD(catcher_3);
        sensitive << e;
        dont_initialize();
    };

    // Trigger.
    void trigger()
    {
        // e triggered at 1, 3, 5, 7 ...
        while (true) {
            // Notify after 1 s
            e.notify(1, sc_core::SC_SEC);
            // Trigger every 2 s
            wait(2, sc_core::SC_SEC);
        }
    };

    // Catcher.
    void catcher_1()
    {
        while (true) {
            std::cout << sc_core::sc_time_stamp() << ": catcher_1 triggered" << std::endl;
            // Dynamic sensitivity
            sc_core::wait(e);
        }
    };
    // Catcher.
    void catcher_2()
    {
        sc_core::wait(e);
        // Avoid initialization - mimic systemC 1.0 behavior wait(e);
        while (true) {
            std::cout << sc_core::sc_time_stamp() << ": catcher_2 triggered" << std::endl;
            // Dynamic sensitivity
            sc_core::wait(e);
        }
    };

    // catcher_3
    // Relies on dont_initialize() to avoid initialization.
    // Therefore, catcher_2 must be triggered before catcher_3.
    void catcher_3()
    {
        while (true) {
            std::cout << sc_core::sc_time_stamp() << ": catcher_3 triggered" << std::endl;
            // Dynamic sensitivity
            sc_core::wait(e);
        }
    };
};

int sc_main(int, char*[])
{
    initialization init_a("init_a");
    sc_core::sc_start(sc_core::sc_time(10, sc_core::SC_SEC));
    sc_core::sc_stop();
    return 0;
}
