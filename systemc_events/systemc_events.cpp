#include <systemc>

SC_MODULE(event)
{
    // Declare an event.
    sc_core::sc_event e;
    SC_CTOR(event)
    {
        // Register a trigger process.
        SC_THREAD(trigger);
        // register a catcher process.
        SC_THREAD(catcher);
    }

    // Define the trigger process.
    void trigger()
    {
        // Start an infinite loop.
        while (true) {
            // Trigger after 1 second
            e.notify(1, sc_core::SC_SEC);
            if (sc_core::sc_time_stamp() == sc_core::sc_time(4, sc_core::SC_SEC)) {
                // cancel the event triggered at time = 4 s
                e.cancel();
            }
            // Wait for 1 sec, and go to the top of the loop and trigger again.
            sc_core::wait(1, sc_core::SC_SEC);
        }
    };
    // Define the catcher process.
    void catcher()
    {
        // Start an infinite loop.
        while (true) {
            // Wait for an event.
            sc_core::wait(e);
            // Print to the console.
            std::cout << "catcher time: " << sc_core::sc_time_stamp() << std::endl;
        }
    };
};

int sc_main(int, char*[])
{
    sc_core::sc_time finalTime { 5, sc_core::SC_SEC };
    // Create an instance.
    event event_a("event_a");
    // Run the simuation for a duration of 5 sec.
    sc_core::sc_start(finalTime);
    // Stop the simulation.
    sc_core::sc_stop();
    return 0;
}
