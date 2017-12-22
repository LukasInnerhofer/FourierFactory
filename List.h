#ifndef LIST_H
#define LIST_H

#include <vector>

template<typename T>
class List : public std::vector<T>
{
public:
	T getMax()
	{
		T max = 0;
		for (T element : *this)
		{
			if (element > max)
			{
				max = element;
			}
		}
	}
};

#endif // LIST_H