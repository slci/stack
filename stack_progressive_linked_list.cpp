#include <iostream>

namespace lzli
{
	template <typename T>
	class Stack
	{
		struct Buffer
		{
			T* data;
			Buffer* prev, * next;
			size_t size, capacity;

			Buffer(size_t capacity, Buffer* prev)
				: size(0), capacity(capacity), data(new T[capacity]), prev(prev), next(nullptr) {}

			~Buffer()
			{
				delete[] data;
			}

			T& top()
			{
				if (size)
					return data[size - 1];
				else
					return prev->top();
			}

			void push(const T& elem)
			{

				data[size] = elem;
				size++;
			}

			void pop()
			{
				if (size > 0)
					size--;
			}
		};

		Buffer* buffer;
	public:
		Stack()
			:buffer(nullptr) {}

		T& top()
		{
			return buffer->top();
		}

		void push(const T & elem)
		{
			if (buffer)
			{
				if (buffer->size < buffer->capacity)
					buffer->push(elem);
				else
				{
					buffer = new Buffer(buffer->capacity * 2, buffer);
					buffer->prev->next = buffer;
					buffer->push(elem);
					std::cout << buffer->capacity << std::endl;
				}
			}
			else
			{
				buffer = new Buffer(1, nullptr);
				buffer->push(elem);
			}
		}

		void pop()
		{
			if (buffer->size > 0)
				buffer->pop();
			else
			{
				buffer = buffer->prev;
				delete buffer->next;
				buffer->pop();
				std::cout << buffer->size << std::endl;
			}
		}
	};
}