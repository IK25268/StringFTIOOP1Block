#include <iostream>
#include <cmath>
#include "String.hpp"
using namespace std;

String::String()
{
	this->quantRef = new size_t;
	*(this->quantRef) = 1;
	this->cap = 10;
	this->len = 0;
	this->charArr = new char[this->cap];
	this->charArr[0] = '\0';
}

String::String(const char* str)
{
	this->quantRef = new size_t;
	*(this->quantRef) = 1;
	this->len = 0;
	while (*str++)
		++this->len;
	str = str - (this->len + 1);
	this->calcCapacity();
	this->charArr = new char[this->cap];
	for (size_t i = 0; i < this->len; i++)
	{
		this->charArr[i] = str[i];
	}
	this->charArr[this->len] = '\0';
}

String::String(const char* str, size_t n)
{
	this->quantRef = new size_t;
	*(this->quantRef) = 1;
	this->len = n;
	this->calcCapacity();
	this->charArr = new char[this->cap];
	for (size_t i = 0; i < this->len; i++)
	{
		this->charArr[i] = str[i];
	}
	this->charArr[this->len] = '\0';
}

String::String(size_t n, char c)
{
	this->quantRef = new size_t;
	*(this->quantRef) = 1;
	this->len = n;
	this->calcCapacity();
	this->charArr = new char[this->cap];
	for (size_t i = 0; i < this->len; i++)
	{
		this->charArr[i] = c;
	}
	this->charArr[this->len] = '\0';
}

String::String(const String& str)
{
	this->charArr = str.charArr;
	this->cap = str.cap;
	this->len = str.len;
	this->quantRef = str.quantRef;
	(*(this->quantRef))++;
}

String::String(const String& str, size_t pos, size_t len)
{
	if ((pos <= str.len) && (pos >= 0))
	{
		if ((len > str.len - pos) || (len == npos)) len = str.len - pos;
		this->len = len;
		calcCapacity();
		this->charArr = new char[this->cap];
		for (size_t i = 0; i < this->len; i++)
		{
			this->charArr[i] = str.charArr[pos + i];
		}
		this->charArr[len] = '\0';
	}
	else
	{
		throw out_of_range("message");
	}
}

String:: ~String()
{
	if (*this->quantRef > 1)
	{
		(*(this->quantRef))--;
	}
	else
	{
		delete this->quantRef;
		delete[] this->charArr;
	}
}

size_t String::size()
{
	return this->len;
}

size_t String::capacity()
{
	return this->cap;
}

void String::reserve(size_t n)
{
	if (n > this->len)
	{
		char* bufer = new char[this->len];
		for (int i = 0; i < this->len; i++)
		{
			bufer[i] = this->charArr[i];
		}
		delete[] this->charArr;
		this->charArr = new char[n];
		for (int i = 0; i < this->len; i++)
		{
			this->charArr[i] = bufer[i];
		}
		this->charArr[this->len] = '\0';
		delete[] bufer;
		this->cap = n;
	}
}

void String::clear()
{
	if (*this->quantRef > 1)
	{
		(*(this->quantRef))--;
	}
	else
	{
		delete[]this->charArr;
	}
	this->len = 0;
	this->calcCapacity();
	this->charArr = new char[this->cap];
	this->charArr[0] = '\0';
}

bool String::empty()
{
	return this->len == 0;
}

char& String::at(size_t pos)
{
	this->fullCopy();
	return pos < this->len ? this->charArr[pos] : throw exception();
}

const char& String::at(size_t pos) const
{
	return pos < this->len ? this->charArr[pos] : throw exception();
}

char& String::operator[](size_t pos)
{
	this->fullCopy();
	return pos < this->len ? this->charArr[pos] : throw exception();
}

const char& String::operator[](size_t pos) const
{
	return pos < this->len ? this->charArr[pos] : throw exception();
}

char& String::back()
{
	this->fullCopy();
	return this->charArr[this->len - 1];
}

const char& String::back() const
{
	return this->charArr[this->len - 1];
}

char& String::front()
{
	this->fullCopy();
	return this->charArr[0];
}

const char& String::front() const
{
	return this->charArr[0];
}

String& String::operator+=(const String& str)
{
	this->fullCopy();
	size_t bufLen = this->len;
	this->reallocStr(this->len + str.len);
	this->len += str.len;
	for (size_t i = bufLen; i < (this->len); i++)
	{
		this->charArr[i] = str.charArr[i - bufLen];
	}
	this->charArr[this->len] = '\0';
	return *this;
}

