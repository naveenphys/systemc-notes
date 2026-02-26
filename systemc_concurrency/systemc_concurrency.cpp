#include <systemc>

SC_MODULE(concurrency)
{
    // Threads will execute until simulation time becomes tMax.
    sc_core::sc_time tMax { 10, sc_core::SC_FS };
    // Constructor.
    SC_CTOR(concurrency)
    {
        // Register the processes.
        SC_THREAD(thread_a);
        SC_THREAD(thread_b);
    };

    // Constructor with extra arguments.
    concurrency(::sc_core::sc_module_name name_, sc_core::sc_time & tMax_)
        : sc_core::sc_module(name_)
        , tMax(tMax_)
    {
        // Register the processes.
        SC_THREAD(thread_a);
        SC_THREAD(thread_b);
    }
    // Define the processes.
    void thread_a()
    {
        static int countMax = tMax / sc_core::sc_get_time_resolution();
        // Time interval at which the thread is triggered is equal to the time
        // resolution.
        static sc_core::sc_time waitTime { sc_core::sc_get_time_resolution() };
        int count_a = 0;
        while (count_a <= countMax) {
            std::cout << "thread_a: " << sc_core::sc_time_stamp() << std::endl;
            sc_core::wait(waitTime);
            count_a++;
        }
    };
    void thread_b()
    {
        static int countMax = tMax / sc_core::sc_get_time_resolution();
        // Time interval at which the thread is triggered is equal to the time
        // resolution.
        static sc_core::sc_time waitTime { sc_core::sc_get_time_resolution() };
        int count_b = 0;
        while (count_b <= countMax) {
            std::cout << "thread_b: " << sc_core::sc_time_stamp() << std::endl;
            sc_core::wait(waitTime);
            count_b++;
        }
    };
};

int sc_main(int, char*[])
{
    // Set the time resolution.
    sc_core::sc_set_time_resolution(1, sc_core::SC_FS);
    sc_core::sc_time finalTime { 5, sc_core::SC_FS };
    // Create an instance,
    concurrency concurrency_a("conc_a", finalTime);
    // Run the simuation for a duration of 10 fs.
    sc_core::sc_start(finalTime);
    sc_core::sc_stop();
    return 0;
}
