#include <iostream>
using namespace std;

#pragma warning(disable: 4996)

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif


class String
{
private:
	char* m_cp;
public:

	/*constructor/destroyer section*/

	String(const char* _cp = "");
	String(char* _cp);
	String(const String& _CS);
	String(String&& _CS) noexcept;
	virtual ~String();


	/*operator section*/

	void operator+=(const String& _CS);

	String operator+(const String& _CS);

	void operator=(const String& _CS);
	void operator=(String&& _CS) noexcept;

	/*inline section*/
	bool operator==(const String& _CS)
	{
		return !strcmp(m_cp, _CS.m_cp);
	}

	/*friend bool operator==(const String& _CS1,const String& _CS2)
	{
		return !strcmp(_CS1.m_cp, _CS2.m_cp);
	}*/
	friend ostream& operator<<(ostream& os, const String& _CS)
	{
		os << _CS.m_cp;
		return os;
	}
};

int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif  _DEBUG

	String S1("Baby");
	cout << S1<<endl;

	String S2("Baby");
	cout <<S2<< endl;
	cout << (S1 == S2) << endl;

	S1 += S2;
	cout << S1<<endl;

	String S3=S1 + S2;
	cout << S3 << endl;

	String S4 = String("KING");
	cout << S4 << endl;

	S4 = String("QUEEEN");
	cout << S4 << endl;
	return 0;
}

String::String(const char* _cp)
{
	m_cp = new char[strlen(_cp)+1];

	strcpy_s(m_cp,strlen(_cp)+1, _cp);
}

String::String(char* _cp)
{
	m_cp = _cp;
}

String::String(const String& _CS)
{
	if (m_cp == nullptr)
	{
		m_cp = new char[strlen(_CS.m_cp) + 1];

		strcpy_s(m_cp, strlen(_CS.m_cp) + 1, _CS.m_cp);
	}
	else
	{
		delete[] m_cp;

		m_cp = new char[strlen(_CS.m_cp) + 1];

		strcpy_s(m_cp, strlen(_CS.m_cp) + 1, _CS.m_cp);
	}
}

String::String(String&& _CS) noexcept
{
	if (m_cp == nullptr)
	{
		m_cp = _CS.m_cp;

		_CS.m_cp = nullptr;
	}
	else
	{
		delete[] m_cp;
		m_cp = _CS.m_cp;

		_CS.m_cp = nullptr;
	}
}

void String::operator+=(const String& _CS)
{
	auto len = strlen(m_cp)+ strlen(_CS.m_cp)+1;
	auto Temp = new char[len];
	strcpy(Temp, m_cp);
	strcat(Temp, _CS.m_cp);

	if (m_cp == nullptr)
	{
		m_cp = new char[strlen(Temp) + 1];
		strcpy(m_cp, Temp);
	}
	else
	{
		delete[] m_cp;
		m_cp = nullptr;
		m_cp = new char[strlen(Temp) + 1];
		strcpy(m_cp, Temp);
	}

	delete[] Temp;
}

String String::operator+(const String& _CS)
{
	auto len = strlen(m_cp) + strlen(_CS.m_cp) + 1;
	auto Temp = new char[len];
	strcpy(Temp, m_cp);
	strcat(Temp, _CS.m_cp);

	return String(Temp);
}

void String::operator=(const String& _CS)
{
	if (_CS.m_cp == nullptr)
		return;

	if (m_cp == nullptr)
	{
		m_cp = new char[strlen(_CS.m_cp) + 1];

		strcpy_s(m_cp, strlen(_CS.m_cp) + 1, _CS.m_cp);
	}
	else
	{
		delete[] m_cp;

		m_cp = new char[strlen(_CS.m_cp) + 1];

		strcpy_s(m_cp, strlen(_CS.m_cp) + 1, _CS.m_cp);
	}
	
}

void String::operator=(String&& _CS) noexcept
{
	if (_CS.m_cp == nullptr)
		return;

	if (m_cp == nullptr)
	{
		m_cp = _CS.m_cp;

		_CS.m_cp = nullptr;
	}
	else
	{
		delete[] m_cp;
		m_cp = _CS.m_cp;

		_CS.m_cp = nullptr;
	}
}

String::~String()
{
	if (m_cp != nullptr);
		delete[] m_cp;
}
