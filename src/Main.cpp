#include <Constants.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]] char *arg[])
{
    Instrumentor::Get().beginSession("Main func");

    TimedBlock block("Main function");

    print_by_force("Hello World!\nThe largest number I can hold is: ", std::numeric_limits<int>::max());
    print_by_force("\nPress enter to continue...");

    std::cin.get();
}
