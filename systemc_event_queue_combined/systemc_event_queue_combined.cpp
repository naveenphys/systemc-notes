#include <systemc>

SC_MODULE(event_queue_combined)
{
    // Declare event queues.
    sc_core::sc_event_queue eq1, eq2;
    // Constructor.
    SC_CTOR(event_queue_combined)
    {
        // Register processes.
        SC_THREAD(trigger);
        SC_THREAD(catcher_eq1_or_eq2);
        // Static sensitivity.
        sensitive << eq1 << eq2;
        // Don't trigger during initialization phase.
        dont_initialize();
    };

    // Define the trigger.
    void trigger()
    {
        while (true) {
            // Trigger e afer 2 s
            eq1.notify(1, sc_core::SC_SEC);
            // Trigger e after 1 s, replaces previous
            eq1.notify(3, sc_core::SC_SEC);
            // Trigger eq after 2 s.
            eq2.notify(2, sc_core::SC_SEC);
            // trigger eq after 1 s, both triggers are available.
            eq2.notify(4, sc_core::SC_SEC);
            // Another trigger round.
            sc_core::wait(10, sc_core::SC_SEC);
            // Another trigger round.
        }
    };

    // Define the catcher.
    void catcher_eq1_or_eq2()
    {
        while (true) {
            std::cout << "catcher_eq1_or_eq2: " << sc_core::sc_time_stamp() << std::endl;
            // No arguments -- as the sensitivity is static.
            sc_core::wait();
        }
    };
};

int sc_main(int, char*[])
{
    event_queue_combined eqc("eqc");
    // Simulate for 20 sec.
    sc_core::sc_start(20, sc_core::SC_SEC);
    sc_core::sc_stop();
    return 0;
}
