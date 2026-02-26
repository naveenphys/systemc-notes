#include <systemc>

SC_MODULE(multi_writers_t)
{
    // A single-writer signal.
    sc_core::sc_signal<int> s1;
    // A multi-writer signal (using SC_MANY_WRITERS)
    sc_core::sc_signal<int, sc_core::SC_MANY_WRITERS> s2;
    // Constructor.
    SC_CTOR(multi_writers_t)
    {
        // Writes to s1
        SC_THREAD(writer1);
        // Writes to s1 and s2.
        SC_THREAD(writer2);

        SC_THREAD(consumer1);
        // Static sensitivity to s1.
        sensitive << s1;
        dont_initialize();

        SC_THREAD(consumer2);
        // Static sensitivity to s1 | s2.
        sensitive << s1 << s2;
        dont_initialize();
    }

    // Define writer 1.
    void writer1()
    {
        // Initial value.
        int v = 1;
        while (true) {
            s1.write(v); // write to s1
            s2.write(v); // write to s2
            std::cout << sc_core::sc_time_stamp() << ": writer1 writes " << v++ << std::endl;
            // Write every 1 s.
            sc_core::wait(1, sc_core::SC_SEC);
        }
    };

    // Define writer 2.
    void writer2()
    {
        // Initial value.
        int v = -1;
        while (true) {
            /* Cannot write to s1s, otherwise we get runtime error: (E115) sc_signal<T> cannot have more than one driver*/
            // s1.write(v);
            // Offset the write time. Otherwise runtime error: conflicting write in delta cycle 0.
            sc_core::wait(sc_core::SC_ZERO_TIME);
            s2.write(v); // write to s2
            std::cout << sc_core::sc_time_stamp() << ": writer2 writes " << v-- << std::endl;
            // Write every 1 s.
            sc_core::wait(1, sc_core::SC_SEC);
        }
    }

    // Define consumer1.
    void consumer1()
    {
        while (true) {
            // Read s1 and s2.
            std::cout << sc_core::sc_time_stamp() << ": consumer1 reads s1=" << s1.read() << "; s2=" << s2.read() << std::endl;
            // Wait for s1.
            sc_core::wait();
        }
    };

    // Define consumer2.
    void consumer2()
    {
        while (true) {
            // Read s1 and s2.
            std::cout << sc_core::sc_time_stamp() << ": consumer2 reads s1=" << s1.read() << "; s2=" << s2.read() << std::endl;
            // Wait for s1 or s2.
            sc_core::wait();
        }
    };
};

int sc_main(int, char*[])
{
    // Create an instance of the class.
    multi_writers_t mw_a("mw_a");
    // Run simulation for 10 s.
    sc_core::sc_start(10, sc_core::SC_SEC);
    // Stop simulation.
    sc_core::sc_stop();
    return 0;
}
