#include <systemc>

SC_MODULE(event_queue)
{
    // Declare event.
    sc_core::sc_event e;
    // Declare event queue.
    sc_core::sc_event_queue eq;
    // Constructor.
    SC_CTOR(event_queue)
    {
        // Register processes.
        SC_THREAD(trigger);
        SC_THREAD(catch_e);
        // Process catch_e() will be triggered by event e.
        sensitive << e;
        // Don't run cach_e() during initialization phase.
        dont_initialize();
        SC_THREAD(catch_eq);
        // Process cach_eq() will be triggered by event queue eq.
        sensitive << eq;
        // Don't run catch_eq() during initialization phase.
        dont_initialize();
    }
    // Define the trigger.
    void trigger()
    {
        while (true) {
            // Trigger e afer 2 s
            e.notify(2, sc_core::SC_SEC);
            // Trigger e after 1 s, replaces previous
            e.notify(1, sc_core::SC_SEC);
            // Trigger eq after 2 s.
            eq.notify(2, sc_core::SC_SEC);
            // trigger eq after 1 s, both triggers are available.
            eq.notify(1, sc_core::SC_SEC);
            // Another trigger round.
            sc_core::wait(10, sc_core::SC_SEC);
        }
    }
    // Define the catcher for event.
    void catch_e()
    {
        while (true) {
            std::cout << sc_core::sc_time_stamp() << ": catches e" << std::endl;
            // No parameter --> wait for static sensitivity, i.e. e
            sc_core::wait();
        }
    }
    // Define the catcher for event queue.
    void catch_eq()
    {
        while (true) {
            std::cout << sc_core::sc_time_stamp() << ": catches eq" << std::endl;
            // no parameter --> wait for static sensitivity, i.e. e
            sc_core::wait();
        }
    }
};

int sc_main(int, char*[])
{
    // Instantiate object
    event_queue queue("queue");
    // Run simulation for 20 s
    sc_core::sc_start(20, sc_core::SC_SEC);
    sc_core::sc_stop();
    return 0;
}
