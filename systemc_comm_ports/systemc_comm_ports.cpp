#include <systemc>

SC_MODULE(module_a)
{
    // A signal (channel) inside the module.
    sc_core::sc_signal<int> s;
    // A port used to write to an outside channel.
    sc_core::sc_port<sc_core::sc_signal_out_if<int>> p;
    SC_CTOR(module_a)
    {
        // A process to write to own channel.
        SC_THREAD(selfWrite);
        // A process to read from own channel.
        SC_THREAD(selfRead);
        // Triggered by value change on the channel.
        sensitive << s;
        dont_initialize();
        // A process to write to an outside channel.
        SC_THREAD(output);
    }

    void selfWrite()
    {
        // Init value.
        int val = 1;
        while (true) {
            // Write to own channel.
            s.write(val++);
            // Repeat after 1 s
            sc_core::wait(1, sc_core::SC_SEC);
        }
    }

    void selfRead()
    {
        while (true) {
            // Read from own channel.
            std::cout << sc_core::sc_time_stamp()
                      << ": reads from own channel, val=" << s.read()
                      << std::endl;
            // Receives from signal (static sensitivity).
            sc_core::wait();
        }
    }

    void output()
    {
        // Initialize value.
        int val = 1;
        while (true) {
            p->write(val++);
            // Write to an outside channel,
            // Calls the write method of the outside channel. p is a pointer.
            sc_core::wait(1, sc_core::SC_SEC);
        }
    }
};

// A module that reads from an outside channel.
SC_MODULE(module_b)
{
    // A port used to read from an outside channel.
    sc_core::sc_port<sc_core::sc_signal_in_if<int>> p;
    SC_CTOR(module_b)
    {
        // A process to read from an outside channel.
        SC_THREAD(input);
        // Triggered by value change on the channel.
        sensitive << p;
        // Prevent the scheduler from executing a thread or method process
        // during the initialization phase.
        dont_initialize();
    }

    void input()
    {
        while (true) {
            // Use port to read from the channel, like a pointer.
            std::cout << sc_core::sc_time_stamp() << ": reads from outside channel, val=" << p->read() << std::endl;
            // Wait one delta cycle.
            sc_core::wait();
        }
    }
};

int sc_main(int, char*[])
{
    // Instantiate module_b
    module_a mod_a("mod_a");
    // Instantiate module_b
    module_b mod_b("mod_b");
    // Declares a signal (channel) outside module_a and moudle_b
    sc_core::sc_signal<int> s;
    // Binds (connects) port p of mod_a to channel (signal) s.
    mod_a.p(s);
    // Binds port p of mod_b to channel s.
    mod_b.p(s);
    sc_core::sc_start(2, sc_core::SC_SEC);
    sc_core::sc_stop();
    return 0;
}
