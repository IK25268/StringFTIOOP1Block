#include <iostream>
#include <cmath>
#include "String.hpp"

void String::initQuantRef()
{
	quantRef = new size_t;
	*(quantRef) = 1;
}

void String::decrQuantRef()
{
	(*(quantRef))--;
}

void String::addQuantRef(size_t* _quantRef)
{
	if (_quantRef != NULL)
	{
		quantRef = _quantRef;
		(*(quantRef))++;
	}
}

//size_t String::calcLen(const char* _str) const
//{
//	if (_str != NULL)
//	{
//		size_t len = 0;
//		while (*_str++)
//			++len;
//		return len;
//	}
//}

String::String()
{
	initQuantRef();
	cap = 10;
	len = 0;
	charArr = new char[cap];
	charArr[0] = '\0';
}

String::String(const char* _str)
{
	if (_str != NULL)
	{
		initQuantRef();
		len = strlen(_str);
		calcCapacity();
		charArr = new char[cap];
		//for (size_t i = 0; i < len; i++)
		//{
		//	charArr[i] = _str[i];
		//}
		memcpy(charArr, _str, len * sizeof(char));
		charArr[len] = '\0';
	}
}

String::String(const char* _str, size_t n)
{
	if (_str != NULL)
	{
		initQuantRef();
		len = n;
		calcCapacity();
		charArr = new char[cap];
		//for (size_t i = 0; i < len; i++)
		//{
		//	charArr[i] = _str[i];
		//}
		memcpy(charArr, _str, len * sizeof(char));
		charArr[len] = '\0';
	}
}

String::String(size_t n, char c)
{
	initQuantRef();
	len = n;
	calcCapacity();
	charArr = new char[cap];
	for (size_t i = 0; i < len; i++)
	{
		charArr[i] = c;
	}
	charArr[len] = '\0';
}

String::String(const String& _str)
{
	charArr = _str.charArr;
	cap = _str.cap;
	len = _str.len;
	addQuantRef(_str.quantRef);
}

String::String(const String& _str, size_t _pos, size_t _len)
{
	if ((_pos <= _str.len) && (_pos >= 0))
	{
		initQuantRef();
		if ((_len > _str.len - _pos) || (_len == npos)) _len = _str.len - _pos;
		len = _len;
		calcCapacity();
		charArr = new char[cap];
		//for (size_t i = 0; i < len; i++)
		//{
		//	charArr[i] = _str.charArr[_pos + i];
		//}
		memcpy(charArr, &(_str.charArr[_pos]), len * sizeof(char));
		charArr[_len] = '\0';
	}
	else
	{
		throw std::out_of_range("message");
	}
}

String:: ~String()
{
	if (*quantRef > 1)
	{
		decrQuantRef();
	}
	else
	{
		delete quantRef;
		delete[] charArr;
	}
}

size_t String::size() const
{
	return len;
}

size_t String::capacity() const
{
	return cap;
}

void String::reserve(size_t n)
{
	if (n > len)
	{
		char* bufer = new char[len];
		//for (int i = 0; i < len; i++)
		//{
		//	bufer[i] = charArr[i];
		//}
		memcpy(bufer, charArr, len * sizeof(char));
		delete[] charArr;
		charArr = new char[n];
		//for (int i = 0; i < len; i++)
		//{
		//	charArr[i] = bufer[i];
		//}
		memcpy(charArr, bufer, len * sizeof(char));
		charArr[len] = '\0';
		delete[] bufer;
		cap = n;
	}
}

void String::clear()
{
	if (*quantRef > 1)
	{
		decrQuantRef();
	}
	else
	{
		delete[]charArr;
	}
	len = 0;
	calcCapacity();
	charArr = new char[cap];
	charArr[0] = '\0';
}

bool String::empty() const
{
	return len == 0;
}

char& String::at(size_t _pos)
{
	if (_pos < len)
	{
		return charArr[_pos];
	}
	else
	{
		throw std::exception();
	}
}

const char& String::at(size_t _pos) const
{
	return _pos < len ? charArr[_pos] : throw std::exception();
}

char& String::operator[](size_t _pos)
{
	return at(_pos);
}

const char& String::operator[](size_t _pos) const
{
	return at(_pos);
}

char& String::back()
{
	if (len != 0) return charArr[len - 1];
	else return charArr[0];
}

const char& String::back() const
{
	if (len != 0) return charArr[len - 1];
	else return charArr[0];
}

char& String::front()
{
	return charArr[0];
}

const char& String::front() const
{
	return charArr[0];
}

String& String::operator+=(const String& _str)
{
	fullCopy();
	size_t bufLen = len;
	reallocStr(len + _str.len);
	len += _str.len;
	//for (size_t i = 0; i < (len - bufLen); i++)
	//{
	//	charArr[bufLen + i] = _str.charArr[i];
	//}
	memcpy(&(charArr[bufLen]), _str.charArr, (len - bufLen) * sizeof(char));
	charArr[len] = '\0';
	return *this;
}

