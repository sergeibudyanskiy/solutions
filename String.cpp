#include "String.h"

StringException::StringException(const char* str) noexcept : std::exception(str)
{}

StringException::~StringException()
{}

char const* StringException::what() const
{
	std::cout << "String error: ";
	return std::exception::what();
}

String::String() : data(nullptr), length(0)
{}

String::String(int i)
{
	int lnt = 1;

	while (i >= pow(10, lnt))
	{
		lnt++;
	}
	length = lnt;
	data = new char[length + 1];
	data[length] = '\0';
	_itoa_s(i, data, length + 1, 10);
}

String::String(const String& s)
{
	length = s.length;
	data = new char[length + 1];
	data[length] = '\0';
	strcpy_s(data, length + 1, s.data);
}

String::String(char* str)
{
	length = strlen(str) + 1;
	data = new char[length + 1];
	data[length] = '\0';
	strcpy_s(data, length + 1, str);
}

String::String(const char* str) : length(strlen(str))
{
	data = new char[length + 1];
	data[length] = '\0';
	strcpy_s(data, length + 1, str);
}

String::~String()
{
	delete[] data;
}

int String::size() const
{
	return length;
}

char* String::begin() const
{
	return data;
}

char* String::end() const
{
	return data + length;
}

//String::operator const char* () const
//{
//	return data;
//}

char& String::operator[](int i) const throw(StringException)
{
	try
	{
		if (i < length) return *(data + i);
		/*else throw(StringException(
			String("Out of range\n\tString: ") +
			data + String(" - length not longer that ") + String(length) +
			String("\n\tYou tried to get element by index: ") + String(i)
		));*/
	}
	catch (StringException & oor)
	{
		std::cout << oor.what() << std::endl;
	}
}

String& String::operator= (const String& s)
{
	if (data != nullptr) delete[] data;
	length = s.length;
	data = new char[length + 1];
	data[length] = '\0';
	strcpy_s(data, length + 1, s.data);

	return *this;
}

bool operator < (const String& l, const String& r)
{
	int less = (l.length < r.length) ? l.length : r.length;
	for (int i = 0; i < less; i++)
	{
		if (l[i] < r[i]) return true;
		if (l[i] == r[i]) continue;
		else return false;
	}
	return false;
}

bool operator == (const String& l, const String& r)
{
	if (l.length == r.length)
	{
		for (int i = 0; i < l.length; i++)
		{
			if (l[i] == r[i]) continue;
			if (l[i] != r[i]) return false;
		}
		return true;
	}
	return false;
}

const String operator+ (const String& l, const String& r)
{
	int newLength = l.length + r.length;
	char* result = new char[newLength + 1];
	result[newLength] = '\0';
	strcpy_s(result, newLength + 1, l.data);
	strcat_s(result, newLength + 1, r.data);
	const String stringResult(result);
	delete[] result;
	return stringResult;
}


std::ostream& operator<< (std::ostream& out, const String& s)
{
	return out << s.data;
}
