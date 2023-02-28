#include <Constants.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{

    Instrumentor::Get().beginSession("Main func");

    TimedBlock block("Main function");

    print_by_force("Hello World!\nThe largest number I can hold is: ", std::numeric_limits<int>::max(), "\n");

    int counter;
    print_by_force("Program Name Is:", argv[0]);
    if (argc == 1)
        print_by_force("\nNo Extra Command Line Argument Passed Other Than Program Name");
    if (argc >= 2)
    {
        print_by_force("\nNumber Of Arguments Passed: ", argc);
        print_by_force("\n----Following Are The Command Line Arguments Passed----");
        for (counter = 0; counter < argc; counter++)
            print_by_force("\nargv[", counter, "]: ", argv[counter]);
    }

    print_by_force("\nPress enter to continue...");

    std::cin.get();
}