String& String::operator+=(const char* _str)
{
	if (_str != NULL)
	{
		fullCopy();
		size_t bufLen = len;
		len += strlen(_str);
		reallocStr(len);
		//for (size_t i = bufLen; i < len; i++)
		//{
		//	charArr[i] = _str[i - bufLen];
		//}
		memcpy(&(charArr[bufLen]), _str, (len - bufLen) * sizeof(char));
		charArr[len] = '\0';
		return *this;
	}
}

String& String::operator+=(char c)
{
	fullCopy();
	len++;
	reallocStr(len);
	charArr[len - 1] = c;
	charArr[len] = '\0';
	return *this;
}

String& String::operator=(const String& _str)
{
	if (*quantRef > 1)
	{
		decrQuantRef();
	}
	else
	{
		delete[] charArr;
	}
	addQuantRef(_str.quantRef);
	charArr = _str.charArr;
	return *this;
}

String& String::operator=(const char* _str)
{
	if (_str != NULL)
	{
		if (*quantRef > 1)
		{
			decrQuantRef();
		}
		else
		{
			delete[] charArr;
		}
		len = strlen(_str);
		calcCapacity();
		charArr = new char[cap];
		for (size_t i = 0; i < len; i++)
		{
			charArr[i] = _str[i];
		}
		memcpy(charArr, _str, len * sizeof(char));
		charArr[len] = '\0';
		return *this;
	}
}

String& String::insert(size_t _pos, const String& _str)
{
	if (_str.len != 0)
	{
		if ((_pos <= len) && (_pos >= 0))
		{
			fullCopy();
			reallocStr(len + _str.len);
			char* buferSecond = NULL;
			if ((len - _pos) > 0)
			{
				buferSecond = new char[len - _pos];
				//for (size_t i = 0; i < len - _pos; i++)
				//{
				//	buferSecond[i] = charArr[i+_pos];
				//}
				memcpy(buferSecond, &(charArr[_pos]), (len - _pos) * sizeof(char));
			}
			//for (size_t i = 0; i < _str.len; i++)
			//{
			//	charArr[i+_pos] = _str[i];
			//}
			memcpy(&(charArr[_pos]), _str.charArr, _str.len * sizeof(char));
			if (buferSecond != NULL)
			{
				//for (size_t i = _pos + _str.len; i < len + _str.len; i++)
				//{
				//	charArr[i] = buferSecond[i - _pos - _str.len];
				//}
				memcpy(&(charArr[_pos + _str.len]), buferSecond, (len - _pos) * sizeof(char));
			}
			len += _str.len;
			charArr[len] = '\0';
			delete[]buferSecond;
		}
		else
		{
			throw std::out_of_range("message");
		}
	}
	return *this;
}

String& String::insert(size_t _pos, const char* _str)
{
	if (_str != NULL)
	{
		if ((_pos <= len) && (_pos >= 0))
		{
			fullCopy();
			size_t strLen = strlen(_str);
			reallocStr(len + strLen);
			char* buferSecond = NULL;
			if ((len - _pos) > 0)
			{
				buferSecond = new char[len - _pos];
				//for (size_t i = _pos; i < len; i++)
				//{
				//	buferSecond[i - _pos] = charArr[i];
				//}
				memcpy(buferSecond, &(charArr[_pos]), (len - _pos) * sizeof(char));
			}
			//for (size_t i = _pos; i < _pos + strLen; i++)
			//{
			//	charArr[i] = _str[i - _pos];
			//}
			memcpy(&(charArr[_pos]), _str, strLen * sizeof(char));
			if (buferSecond != NULL)
			{
				//for (size_t i = _pos + strLen; i < len + strLen; i++)
				//{
				//	charArr[i] = buferSecond[i - _pos - strLen];
				//}
				memcpy(&(charArr[_pos + strLen]), buferSecond, (len - _pos) * sizeof(char));
			}
			len += strLen;
			charArr[len] = '\0';
			delete[]buferSecond;
		}
		else
		{
			throw std::out_of_range("message");
		}
	}
	return *this;
}

String& String::erase(size_t _pos, size_t _len)
{
	if ((_pos <= len) && (_pos >= 0))
	{
		fullCopy();
		if (_len < 0) _len = 0;
		if ((_len > len - _pos) || (_len == npos)) _len = len - _pos;
		//for (size_t i = 0; i < len - _pos - _len; i++)
		//{
		//	charArr[i + _pos] = charArr[i + _pos + _len];
		//}
		memcpy(&(charArr[_pos]), &(charArr[_pos + _len]), (len - _pos - _len) * sizeof(char));
		len -= _len;
		charArr[len] = '\0';
	}
	else
	{
		throw std::out_of_range("message");
	}
	return *this;
}

