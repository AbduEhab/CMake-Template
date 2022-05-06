#include <Constants.h>

void print(const char *message)
{
    std::cout << message << std::endl;
}

int main(int, char **)
{
    TimedBlock block("main");
    print("Hello, world!\n");
}
