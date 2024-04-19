#include <Constants.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{

    Instrumentor::Get().beginSession("Main func");

    TimedBlock block("Main function");

    print_by_force("Hello World!");
    print_by_force("The largest number I can hold is: ", std::numeric_limits<int>::max());

    int counter;
    print_by_force("Program name is: ", argv[0]);
    if (argc == 1)
        print_by_force("No Extra Command Line Argument Passed Other Than Program Name");
    if (argc >= 2)
    {
        print_by_force("Number Of Arguments Passed: ", argc);
        print_by_force("----Following Are The Command Line Arguments Passed----");
        for (counter = 0; counter < argc; counter++)
            print_by_force("argv[", counter, "]: ", argv[counter]);
    }

}
