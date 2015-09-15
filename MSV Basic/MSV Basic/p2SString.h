#ifndef __p2SString_H__
#define __p2SString_H__

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "p2Stack.h"

#define TMP_STRING_SIZE	4096

class p2SString
{
private:

	char* str;
	unsigned int size;

public:

	// Constructors
	p2SString()
	{
		Alloc(1);
		Clear();
	}

	p2SString(unsigned int size)
	{
		if(size > 0)
			Alloc(size);
		else
			Alloc(1);

		Clear();
	}

	p2SString(const p2SString& string)
	{
		Alloc(string.size);
		strcpy_s(str, size, string.str);
	}

	p2SString(const char *format, ...)
	{
		size = 0;

		if(format != NULL)
		{
			static char tmp[TMP_STRING_SIZE];
			static va_list  ap;

			// Construct the string from variable arguments
			va_start(ap, format);
			int res = vsprintf_s(tmp, TMP_STRING_SIZE, format, ap);
			va_end(ap);

			if(res > 0)
			{
				Alloc(res + 1);
				strcpy_s(str, size, tmp);
			}
		}

		if(size == 0)
		{
			Alloc(1);
			Clear();
		}
	}
	
	// Destructor
	virtual ~p2SString()
	{
		if(str != NULL)
			delete[] str;
	}

	// Operators
	bool operator== (const p2SString& string) const
	{
		return strcmp(string.str, str) == 0;
	}

	bool operator== (const char* string) const
	{
		if(string != NULL)
			return strcmp(string, str) == 0;
		return false;
	}

	bool operator!= (const p2SString& string) const
	{
		return strcmp(string.str, str) != 0;
	}

	bool operator!= (const char* string) const
	{
		if(string != NULL)
			return strcmp(string, str) != 0;
		return true;
	}
	
	const p2SString& operator= (const p2SString& string)
	{
		if(string.Length() + 1 > size)
		{
			delete[] str;
			Alloc(string.Length() + 1);
		}
		else
			Clear();

		strcpy_s(str, size, string.str);

		return(*this);
	}

	const p2SString& operator= (const char* string)
	{
		if(string != NULL)
		{
			if(strlen(string) + 1 > size)
			{
				delete[] str;
				Alloc(strlen(string)+1);
			}
			else
				Clear();

			strcpy_s(str, size, string);
		}
		else
		{
			Clear();
		}

		return(*this);
	}
	
	const p2SString& operator+= (const p2SString& string)
	{
		unsigned int need_size = string.Length() + Length() + 1;

		if(need_size > size)
		{
			char* tmp = str;
			Alloc(need_size);
			strcpy_s(str, size, tmp);
			delete[] tmp;
		}

		strcat_s(str, size, string.str);

		return(*this);
	}

	const p2SString& operator+= (const char* string)
	{
		if(string != NULL)
		{
			unsigned int need_size = strlen(string) + Length() + 1;

			if(need_size > size)
			{
				char* tmp = str;
				Alloc(need_size);
				strcpy_s(str, size, tmp);
				delete[] tmp;
			}

			strcat_s(str, size, string);
		}

		return(*this);
	}

	// Utils
	unsigned int Length() const
	{
		return strlen(str);
	}

	void Clear()
	{
		str[0] = '\0';
	}

	const char* GetString() const
	{
		return str;
	}

	unsigned int GetCapacity() const
	{
		return size;
	}

private:

	void Alloc(unsigned int requiered_memory)
	{
		char* tmp = new char[size];

		for (unsigned int i = 0; i < size; i++)
		{
			tmp[i] = str[i];
		}

		size = requiered_memory;

		
		str = new char[size];

		for (unsigned int i = 0; i < size; i++)
		{
			str[i] = '\0';
		}

		for (unsigned int i = 0; i < strlen(tmp); i++)
		{
			str[i] = tmp[i];
		}

		delete[] tmp;

	}




public:
	/*-------------------------------------------------------
	------------- APARTADO EXAMEN FINAL ---------------------
	-------------------------------------------------------*/

	void Cut(const unsigned int init, const unsigned int last)
	{
		// comprobar que los valores que nos entran son los correctos
		if (init <= size || last <= size || init != last)
		{
			if (last > init)
			{
				int quantity = last - init + 1;

				for (int i = 0; i < quantity; i++)
				{
					str[init + i] = str[last - i];
				}
			}

			Alloc(init + 1);

		}
	}

public:
	/*-------------------------------------------------------
	------------- APARTADO REEVALUACION ---------------------
	-------------------------------------------------------*/

	unsigned int DoubleVocals()
	{
		unsigned int vocal_count = 0;

		p2Stack<int> stack;

		// recorremos el string y nos guardamos en el stack la posicion de las vocales
		for (int i = 0; i < (int)size; i++)
		{
			switch (str[i])
			{
			case 'a': stack.Push(i);  break;
			case 'A': stack.Push(i);  break;
			case 'e': stack.Push(i);  break;
			case 'E': stack.Push(i);  break;
			case 'i': stack.Push(i);  break;
			case 'I': stack.Push(i);  break;
			case 'o': stack.Push(i);  break;
			case 'O': stack.Push(i);  break;
			case 'u': stack.Push(i);  break;
			case 'U': stack.Push(i);  break;
			}
		}

		vocal_count = stack.Count();

		if (vocal_count > 0)
		{
			// anadimos espacio si es necesario
			if (vocal_count + strlen(str) > size)
			{
				Alloc(size + vocal_count);
			}

			int pos;
			while (stack.Pop(pos))
			{
				// desplazamos todos los caracteres a la derecha de cada vocal para dar sitio a la vocal nueva que se repite
				for (int i = size; i > pos; i--)
				{
					str[i] = str[i - 1];
				}
			}
		}

		return vocal_count;
	}








};

#endif // __p2SString_H__