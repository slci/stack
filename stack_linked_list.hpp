#include <iostream>
#include <stdexcept>
#include <cstdint>

// TODO validate stack frame addresses
// CCTOR
// MCTOR

namespace stack
{
    struct value_tag {};
    struct address_tag {};

    /**
     * @brief Trivial Stack frame.
     * @param next pointer to next frame
     * @param value value stored in frame
     */
    template <typename T>
    struct StackFrame
    {
        StackFrame<T> *next;
        T value;
    };

    template <typename T>
    struct Stack
    {
        using Frame = StackFrame<T>;

        Stack();
        ~Stack();
        Stack(Stack const &cp);                 // TODO deep-copy
        Stack &operator=(Stack const &cp);      // TODO deep-copy
        Stack(Stack &&mv);                      // TODO mv semantics
        Stack &operator=(Stack &&mv);           // TODO mv semantics 

        void showAllNodes();
        std::uint32_t countItemsOnStack();

        /**
         * @brief push elem on stack
         * @param value to be pushed on stack
         */
        void push(T arg);

        /**
         * @brief push elem on stack
         * @param value to be pushed
         * @param args unbounds number of arguments to be pushed
         */
        template <typename F, typename... Values>
        void push(F firstValue, Values... args);

        /**
         * @brief functions that uses tag dispatching
         * @return value of type T
         */
        T top(Frame *val, value_tag);

        /**
         * @brief functions that uses tag dispatching
         * @return address of type T
         */
        T *top(Frame *val, address_tag);

        /**
         * @brief pops top value from stack
         * @return copy of top value
         */
        T pop();

        /**
         * @brief This is redundant function, mainly created for gaining experience
         *  while working with tag dispatching, which returns either value or address of type T.
         * @param firstAddress addres of deleted stack frame
         * @param secondAddress usually nullptr
         * @return bool comparishment
         */
        bool validatePop(T *firstAddress, T *secondAddress = nullptr);

    private:
        T helperType;
        Frame *head;
        Frame *tail;
        Frame *temp;
    };

} // stack

template <typename T>
stack::Stack<T>::Stack() // RAII OK
    : head{nullptr}, tail{nullptr}, temp{nullptr}
{
    std::cout << "Stack created. \n";
}

template <typename T> // RAII NOT OK
stack::Stack<T>::~Stack()
{
    delete head;
    // delete tail; // TODO when 1 item left tails points to head, doubled free
    delete temp;
    std::cout << "Stack destructor \n";
}

template <typename T> // TODO
stack::Stack<T>::Stack(Stack const &ref)
{
    // head = new Frame;
    // tail = head;
}

template <typename T> // TODO deep-copy implementation
stack::Stack<T> &stack::Stack<T>::operator=(Stack const &ref)
{
}

template <typename T>
std::uint32_t stack::Stack<T>::countItemsOnStack()
{
    unsigned long itemsOnStack{0};

    temp = head;

    while (temp)
    {
        temp = temp->next;
        itemsOnStack++;
    }

    temp = nullptr;
    return itemsOnStack;
}

template <typename T>
void stack::Stack<T>::push(T arg) // RAII - ok
{

    if (!std::is_same<decltype(arg), decltype(helperType)>::value)
        throw std::runtime_error{"Types differ. Consider creating stack for one type. "};

    if (head == nullptr)
    {
        head = new Frame;
        tail = head;
        head->value = arg;
    }
    else
    {
        Frame *tmp = new Frame;
        tail->next = tmp;
        tail = tail->next;
        tail->value = arg;
    }
}

template <typename T>
template <typename F, typename... Values>
void stack::Stack<T>::push(F firstValue, Values... args) // OK
{
    push(firstValue);
    push(args...);
}

template <typename T>
T stack::Stack<T>::top(Frame *frame, value_tag)
{
    if (frame == nullptr)
        throw std::runtime_error{"Stack is empty. "};

    temp = head;

    while (temp->next)
    {
        temp = temp->next;
    }

    T result = temp->value;
    temp = nullptr;

    return result;
}

template <typename T> // RAII OK
T *stack::Stack<T>::top(Frame *frame, address_tag)
{
    std::cout << "Frame address: " << frame << "\n";

    return frame;
}

template <typename T>
T stack::Stack<T>::pop()
{
    T result;
    T *firstAddress;

    value_tag valueTag;
    address_tag addressTag;

    if (head == nullptr)
    {
        throw std::runtime_error{"Stack is empty. "};
    }
    else if (head->next == nullptr)
    {
        if (top(head, valueTag) == head->value)
        {
            result = head->value;

            head = nullptr;
            return result;
        }
    }
    else
    {
        temp = head;

        while (temp->next->next != nullptr)
        {
            temp = temp->next;
        }

        tail = temp;

        if (top(head, valueTag) == tail->next->value)
        {
            result = tail->next->value;
            delete tail->next;
            tail->next = nullptr;

            firstAddress = reinterpret_cast<T *>(tail->next);
        }
        temp = nullptr;
    }

    validatePop(firstAddress, nullptr);
    return result;
}

template <typename T>
bool stack::Stack<T>::validatePop(T *firstAddress, T *secondAddress)
{
    std::cout << "first address:  " << firstAddress << "\n";
    std::cout << "second address: " << secondAddress << "\n";

    if (firstAddress != secondAddress)
        throw std::runtime_error{"Value wasn't poped correct from stack. "};

    delete firstAddress;

    return true;
}

/**
 * @brief helper function during developing stage
 */
template <typename T>
void stack::Stack<T>::showAllNodes()
{
    int cnt{0};

    temp = head;

    while (temp)
    {
        cnt += 1;
        std::cout << "data: " << cnt << " - " << temp->value << "\n";
        temp = temp->next;
    }

    temp = nullptr;
}