String& String::operator+=(const char* str)
{
	this->fullCopy();
	size_t bufLen = this->len;
	while (*str++)
		++this->len;
	str = str - (this->len - bufLen + 1);
	this->reallocStr(this->len);
	for (size_t i = bufLen; i < this->len; i++)
	{
		this->charArr[i] = str[i - bufLen];
	}
	this->charArr[this->len] = '\0';
	return *this;
}

String& String::operator+=(char c)
{
	this->fullCopy();
	this->len++;
	this->reallocStr(this->len);
	this->charArr[this->len - 1] = c;
	this->charArr[this->len] = '\0';
	return *this;
}

String& String::operator=(const String& str)
{
	if (*this->quantRef > 1)
	{
		(*(this->quantRef))--;
	}
	else
	{
		delete[] this->charArr;
	}
	this->quantRef = str.quantRef;
	(*(this->quantRef))++;
	this->charArr = str.charArr;
	return *this;
}

String& String::operator=(const char* str)
{
	if (*this->quantRef > 1)
	{
		(*(this->quantRef))--;
	}
	else
	{
		delete[] this->charArr;
	}
	this->len = 0;
	while (*str++)
		++this->len;
	str = str - (this->len + 1);
	this->calcCapacity();
	this->charArr = new char[this->cap];
	for (size_t i = 0; i < this->len; i++)
	{
		this->charArr[i] = str[i];
	}
	this->charArr[this->len] = '\0';
	return *this;
}

String& String::insert(size_t pos, const String& str)
{
	if ((pos <= this->len) && (pos >= 0))
	{
		this->fullCopy();
		this->reallocStr(this->len + str.len);
		char* buferSecond = NULL;
		if ((this->len - pos) > 0)
		{
			buferSecond = new char[this->len - pos];
			for (size_t i = pos; i < this->len; i++)
			{
				buferSecond[i - pos] = this->charArr[i];
			}
		}
		for (size_t i = pos; i < pos + str.len; i++)
		{
			this->charArr[i] = str[i - pos];
		}
		if (buferSecond != NULL)
		{
			for (size_t i = pos + str.len; i < this->len + str.len; i++)
			{
				this->charArr[i] = buferSecond[i - pos - str.len];
			}
		}
		this->len += str.len;
		this->charArr[this->len] = '\0';
		delete[]buferSecond;
	}
	else
	{
		throw out_of_range("message");
	}
	return *this;
}

String& String::insert(size_t pos, const char* str)
{
	if ((pos <= this->len) && (pos >= 0))
	{
		this->fullCopy();
		size_t strLen = 0;
		while (*str++)
			++strLen;
		str = str - (strLen + 1);
		this->reallocStr(this->len + strLen);
		char* buferSecond = NULL;
		if ((this->len - pos) > 0)
		{
			buferSecond = new char[this->len - pos];
			for (size_t i = pos; i < this->len; i++)
			{
				buferSecond[i - pos] = this->charArr[i];
			}
		}
		for (size_t i = pos; i < pos + strLen; i++)
		{
			this->charArr[i] = str[i - pos];
		}
		if (buferSecond != NULL)
		{
			for (size_t i = pos + strLen; i < this->len + strLen; i++)
			{
				this->charArr[i] = buferSecond[i - pos - strLen];
			}
		}
		this->len += strLen;
		this->charArr[this->len] = '\0';
		delete[]buferSecond;
	}
	else
	{
		throw out_of_range("message");
	}
	return *this;
}

String& String::erase(size_t pos, size_t len)
{
	if ((pos <= this->len) && (pos >= 0))
	{
		this->fullCopy();
		if (len < 0) len = 0;
		if ((len > this->len - pos) || (len == npos)) len = this->len - pos;
		for (size_t i = pos + len; i < this->len; i++)
		{
			this->charArr[i - len] = this->charArr[i];
		}
		this->len -= len;
		this->charArr[this->len] = '\0';
		this->reallocStr(this->len);
	}
	else
	{
		throw out_of_range("message");
	}
	return *this;
}

String& String::replace(size_t pos, size_t len, const String& str)
{
	this->erase(pos, len);
	this->insert(pos, str);
	return *this;
}

