#include <systemc>

SC_MODULE(process)
{
    sc_core::sc_event e;
    // Constructor
    SC_CTOR(process)
    {
        // Register a trigger process.
        SC_THREAD(trigger);
        // Register a thread process.
        SC_THREAD(thread);
        // Register a method process.
        SC_METHOD(method);
        // Static sensitivity of the method to event e.
        sensitive << e;
    };
    void trigger()
    {
        while (true) {
            e.notify();
            std::cout << "trigger @ " << sc_core::sc_time_stamp() << std::endl;
            sc_core::wait(1, sc_core::SC_SEC);
        }
    };
    void thread()
    {
        // declare only once
        int idx = 0;
        // loop forever
        while (true) {
            std::cout << "thread" << idx++ << " @ " << sc_core::sc_time_stamp() << std::endl;
            // re - trigger after 1 s
            sc_core::wait(1, sc_core::SC_SEC);
        }
    }

    void method()
    {
        // notice there's no while loop here
        // re-declare every time, this method is triggered, as the local
        // variables are destroyed on return from the method.
        int idx = 0;
        std::cout << "method" << idx++ << " @ " << sc_core::sc_time_stamp() << std::endl;
        next_trigger(1, sc_core::SC_SEC);
    }
};
int sc_main(int, char*[])
{
    process process_a("process_a");
    sc_core::sc_start(4, sc_core::SC_SEC);
    sc_core::sc_stop();
    return 0;
}
