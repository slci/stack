#define CATCH_CONFIG_MAIN   // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp> // download from https://raw.githubusercontent.com/catchorg/Catch2/v2.x/single_include/catch2/catch.hpp

#include "stack_linked_list.hpp"

void testCharStack();
void testIntStack();

SCENARIO("Stack acts like as LIFO queue")
{
    stack::Stack<int> iStack1{};

    WHEN("User attempts to get top element from empty stack")
    {
        THEN("an exception is thrown")
        {
            CHECK_THROWS(iStack1.pop());
        }
    }

    WHEN("The stack is filled with 10 integers")
    {
        for (int i = 1; i <= 10; i++)
            iStack1.push(i);

        THEN("The top element in the stack shall be `10`")
        {
            int top;
            REQUIRE_NOTHROW(testIntStack());
            CHECK(top == 10);
        }
    }
}

void testCharStack()
{
    stack::Stack<char> charStack1;

    // wtf?! xD
    // for (int i = 65; i < 85; i++)
    //     charStack1.push(static_cast<char>(i));

    const auto alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (auto letter : alphabet)
        charStack1.push(letter);

    charStack1.push('a', 'b', 'c', 'd', 'e');
    charStack1.pop();
    charStack1.showAllNodes();

    std::cout << "items on stack: " << charStack1.countItemsOnStack() << "\n";
}

void testIntStack()
{
    stack::Stack<int> iStack1;

    for (int i = 1; i <= 10; i++)
        iStack1.push(i);

    iStack1.pop();
    iStack1.showAllNodes();

    std::cout << "items on stack: " << iStack1.countItemsOnStack() << "\n";
}