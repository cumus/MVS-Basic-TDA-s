#ifndef __p2List_H__
#define __p2List_H__

#include "p2Defs.h"
#include "p2Assert.h"

/**
* Contains items from double linked list
*/
template<class tdata>
struct p2List_item
{
	tdata                 data;
	p2List_item<tdata>*   next;
	p2List_item<tdata>*   prev;

	inline p2List_item(const tdata& _data)
	{
		data = _data;
		next = prev = NULL;
	}

	~p2List_item()
	{}
};

/**
* Manages a double linked list
*/
template<class tdata>
class p2List
{

public:

	p2List_item<tdata>*   start;
	p2List_item<tdata>*   end;

private:

	unsigned int  size;

public:

	/**
	* Constructor
	*/
	inline p2List()
	{
		start = end = NULL;
		size = 0;
	}

	/**
	* Destructor
	*/
	~p2List()
	{
		clear();
	}

	/**
	* Get Size
	*/
	unsigned int count() const
	{
		return size;
	}

	/**
	* Add new item
	*/
	unsigned int add(const tdata& item)
	{
		p2List_item<tdata>*   p_data_item;
		p_data_item = new p2List_item < tdata >(item);

		if (start == NULL)
		{
			start = end = p_data_item;
		}
		else
		{
			p_data_item->prev = end;
			end->next = p_data_item;
			end = p_data_item;
		}

		return(++size);
	}

	/**
	* Deletes an item from the list
	*/
	bool del(p2List_item<tdata>* item)
	{
		if (item == NULL)
		{
			return (false);
		}

		// Now reconstruct the list
		if (item->prev != NULL)
		{
			item->prev->next = item->next;

			if (item->next != NULL)
			{
				item->next->prev = item->prev;
			}
			else
			{
				end = item->prev;
			}
		}
		else
		{
			if (item->next)
			{
				item->next->prev = NULL;
				start = item->next;
			}
			else
			{
				start = end = NULL;
			}
		}

		RELEASE(item);
		--size;
		return(true);
	}

	/**
	* Destroy and free all mem
	*/
	void clear()
	{
		p2List_item<tdata>*   p_data;
		p2List_item<tdata>*   p_next;
		p_data = start;

		while (p_data != NULL)
		{
			p_next = p_data->next;
			RELEASE(p_data);
			p_data = p_next;
		}

		start = end = NULL;
		size = 0;
	}

	/**
	* read / write operator access directly to a position in the list
	
	tdata& operator  [](const unsigned int index)
	{
		long                  pos;
		p2List_item<tdata>*   p_item;
		pos = 0;
		p_item = start;

		while (p_item != NULL)
		{
			if (pos == index)
			{
				break;
			}

			++pos;
			p_item = p_item->next;
		}

		ASSERT(p_item);

		return(p_item->data);
	}*/

	/**
	* returns the first apperance of data as index (-1 if not found)
	*/
	int find(const tdata& data)
	{
		p2List_item<tdata>* tmp = start;
		int index = 0;

		while (tmp != NULL)
		{
			if (tmp->data == data)
				return(index);

			++index;
			tmp = tmp->next;
		}
		return (-1);
	}



	/*
	-----------------------------------------------------------------------------------------------------------
	*/




public:
	tdata& operator [](const unsigned int index)
	{
		p2List_item<tdata>* tmp = start;

		if (index < size)
		{
			for (unsigned int i = 0; i < index; i++)
			{
				tmp = tmp->next;
			}
		}

		ASSERT(tmp);

		return tmp->data;
	}

	const tdata& operator [](const unsigned int index) const
	{
		p2List_item<tdata>* tmp = start;

		if (index < size)
		{
			for (unsigned int i = 0; i < index; i++)
			{
				tmp = tmp->next;
			}
		}

		ASSERT(tmp);

		return tmp->data;
	}



	unsigned int Cocktail_Data()
	{
		unsigned int check_quantity = 0;

		p2List_item<tdata>* node_1 = NULL;
		p2List_item<tdata>* node_2 = NULL;

		for (node_1 = start; node_1 != NULL; node_1 = node_1->next)
		{
			for (node_2 = node_1; node_2 != NULL; node_2 = node_2->next)
			{
				check_quantity++;

				if (node_1->data > node_2->data) { SWAP_Data(node_1, node_2); }
			}
		}
		return check_quantity;
	}


	unsigned int Cocktail_Nodes()
	{
		unsigned int check_quantity = 0;

		p2List_item<tdata>* node_1 = NULL;
		p2List_item<tdata>* node_2 = NULL;

		for (node_1 = start; node_1 != NULL; node_1 = node_1->next)
		{
			for (node_2 = node_1; node_2 != NULL; node_2 = node_2->next)
			{
				check_quantity++;

				if (node_1->data > node_2->data) { SWAP_Nodes(node_1, node_2); }
			}
		}

		for (node_1 = start; node_1->prev != NULL; node_1 = node_1->prev){}
		start = node_1;

		for (node_2 = end; node_2->next != NULL; node_2 = node_2->next){}
		end = node_2;

		return check_quantity;
	}


