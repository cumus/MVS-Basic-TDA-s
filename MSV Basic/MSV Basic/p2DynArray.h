// ----------------------------------------------------
// Array that resizes dynamically   -------------------
// ----------------------------------------------------

#ifndef __P2DYNARRAY_H__
#define __P2DYNARRAY_H__

#include <cstdlib>
#include <assert.h>
#include "p2List.h"

#define DYN_ARRAY_BLOCK_SIZE 16

template<class VALUE>
class p2DynArray
{
private:

	VALUE*			data;
	unsigned int	mem_capacity;
	unsigned int	num_elements;

public:

	// Constructors
	p2DynArray() : mem_capacity(0), num_elements(0), data(NULL)
	{
		Alloc(DYN_ARRAY_BLOCK_SIZE);
	}

	p2DynArray(unsigned int capacity) : mem_capacity(0), num_elements(0), data(NULL)
	{
		Alloc(capacity);
	}

	// Destructor
	~p2DynArray()
	{
		delete[] data;
	}

	// Operators
	VALUE& operator[](unsigned int index)
	{
		assert(index < num_elements);
		return data[index];
	}

	const VALUE& operator[](unsigned int index) const
	{
		assert(index < num_elements);
		return data[index];
	}

	// Data Management
	void PushBack(const VALUE& element)
	{
		if(num_elements >= mem_capacity)
		{
			Alloc(mem_capacity + DYN_ARRAY_BLOCK_SIZE);
		}

		data[num_elements++] = element;
	}

	bool Pop(VALUE& value)
	{
		if(num_elements > 0)
		{
			value = data[--num_elements];
			return true;
		}
		return false;
	}

	void Clear()
	{
		num_elements = 0;
	}

	bool Insert(const VALUE& element, unsigned int position)
	{
		if(position > num_elements)
			return false;

		if(position == num_elements)
		{
			PushBack(element);
			return true;
		}

		if(num_elements + 1 > mem_capacity)
			Alloc(mem_capacity + DYN_ARRAY_BLOCK_SIZE);

		for(unsigned int i = num_elements; i > position; --i)
		{
			data[i] = data[i - 1];
		}

		data[position] = element;
		++num_elements;

		return true;
	}

	VALUE* At(unsigned int index)
	{
		VALUE* result = NULL;
		
		if(index < num_elements)
			return result = &data[index];
		
		return result;
	}

	const VALUE* At(unsigned int index) const
	{
		VALUE* result = NULL;

		if(index < num_elements)
			return result = &data[index];

		return result;
	}

	// Utils
	unsigned int GetCapacity() const
	{
		return mem_capacity;
	}

	unsigned int Count() const
	{
		return num_elements;
	}

private:
	
	// Private Utils
	void Alloc(unsigned int mem)
	{
		VALUE* tmp = data;

		mem_capacity = mem;
		data = new VALUE[mem_capacity];

		if(num_elements > mem_capacity)
			num_elements = mem_capacity;

		if(tmp != NULL)
		{
			for(unsigned int i = 0; i < num_elements; ++i)
				data[i] = tmp[i];

			delete[] tmp;
		}
	}


public:

	void Insert(const p2DynArray<VALUE> array, const unsigned int position)
	{
		// salir si la posicion no puede ser correcta
		if (position >= mem_capacity)
		{
			return;
		}

		// aumentar el tamaño del array si es necesario

		if (num_elements + array.num_elements > mem_capacity)
		{
			Alloc(num_elements + array.num_elements);
		}

		// pasar a partir de la posicion indicada data
		// copiar el contenido de array a la posicion

		for (unsigned int i = position; i < array.num_elements; i++)
		{
			data[i + array.num_elements] = data[i];
			data[i] = array[i - position];
		}
	}















	/*
	ARRANGEMENT METHODS
	*/


public:
	unsigned int check_quantity;

private:
	// dividir data e intercambiar 
	int divide(int start, int end)
	{
		VALUE pivot = data[start];
		int left = start;
		int right = end;

		// progresar hasta que los indices se crucen
		while (left < right)
		{
			// progresar por la izquierda
			while (data[right] > pivot) { check_quantity++;  right--; }
			// progresar por la derecha
			while ((left < right) && (data[left] <= pivot)) { check_quantity++; left++; }
			// si los indices no se solapan, cambiarlos
			if (left < right) { SWAP(left, right); }
			check_quantity++;
		}

		// pasar el pivote al principio
		SWAP(start, right);

		return right;
	}

