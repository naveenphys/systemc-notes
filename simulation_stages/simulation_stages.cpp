#include <systemc>

SC_MODULE(stage_t)
{
    SC_CTOR(stage_t)
    {
        std::cout << sc_core::sc_time_stamp() << ": Elaboration: constructor" << std::endl;
        SC_THREAD(thread);
    };
    void thread()
    {
        // Execution initialization.
        std::cout << sc_core::sc_time_stamp() << ": Execution.initialization:" << std::endl;
        std::size_t count = 0;
        while (true) {
            // Advance-time.
            sc_core::wait(1, sc_core::SC_SEC);
            // Evaluation.
            std::cout << sc_core::sc_time_stamp() << ": Execution.simulation" << std::endl;
            // Stop simulation after 2 iterations.
            if (count++ >= 2) {
                sc_core::sc_stop();
            }
        }
    };

    // callback: before_end_of_elaboration()
    void before_end_of_elaboration()
    {
        std::cout << sc_core::sc_time_stamp() << ": before end of elaboration" << std::endl;
    }
    // callback: end_of_elaboration()
    void end_of_elaboration()
    {
        std::cout << sc_core::sc_time_stamp() << ": end of elaboration" << std::endl;
    }
    // callback: start_of_simulation()
    void start_of_simulation()
    {
        std::cout << sc_core::sc_time_stamp() << ": start of simulation" << std::endl;
    }
    // callback: end_of_simulation()
    void end_of_simulation()
    {
        std::cout << sc_core::sc_time_stamp() << ": end of simulation" << std::endl;
    }
    // Destructor.
    ~stage_t()
    {
        std::cout << sc_core::sc_time_stamp() << ": Cleanup: destructor" << std::endl;
    };
};

int sc_main(int, char*[])
{
    stage_t stage("stage");
    sc_core::sc_start();
    return 0;
}