	void FLIP()
	{
		p2List_item<tdata>* node_1 = start;
		p2List_item<tdata>* node_2 = end;

		for (unsigned int i = 0; node_1 != node_2; i++)
		{
			SWAP_Nodes(node_1, node_2);

			if (i % 2 == 0)
			{
				node_1 = node_1->prev, node_2 = node_2->next;
			}
			else
			{
				node_1 = node_1->next, node_2 = node_2->prev;
			}
			
		}

		p2List_item<tdata>* tmp = end;
		end = start;
		start = tmp;
	}
	



private:
	void SWAP_Data(p2List_item<tdata>* node_1, p2List_item<tdata>* node_2)
	{
		if (node_1 != NULL && node_2 != NULL)
		{
			tdata tmp = node_1->data;
			node_1->data = node_2->data;
			node_2->data = tmp;
		}
	}

	void SWAP_Nodes___(p2List_item<tdata>* node_1, p2List_item<tdata>* node_2)
	{
		if (node_1 != NULL && node_2 != NULL)
		{
			p2List_item<tdata>* tmp = NULL;

			tmp = node_1->prev;
			node_1->prev = node_2->prev;
			node_2->prev = tmp;

			if (node_1->prev != NULL) { node_1->prev->next = node_1; }
			if (node_2->prev != NULL) { node_2->prev->next = node_2; }

			tmp = node_1->next;
			node_1->next = node_2->next;
			node_2->next = tmp;

			if (node_1->next != NULL) { node_1->next->prev = node_1; }
			if (node_2->next != NULL) { node_2->next->prev = node_2; }
		}
	}

	void SWAP(unsigned int i, unsigned int j)
	{
		if (i <= size && j <= size)
		{
			p2List_item<tdata>* node_1 = nodeAt(i);
			p2List_item<tdata>* node_2 = nodeAt(i2);

			if (node_1 != NULL and node_2 != NULL)
			{
				tdata tmp = node_1->data;
				node_1->data = node_2->data;
				node_2->data = tmp;
			}
		}
	}

	p2List_item<tdata>* nodeAt(const unsigned int index)
	{
		p2List_item<tdata>* return_value = NULL;

		if (index < size)
		{
			return_value = start;

			for (unsigned int i = 0; i < index; i++)
			{
				return_value = return_value->next;
			}
		}

		return return_value;
	}









public:
	/*-------------------------------------------------------
	------------- APARTADO EXAMEN FINAL ---------------------
	-------------------------------------------------------*/

	void InsertAfter(const unsigned int index, const p2List<tdata> list)
	{
		if (index > size || list.start == NULL)
		{
			return;
		}

		p2List_item<tdata>* node = nodeAt(index);
		p2List_item<tdata>* next = node->next;

		node->next = list.start;
		list.end->next = next;

		if (index == size)
		{
			end = list.end;
		}

	}

public:
	/*-------------------------------------------------------
	------------- APARTADO REEVALUACION ---------------------
	-------------------------------------------------------*/

	void Flip()
	{
		p2List_item<tdata>* node_1 = start;
		p2List_item<tdata>* node_2 = end;

		// Caso lista con elementos pares
		if (size % 2 == 0)
		{
			for (unsigned int i = 0; node_1->next != node_2 && node_1->prev != node_2; i++)
			{
				SWAP_Nodes(node_1, node_2);

				if (i % 2 == 0)
				{
					node_1 = node_1->prev, node_2 = node_2->next;
				}
				else
				{
					node_1 = node_1->next, node_2 = node_2->prev;
				}
			}

			// SWAP los dos del medio que nos faltan
			SWAP_Nodes(node_1, node_2);
		}
		// Caso lista con elementos impares
		else
		{
			for (unsigned int i = 0; node_1 != node_2; i++)
			{
				SWAP_Nodes(node_1, node_2);

				if (i % 2 == 0)
				{
					node_1 = node_1->prev, node_2 = node_2->next;
				}
				else
				{
					node_1 = node_1->next, node_2 = node_2->prev;
				}
			}
		}

		// cambiar los valores de start y end
		p2List_item<tdata>* tmp = end;
		end = start;
		start = tmp;
	}

	void SWAP_Nodes(p2List_item<tdata>* node_1, p2List_item<tdata>* node_2)
	{
		if (node_1 != NULL && node_2 != NULL)
		{
			p2List_item<tdata>* tmp = NULL;

			tmp = node_1->prev;
			node_1->prev = node_2->prev;
			node_2->prev = tmp;

			if (node_1->prev != NULL) { node_1->prev->next = node_1; }
			if (node_2->prev != NULL) { node_2->prev->next = node_2; }

			tmp = node_1->next;
			node_1->next = node_2->next;
			node_2->next = tmp;

			if (node_1->next != NULL) { node_1->next->prev = node_1; }
			if (node_2->next != NULL) { node_2->next->prev = node_2; }
		}
	}

};
#endif /*__p2List_H__*/