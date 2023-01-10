#include "stack_linked_list.hpp"

void testCharStack();
void testInstStack();

int main()
{
    try
    {
        testInstStack();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void testCharStack()
{
    stack::Stack<char> charStack1;

    for (int i = 65; i < 85; i++)
        charStack1.push(static_cast<char>(i));

    charStack1.push('a', 'b', 'c', 'd', 'e');
    charStack1.pop();
    charStack1.showAllNodes();

    std::cout << "items on stack: " << charStack1.countItemsOnStack() << "\n";
}

void testInstStack()
{
    stack::Stack<int> iStack1;

    for (int i = 1; i <= 10; i++)
        iStack1.push(i);

    iStack1.pop();
    iStack1.showAllNodes();

    std::cout << "items on stack: " << iStack1.countItemsOnStack() << "\n";
}