	void recursive_quicksort(int start, int end)
	{
		if (start < end)
		{
			// encontrar el pivot
			int pivot = divide(start, end);
			// llamar a recursive_quicksort para los elementos antes y despues del pivot
			recursive_quicksort(start, pivot - 1);
			recursive_quicksort(pivot + 1, end);
		}
	}

public:
	int QuickSort()
	{
		// resetear VALUE p2DynArray::check_quantity
		check_quantity = 0;
		// llamar a la funcion con los margenes que queramos
		recursive_quicksort(0, num_elements - 1);
		// devolver la cantidad de comprobaciones (iterations)
		return check_quantity;
	}




	// cocktail
	unsigned int Bubble4()
	{
		check_quantity = 0;
		bool notSorted = true;
		while (notSorted)
		{
			notSorted = false;
			for (unsigned int i = 0; i < num_elements - 1; i++)
			{
				check_quantity++;
				if (data[i] > data[i + 1])
				{
					SWAP(i, i + 1);
					notSorted = true;
				}
			}

			if (!notSorted) { return iterations; }

			for (unsigned int i = num_elements - 1; i > num_elements - 1; i--)
			{
				check_quantity++;
				if (data[i] > data[i + 1])
				{
					SWAP(i, i + 1);
					notSorted = true;
				}
			}
		}
		return check_quantity;
	}
	
	unsigned int Cocktail1()
	{
		check_quantity = 0;

		for (unsigned int i = 0; i < num_elements - 1; i++)
		{
			for (unsigned int i2 = i + 1; i2 < num_elements; i2++)
			{
				check_quantity++;

				if (data[i] > data[i2]) { SWAP(i, i2); }
			}
		}
		return check_quantity;
	}

	unsigned int Bubble()
	{
		check_quantity = 0;
		bool finished = false;

		while (!finished)
		{
			finished = true;

			for (unsigned int i = 0; i < num_elements - 1; i++)
			{
				check_quantity++;

				if (data[i] > data[i + 1]) { SWAP(i, i + 1); finished = false; }
			}
		}
		return check_quantity;
	}

private:

	void SWAP(unsigned int i, unsigned int j)
	{
		if (i <= num_elements && j <= num_elements)
		{
			VALUE tmp = data[i];
			data[i] = data[j];
			data[j] = tmp;
		}
	}


public:
	unsigned int Combosort(const int gap_reduction)
	{
		int gap = num_elements;
		check_quantity = 0;
		bool finished = false;

		while (!finished)
		{
			finished = true;

			if (gap > 1) { gap--; }

			for (unsigned int i = 0; i + gap < num_elements; i++)
			{
				check_quantity++;
				if (data[i] > data[i + gap]) { SWAP(i, i + 1); finished = false; }
			}

		}
		return check_quantity;
	}






public:
	/*-------------------------------------------------------
	------------- APARTADO EXAMEN FINAL ---------------------
	-------------------------------------------------------*/

	p2DynArray<VALUE>& operator += (const p2DynArray<VALUE> array2)
	{
		// aumentar la capacidad si es necesario

		if (num_elements + array2.num_elements > mem_capacity)
		{
			Alloc(num_elements + array2.num_elements);
		}
		
		for (unsigned int i = 0; i < array2.num_elements; i++)
		{
			data[num_elements] = array2.data[i];
			num_elements++;
		}

		return *this;

	}



public:
	/*-------------------------------------------------------
	------------- APARTADO REEVALUACION ---------------------
	-------------------------------------------------------*/

	//VALUE*			data;
	//unsigned int	mem_capacity;
	//unsigned int	num_elements;

	void PrefixList(const p2List<VALUE> list)
	{
		// save list.Count so we just call the function once
		int  list_count = list.count();

		// if list is empty, we are done
		if (list_count != 0)
		{
			num_elements += list_count;

			// check if space is needed
			if (num_elements > mem_capacity)
			{
				Alloc(num_elements);
			}

			// move values to the right
			for (int i = num_elements; i > 0; i--)
			{
				data[i] = data[i - list_count];
			}

			// add values from list
			p2List_item<VALUE>* list_item = list.start;

			for (int i = 0; i < list_count; i++)
			{
				data[i] = list_item->data;
				list_item = list_item->next;
			}
		}
	}


	void AddToList(p2List<VALUE>* list)
	{
		for (unsigned int i = 0; i < num_elements; i++)
		{
			list->add(data[i]);
		}
	}


};

#endif // __P2DYNARRAY_H__