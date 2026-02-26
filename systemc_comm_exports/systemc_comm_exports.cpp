#include <systemc>

SC_MODULE(module_a)
{
    // An export for other modules to connect.
    sc_core::sc_export<sc_core::sc_signal<int>> p;
    // A signal (channel) inside the module. If not using export,
    // the channel need to be defined outside module_a.
    sc_core::sc_signal<int> s;

    // Constructor.
    SC_CTOR(module_a)
    {
        // Bind an export to an internal channel.
        p(s);
        // Register processes.
        // A process to write to an internal channel.
        SC_THREAD(writer);
    }

    // Define writer.
    void writer()
    {
        // Init value.
        int val = 1;
        while (true) {
            // Write to an internal channel.
            s.write(val++);
            sc_core::wait(1, sc_core::SC_SEC);
        }
    }
};

// Define a module that reads from an export.
SC_MODULE(module_b)
{
    // A port used to read from an export of another module.
    sc_core::sc_port<sc_core::sc_signal_in_if<int>> p;
    SC_CTOR(module_b)
    {
        // A process to read from an outside channel.
        SC_THREAD(reader);
        // Sensitive to value change on the channel.
        sensitive << p;
        dont_initialize();
    }

    // Define reader.
    void reader()
    {
        while (true) {
            // Use ex"port" to read from the channel, like a pointer.
            std::cout << sc_core::sc_time_stamp() << ": reads from outside channel, val=" << p->read() << std::endl;
            // Receives from port.
            sc_core::wait();
        }
    }
};

int sc_main(int, char*[])
{
    // Instantiate mod_a.
    module_a mod_a("mod_a");
    // Instantiate mod_b.
    module_b mod_b("mod_b");
    // Connect mod_b's port to mod_a's export.
    // No need to declare a channel outside mod_a and mod_b.
    mod_b.p(mod_a.p);
    sc_core::sc_start(10, sc_core::SC_SEC);
    sc_core::sc_stop();
    return 0;
}