String& String::replace(size_t _pos, size_t _len, const String& _str)
{
	erase(_pos, _len);
	insert(_pos, _str);
	return *this;
}

String& String::replace(size_t _pos, size_t _len, const char* _str)
{
	erase(_pos, _len);
	insert(_pos, _str);
	return *this;
}

String& String::replace(size_t _pos, size_t _len, size_t n, char c)
{
	erase(_pos, _len);
	char* bufStr = new char[n + 1];
	for (size_t i = 0; i < n; i++)
	{
		bufStr[i] = c;
	}
	bufStr[n] = '\0';
	insert(_pos, bufStr);
	delete[]bufStr;
	return *this;
}

void String::swap(String& _str)
{
	std::swap(_str.charArr, charArr);
	std::swap(_str.len, len);
	std::swap(_str.cap, cap);
	std::swap(_str.quantRef, quantRef);
}

const char* String::data()
{
	return this->charArr;
}

size_t String::find(const String& _str, size_t _pos) const
{
	if ((_pos >= 0) && (_pos < len))
	{
		int count = 0;
		for (size_t i = _pos; i < len; i++)
		{
			if (charArr[i] != _str.charArr[count]) count = 0;
			if (charArr[i] == _str.charArr[count]) count++;
			if (count == _str.len) return (i - count + 1);
		}
		return npos;
	}
	else
	{
		return npos;
	}
}

size_t String::find(const char* _str, size_t _pos) const
{
	if (_str != NULL)
	{
		if ((_pos >= 0) && (_pos < len))
		{
			size_t strLen = strlen(_str);
			int count = 0;
			for (size_t i = _pos; i < len; i++)
			{
				if (charArr[i] != _str[count]) count = 0;
				if (charArr[i] == _str[count]) count++;
				if (count == strLen) return (i - count + 1);
			}
			return npos;
		}
		else
		{
			return npos;
		}
	}
}

size_t String::find(char c, size_t _pos) const
{
	if ((_pos >= 0) && (_pos < len))
	{
		for (size_t i = _pos; i < len; i++)
		{
			if (charArr[i] == c) return i;
		}
		return npos;
	}
	else
	{
		return npos;
	}
}

String String::substr(size_t _pos, size_t _len)
{
	if ((_pos >= 0) && (_pos < len))
	{
		fullCopy();
		if ((_len > len - _pos) || (_len == npos)) _len = len - _pos;
		char* bufer = new char[_len];
		//for (size_t i = 0; i < _len; i++)
		//{
		//	bufer[i] = charArr[i+_pos];
		//}
		memcpy(bufer, &(charArr[_pos]), _len * sizeof(char));
		delete[]charArr;
		len = _len;
		calcCapacity();
		charArr = new char[cap];
		//for (size_t i = 0; i < len; i++)
		//{
		//	charArr[i] = bufer[i];
		//}
		memcpy(charArr, bufer, len * sizeof(char));
		charArr[len] = '\0';
		delete[]bufer;
	}
	else
	{
		throw std::out_of_range("message");
	}
	return *this;
}

int String::compare(const String& _str) const
{
	for (size_t i = 0; (i < len) || (i < _str.len); i++)
	{
		if (i == _str.len) return 1;
		if (i == len) return -1;
		if (charArr[i] > _str.charArr[i]) return 1;
		if (charArr[i] < _str.charArr[i]) return -1;
	}
	return 0;
}

void String::fullCopy()
{
	if (*(quantRef) > 1)
	{
		decrQuantRef();
		initQuantRef();
		char* buferPtr = charArr;
		charArr = new char[cap];
		//for (size_t i = 0; i < len; i++)
		//{
		//	charArr[i] = buferPtr[i];
		//}
		memcpy(charArr, buferPtr, (len) * sizeof(char));
		charArr[len] = '\0';
	}
}

void String::calcCapacity(size_t _len)
{
	cap = 10 * (_len / 10 + 1);
}

void String::calcCapacity()
{
	cap = 10 * (len / 10 + 1);
}

void String::reallocStr(size_t _newLen)
{
	size_t buferCap = cap;
	calcCapacity(_newLen);
	if (cap != buferCap)
	{
		char* bufer = new char[len];
		//for (int i = 0; i < len; i++)
		//{
		//	bufer[i] = charArr[i];
		//}
		memcpy(bufer, charArr, (len) * sizeof(char));
		delete[] charArr;
		charArr = new char[cap];
		//for (int i = 0; i < len; i++)
		//{
		//	charArr[i] = bufer[i];
		//}
		memcpy(charArr, bufer, (len) * sizeof(char));
		charArr[len] = '\0';
		delete[] bufer;
	}
}

size_t String::countRef() const
{
	if (quantRef != NULL) return *quantRef;
	return NULL;
}