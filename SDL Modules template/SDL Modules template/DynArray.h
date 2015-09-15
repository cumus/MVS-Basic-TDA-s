#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

#define BLOCK_SIZE 8

template<class DynArrayTYPE> class DynArray
{
private:
	DynArrayTYPE* data;
	unsigned int capacity;
	unsigned int num_elements;

	void Alloc(unsigned int capacity)
	{
		DynArrayTYPE* tmp = data;
		this->capacity = capacity;
		data = new DynArrayTYPE[capacity];

		if (tmp != NULL)
		{
			for (unsigned int i = 0; i < num_elements; ++i) { data[i] = tmp[i]; }
			delete[] tmp;
		}
	}

public:
	DynArray() : num_elements(0), data(NULL) { Alloc(BLOCK_SIZE); }
	DynArray(unsigned int capacity) : num_elements(0), data(NULL) { Alloc(capacity); }

	~DynArray(){ delete[] data; }


	// Data Management
	void push_back(const DynArrayTYPE& element)
	{
		if (num_elements >= capacity){ Alloc(capacity + BLOCK_SIZE); }
		data[num_elements++] = element;
	}

	void Pop()
	{
		if(num_elements > 0){ num_elements--; }
	}

	void clear() { num_elements = 0; }

	DynArrayTYPE* at(unsigned int index)
	{
		if (index < num_elements){ return &data[index]; }
		return NULL;
	}

	const DynArrayTYPE* at(unsigned int index) const
	{
		if (index < num_elements){ return &data[index]; }
		return NULL;
	}

	void Delete_Element_At(const unsigned int index)
	{
		if (index < num_elements)
		{
			num_elements--;

			delete data[index];
			data[index] = NULL;

			for (unsigned int i = index; i < num_elements; i++)
			{
				data[i] = data[i + 1];
			}
			data[num_elements] = NULL;
		}
	}

	void Reduce_To(unsigned int quantity)
	{
		if (quantity < num_elements)
		{
			num_elements = quantity;
		}
	}

	void ClearAll()
	{
		num_elements = 0;
		delete[] data;
		data = NULL;
		Alloc(BLOCK_SIZE);
	}

	// Utils
	void Init(){ num_elements = 0; data = NULL; Alloc(BLOCK_SIZE); }
	unsigned int size() const { return capacity; }
 	unsigned int Count() const { return num_elements; }
	bool empty(){ return num_elements == 0; }

};

#endif