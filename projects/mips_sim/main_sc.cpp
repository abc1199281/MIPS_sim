#include <systemc.h>

// A simple module to say hello
SC_MODULE(HelloWorld) {
    SC_CTOR(HelloWorld) {
        // Constructor
        SC_THREAD(say_hello);
    }

    void say_hello() {
        cout << "Hello World, SystemC!" << endl;
    }
};

// Top-level function
int sc_main(int argc, char* argv[]) {
    HelloWorld hello("HELLO");
    sc_start(1, SC_NS); // Run simulation for 1 nanosecond
    return 0;
}
