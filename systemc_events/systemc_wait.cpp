// Include the systemC header file.
#include <systemc>

SC_MODULE(combined)
{
    sc_core::sc_time tMax { 100, sc_core::SC_SEC };
    sc_core::sc_event e0, e1, e2, e3, e4, e5, e6, e7;
    SC_CTOR(combined)
    {
        // Register the threads,
        SC_THREAD(trigger);
        // Register the catchers.
        SC_THREAD(catcher_e0);
        SC_THREAD(catcher_e1_and_e2);
        SC_THREAD(catcher_e3_or_e4);
        SC_THREAD(catcher_timeout_or_e5);
        SC_THREAD(catcher_timeout_or_e6_or_e7);
    };
    combined(sc_core::sc_module_name name_, sc_core::sc_time tMax_)
        : sc_core::sc_module(name_)
        , tMax(tMax_)
    {
        // Register the threads,
        SC_THREAD(trigger);
        // Register the catchers.
        SC_THREAD(catcher_e0);
        SC_THREAD(catcher_e1_and_e2);
        SC_THREAD(catcher_e3_or_e4);
        SC_THREAD(catcher_timeout_or_e5);
        SC_THREAD(catcher_timeout_or_e6_or_e7);
    };
    // Define the trigger.
    void trigger()
    {
        e0.notify(1, sc_core::SC_SEC);
        e1.notify(2, sc_core::SC_SEC);
        e2.notify(3, sc_core::SC_SEC);
        e3.notify(4, sc_core::SC_SEC);
        e4.notify(5, sc_core::SC_SEC);
        e5.notify(6, sc_core::SC_SEC);
        e6.notify(7, sc_core::SC_SEC);
        e7.notify(8, sc_core::SC_SEC);
    };

    void catcher_e0(void)
    {
        // e1 triggered
        sc_core::wait(e0);
        std::cout << sc_core::sc_time_stamp() << ": catch e0" << std::endl;
    }
    void catcher_e1_and_e2(void)
    {
        // e1 and e2
        sc_core::wait(e1 & e2);
        std::cout << sc_core::sc_time_stamp() << ": catch e1 and e2" << std::endl;
    }
    void catcher_e3_or_e4(void)
    {
        // e3 or e4
        sc_core::wait(e3 | e4);
        std::cout << sc_core::sc_time_stamp() << ": catch e3 or e4" << std::endl;
    }
    void catcher_timeout_or_e5(void)
    {
        // timeout or e5
        sc_core::wait(sc_core::sc_time(5, sc_core::SC_SEC), e5);
        std::cout << sc_core::sc_time_stamp() << ": 5sec timeout or catch e5" << std::endl;
    }
    void catcher_timeout_or_e6_or_e7(void)
    {
        // timeout or (e6 or e7)
        sc_core::wait(sc_core::sc_time(20, sc_core::SC_SEC), e6 | e7);
        std::cout << sc_core::sc_time_stamp() << ": 20sec timeout or catch e6 or e7" << std::endl;
    }
};

int sc_main(int, char*[])
{
    sc_core::sc_time finalTime { 100, sc_core::SC_SEC };
    // Create an instance.
    combined com_a("com_a", sc_core::sc_time(50, sc_core::SC_SEC));
    // Run the simuation for a duration of 5 sec.
    sc_core::sc_start(finalTime);
    // Stop the simulation.
    sc_core::sc_stop();
    return 0;
}
