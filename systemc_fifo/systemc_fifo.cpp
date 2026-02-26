#include <systemc>

// 1. int num_available(): returns the number of values that are available
// for reading in the current delta cycle.The calculation shall deduct any
// values read during the current delta cycle but shall not add any values
// written during the current delta cycle.

// 2. int num_free(): returns the number of empty slots that are free for
// writing in the current delta cycle. The calculation shall deduct any
// slots written during the current delta cycle but shall not add any slots
// made free by reading in the current delta cycle.

SC_MODULE(fifo)
{
    // Declare fifo.
    sc_core::sc_fifo<int> f1, f2, f3;
    // Constructor.
    // Each fifo with size 2
    SC_CTOR(fifo)
        : f1(2)
        , f2(2)
        , f3(3)
    {
        // Register processes.
        SC_THREAD(generator1);
        SC_THREAD(consumer1);
        SC_THREAD(generator2);
        SC_THREAD(consumer2);
        SC_THREAD(generator3);
        SC_THREAD(consumer3);
    };

    // Define generator1.
    // blocking write
    void generator1()
    {
        int v = 0;
        while (true) {
            // Same as f = v, which is not recommended.
            f1.write(v);
            std::cout << sc_core::sc_time_stamp() << ": generator1 writes " << v++ << std::endl;
            // Write every 1 s
            sc_core::wait(1, sc_core::SC_SEC);
        }
    };

    // Define consumer1.
    // Blocking read.
    void consumer1()
    {
        int v = -1;
        while (true) {
            // Same as v = int(f), which is not recommended; or, v = f1.read();
            f1.read(v);
            std::cout << sc_core::sc_time_stamp() << ": consumer1 reads " << v << std::endl;
            // Read every 3 s, fifo will fill up soon
            sc_core::wait(3, sc_core::SC_SEC);
        }
    };

    // Define generator2.
    // Non-blocking write.
    void generator2()
    {
        int v = 0;
        while (true) {
            // Non-blocking write until succeeded
            while (f2.nb_write(v) == false) {
                // If not successful, wait for data read (a fifo slot becomes available)
                sc_core::wait(f2.data_read_event());
            }
            std::cout << sc_core::sc_time_stamp() << ": generator2 writes " << v++ << std::endl;
            // Write every 1 s
            sc_core::wait(1, sc_core::SC_SEC);
        }
    };

    // Define consumer2.
    // Non-blocking read.
    void consumer2()
    {
        int v = -1;
        while (true) {
            while (f2.nb_read(v) == false) {
                sc_core::wait(f2.data_written_event());
            }
            std::cout << sc_core::sc_time_stamp() << ": consumer2 reads " << v << std::endl;
            // Read every 3 s, fifo will fill up soon
            sc_core::wait(3, sc_core::SC_SEC);
        }
    }

    // Define generator3.
    // free/available slots before/after write
    void generator3()
    {
        int v = 0;
        while (true) {
            std::cout << sc_core::sc_time_stamp() << ": generator3, before write, #free/#available=" << f3.num_free() << "/" << f3.num_available() << std::endl;
            f3.write(v++);
            std::cout << sc_core::sc_time_stamp() << ": generator3, after write, #free/#available=" << f3.num_free() << "/" << f3.num_available() << std::endl;
            sc_core::wait(1, sc_core::SC_SEC);
        }
    };

    // Define consumer3.
    // free/available slots before/after read
    void consumer3()
    {
        int v = -1;
        while (true) {
            std::cout << sc_core::sc_time_stamp() << ": consumer3, before read, #free/#available=" << f3.num_free() << "/" << f3.num_available() << std::endl;
            f3.read(v);
            std::cout << sc_core::sc_time_stamp() << ": consumer3, after read, #free/#available=" << f3.num_free() << "/" << f3.num_available() << std::endl;
            // Read every 3 s, fifo will fill up soon
            sc_core::wait(3, sc_core::SC_SEC);
        }
    };
};

int sc_main(int, char*[])
{
    fifo fifo_a("fifo_a");
    sc_core::sc_start(20, sc_core::SC_SEC);
    sc_core::sc_stop();
    return 0;
}
