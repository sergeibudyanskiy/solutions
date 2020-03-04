#pragma once
#include <iostream>
#include <exception>

class StringException : public std::exception
{
public:
	explicit StringException(const char*) noexcept;
	~StringException();
	char const* what() const;
};

class String
{
public:
	String();
	String(int);
	String(const String&);
	String(char*);
	String(const char*);
	~String();

	int size() const;

	char* begin() const;
	char* end() const;

	//operator const char* () const;
	char& operator[](int) const throw(std::out_of_range);
	String& operator= (const String&);
	
	friend bool operator == (const String&, const String&);
	friend bool operator < (const String&, const String&);
	friend const String operator+ (const String&, const String&);
	friend std::ostream& operator<< (std::ostream&, const String&);
private:
	char* data;
	int length;
};
