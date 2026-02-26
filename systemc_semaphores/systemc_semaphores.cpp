#include <systemc>

SC_MODULE(semaphore)
{
    // Declare semaphore.
    sc_core::sc_semaphore s;
    // Constructor: Init semaphore with 2 resources
    SC_CTOR(semaphore)
        : s(2)
    {
        // Register 3 threads competing for resources.
        SC_THREAD(thread_1);
        SC_THREAD(thread_2);
        SC_THREAD(thread_3);
    };
    // Define thread_1.
    void thread_1()
    {
        while (true) {
            // Try to obtain a resource.
            if (s.trywait() == -1) {
                // If not successful, wait till resource is available
                s.wait();
            }
            std::cout << sc_core::sc_time_stamp() << ": locked by thread_1, value is " << s.get_value() << std::endl;
            // Occupy resource for 1 s.
            sc_core::wait(1, sc_core::SC_SEC);
            // Release resource.
            s.post();
            std::cout << sc_core::sc_time_stamp() << ": unlocked by thread_1, value is " << s.get_value() << std::endl;
            // Give time for the other process to lock.
            sc_core::wait(sc_core::SC_ZERO_TIME);
        }
    };
    // Define thread_2.
    void thread_2()
    {
        while (true) {
            // Try to obtain a resource.
            if (s.trywait() == -1) {
                // If not successful, wait till resource is available
                s.wait();
            }
            std::cout << sc_core::sc_time_stamp() << ": locked by thread_2, value is " << s.get_value() << std::endl;
            // Occupy resource for 1 s.
            sc_core::wait(1, sc_core::SC_SEC);
            // Release resource.
            s.post();
            std::cout << sc_core::sc_time_stamp() << ": unlocked by thread_2, value is " << s.get_value() << std::endl;
            // Give time for the other process to lock.
            sc_core::wait(sc_core::SC_ZERO_TIME);
        }
    };
    // Define thread_3.
    void thread_3()
    {
        while (true) {
            // Try to obtain a resource.
            if (s.trywait() == -1) {
                // If not successful, wait till resource is available
                s.wait();
            }
            std::cout << sc_core::sc_time_stamp() << ": locked by thread_3, value is " << s.get_value() << std::endl;
            // Occupy resource for 1 s.
            sc_core::wait(1, sc_core::SC_SEC);
            // Release resource.
            s.post();
            std::cout << sc_core::sc_time_stamp() << ": unlocked by thread_3, value is " << s.get_value() << std::endl;
            // Give time for the other process to lock.
            sc_core::wait(sc_core::SC_ZERO_TIME);
        }
    };
};

int sc_main(int, char*[])
{
    semaphore semaphore_a("semaphore_a");
    sc_core::sc_start(4, sc_core::SC_SEC);
    sc_core::sc_stop();
    return 0;
}
