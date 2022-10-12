#include <Constants.hpp>

int main([[maybe_unused]] int, [[maybe_unused]] char **)
{
    Instrumentor::Get().beginSession("Main func");

    TimedBlock block("Main function");

    print_by_force("Hello World!\nThe largest number I can hold is: ", std::numeric_limits<int>::max());
    print_by_force("\nPress enter to continue...");

    std::cin.get();
}
