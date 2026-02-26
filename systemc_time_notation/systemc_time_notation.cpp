#include <systemc>

int sc_main(int, char*[])
{

    // Set the time resolution. Must be done in the elaboration phase.
    sc_core::sc_set_time_resolution(1, sc_core::SC_FS);
    // Concept of default time unit is a deprecated feature. Now, a global time
    // is avoided. Time should be specified using SC_TIME(value, UNIT).
    sc_core::sc_set_default_time_unit(1, sc_core::SC_FS);
    // Start the simulation.
    sc_core::sc_start();
    std::cout << "Time resolution = " << sc_core::sc_get_time_resolution() << std::endl;
    std::cout << "Time unit       = " << sc_core::sc_get_default_time_unit() << std::endl;
    std::cout << "1 SEC =     " << sc_core::sc_time(1, sc_core::SC_SEC).to_default_time_units() << " SEC" << std::endl;
    std::cout << "1 MS =     " << sc_core::sc_time(1, sc_core::SC_MS).to_default_time_units() << " SEC" << std::endl;
    std::cout << "1 US =     " << sc_core::sc_time(1, sc_core::SC_US).to_default_time_units() << " SEC" << std::endl;
    std::cout << "1 NS =     " << sc_core::sc_time(1, sc_core::SC_NS).to_default_time_units() << " SEC" << std::endl;
    std::cout << "1 PS =     " << sc_core::sc_time(1, sc_core::SC_PS).to_default_time_units() << " SEC" << std::endl;
    std::cout << "1 FS =     " << sc_core::sc_time(1, sc_core::SC_FS).to_default_time_units() << " SEC" << std::endl;
    // Stop the simulation.
    sc_core::sc_stop();
    return 0;
}
