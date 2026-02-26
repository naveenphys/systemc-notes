#include <systemc>

SC_MODULE(delta_cycle)
{
    int x = 1;
    // Constructor.
    SC_CTOR(delta_cycle)
    {
        // Register processes.
        SC_THREAD(add_2_to_x);
        SC_THREAD(multiply_2_to_x);
    };

    // Executed first.
    void add_2_to_x()
    {
        std::cout << "add_2_to_x: " << sc_core::sc_time_stamp() << std::endl;
        x += 2;
        std::cout << "x: " << x << std::endl;
    }
    // Waits for the next delta cycle.
    void multiply_2_to_x()
    {
        // Causes the event to be notified in the evaluate phase of the next
        // delta cycle, this is called a "delta notification"
        sc_core::wait(sc_core::SC_ZERO_TIME);
        std::cout << "multiply_2_to_x: " << sc_core::sc_time_stamp() << std::endl;
        x *= 2;
        std::cout << "x: " << x << std::endl;
    }
};

int sc_main(int, char*[])
{
    delta_cycle dc_a("dc_a");
    sc_core::sc_start(sc_core::sc_time { 20, sc_core::SC_SEC });
    sc_core::sc_stop();
    return 0;
}