String& String::replace(size_t pos, size_t len, const char* str)
{
	this->erase(pos, len);
	this->insert(pos, str);
	return *this;
}

String& String::replace(size_t pos, size_t len, size_t n, char c)
{
	this->erase(pos, len);
	char* bufStr = new char[n + 1];
	for (size_t i = 0; i < n; i++)
	{
		bufStr[i] = c;
	}
	bufStr[n] = '\0';
	this->insert(pos, bufStr);
	delete[]bufStr;
	return *this;
}

void String::swap(String& str)
{
	this->fullCopy();
	str.fullCopy();
	char* bufer = str.charArr;
	str.charArr = this->charArr;
	this->charArr = bufer;
	size_t buferLen = str.len;
	str.len = this->len;
	this->len = buferLen;
}

const char* String::data()
{
	return this->charArr;
}

size_t String::find(const String& str, size_t pos)
{
	if ((pos >= 0) && (pos < this->len))
	{
		int count = 0;
		for (size_t i = pos; i < this->len; i++)
		{
			if (this->charArr[i] != str.charArr[count]) count = 0;
			if (this->charArr[i] == str.charArr[count]) count++;
			if (count == str.len) return (i - count + 1);
		}
		return npos;
	}
	else
	{
		return npos;
	}
}

size_t String::find(const char* str, size_t pos)
{
	if ((pos >= 0) && (pos < this->len))
	{
		size_t strLen = 0;
		while (*str++)
			++strLen;
		str = str - (strLen + 1);
		int count = 0;
		for (size_t i = pos; i < this->len; i++)
		{
			if (this->charArr[i] != str[count]) count = 0;
			if (this->charArr[i] == str[count]) count++;
			if (count == strLen) return (i - count + 1);
		}
		return npos;
	}
	else
	{
		return npos;
	}
}

size_t String::find(char c, size_t pos)
{
	if ((pos >= 0) && (pos < this->len))
	{
		for (size_t i = pos; i < this->len; i++)
		{
			if (this->charArr[i] == c) return i;
		}
		return npos;
	}
	else
	{
		return npos;
	}
}

String String::substr(size_t pos, size_t len)
{
	if ((pos >= 0) && (pos < this->len))
	{
		this->fullCopy();
		if ((len > this->len - pos) || (len == npos)) len = this->len - pos;
		char* bufer = new char[len];
		for (size_t i = pos; i < pos + len; i++)
		{
			bufer[i - pos] = this->charArr[i];
		}
		delete[]this->charArr;
		this->len = len;
		this->calcCapacity();
		this->charArr = new char[this->cap];
		for (size_t i = 0; i < this->len; i++)
		{
			this->charArr[i] = bufer[i];
		}
		this->charArr[this->len] = '\0';
		delete[]bufer;
	}
	else
	{
		throw out_of_range("message");
	}
	return *this;
}

int String::compare(const String& str)
{
	for (size_t i = 0; (i < this->len) || (i < str.len); i++)
	{
		if (i == str.len) return 1;
		if (i == this->len) return -1;
		if (this->charArr[i] > str.charArr[i]) return 1;
		if (this->charArr[i] < str.charArr[i]) return -1;
	}
	return 0;
}

void String::fullCopy()
{
	if (*(this->quantRef) > 1)
	{
		(*(this->quantRef))--;
		this->quantRef = new size_t;
		*(this->quantRef) = 1;
		char* buferPtr = this->charArr;
		this->charArr = new char[this->cap];
		for (size_t i = 0; i < this->len; i++)
		{
			this->charArr[i] = buferPtr[i];
		}
		this->charArr[this->len] = '\0';
	}
}

void String::calcCapacity(size_t len)
{
	this->cap = 10 * (len / 10 + 1);
}

void String::calcCapacity()
{
	this->cap = 10 * (this->len / 10 + 1);
}

void String::reallocStr(size_t newLen)
{
	size_t buferCap = this->cap;
	calcCapacity(newLen);
	if (this->cap != buferCap)
	{
		char* bufer = new char[this->len];
		for (int i = 0; i < this->len; i++)
		{
			bufer[i] = this->charArr[i];
		}
		delete[] this->charArr;
		this->charArr = new char[this->cap];
		for (int i = 0; i < this->len; i++)
		{
			this->charArr[i] = bufer[i];
		}
		this->charArr[this->len] = '\0';
		delete[] bufer;
	}
}

size_t String::countRef()
{
	return *this->quantRef;
}