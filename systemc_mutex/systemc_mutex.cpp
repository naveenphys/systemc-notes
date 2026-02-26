#include <systemc>

SC_MODULE(mutex)
{
    // Declare a mutex.
    sc_core::sc_mutex m;
    // Constructor.
    SC_CTOR(mutex)
    {
        // Register processes.
        SC_THREAD(thread_1);
        SC_THREAD(thread_2);
    }
    // Define process thread_1.
    void thread_1()
    {
        while (true) {
            // Try to lock the mutex.
            if (m.trylock() == -1) {
                // Failed, wait to lock.
                m.lock();
                std::cout << sc_core::sc_time_stamp() << ": thread_1 obtained resource by lock()" << std::endl;
            } else {
                // Succeeded.
                std::cout << sc_core::sc_time_stamp() << ": thread_1 obtained resource by trylock()" << std::endl;
            }
            // Occupy mutex for 1 s.
            sc_core::wait(1, sc_core::SC_SEC);
            // Unlock mutex
            m.unlock();
            std::cout << sc_core::sc_time_stamp() << ": unlocked by thread_1" << std::endl;
            // Give time for the other process to lock the mutex.
            sc_core::wait(sc_core::SC_ZERO_TIME);
        }
    }
    void thread_2()
    {
        while (true) {
            // Try to lock the mutex
            if (m.trylock() == -1) {
                // Failed, wait to lock.
                m.lock();
                std::cout << sc_core::sc_time_stamp() << ": thread_2 obtained resource by lock()" << std::endl;
            } else {
                // Succeeded.
                std::cout << sc_core::sc_time_stamp() << ": thread_2 obtained resource by trylock()" << std::endl;
            }
            sc_core::wait(1, sc_core::SC_SEC);
            // Occupy mutex for 1 s.
            m.unlock();
            // Unlock mutex.
            std::cout << sc_core::sc_time_stamp() << ": unlocked by thread_2" << std::endl;
            // Give time for the other process to lock the mutex.
            sc_core::wait(sc_core::SC_ZERO_TIME);
        }
    }
};

int sc_main(int, char*[])
{
    mutex mutex_a("mutex_a");
    sc_core::sc_start(4, sc_core::SC_SEC);
    sc_core::sc_stop();
    return 0;
}
