
#ifndef __Queue_H__
#define __Queue_H__

template <class DoubleNodeDataTYPE>struct DoubleNode
{
	DoubleNodeDataTYPE data;
	DoubleNode* previous;
	DoubleNode* next;

	inline DoubleNode() : data(NULL), next(NULL), previous(NULL) {}
	inline DoubleNode(const DoubleNodeDataTYPE& item) : data(item), next(NULL), previous(NULL) {}
	inline DoubleNode(const DoubleNode& node) : data(node.item), next(node.next), previous(node.previous) {}
	void operator = (const DoubleNodeDataTYPE& item) { data = item; }

	~DoubleNode(){ delete data; }
};

template <class QueueTYPE> class DoubleNodedList
{
private:

	DoubleNode<QueueTYPE>* init;
	DoubleNode<QueueTYPE>* last;
	unsigned int num_elements;

public:

	inline DoubleNodedList(){ init = last = NULL; num_elements = 0; }

	~DoubleNodedList(){ clear(); }

	DoubleNode<QueueTYPE>* getStart(){ return init; }
	DoubleNode<QueueTYPE>* getLast(){ return last; }
	unsigned int Count(){ return num_elements; }

	void push(const QueueTYPE& data)
	{
		//DoubleNode<QueueTYPE> tmp(data);
		//DoubleNode<QueueTYPE>* node = &tmp;

		DoubleNode<QueueTYPE>* node = new DoubleNode<QueueTYPE>(data);

		if (init == NULL)
		{
			last = init = node;
		}
		else
		{
			last->next = node;
			node->previous = last;
			last = node;
		}
		num_elements++;
	}

	void push(DoubleNode<QueueTYPE>* node)
	{
		node->next = NULL;

		if (init == NULL)
		{
			node->previous = NULL;
			last = init = node;
		}
		else
		{
			node->previous = last;
			last->next = node;
			last = node;
		}

		num_elements++;
	}

	void clear()
	{
		if (init == NULL)
		{
			DoubleNode<QueueTYPE>* p_data;
			DoubleNode<QueueTYPE>* p_next;
			p_data = init;

			while (p_data != NULL)
			{
				p_next = p_data->next;
				delete p_data;
				p_data = p_next;
			}

			init = last = NULL;
			num_elements = 0;
		}
	}

	void ReduceTo(const unsigned int quantity)
	{
		if (quantity < num_elements)
		{
			last = init;
			for (unsigned int i = 1; i < quantity; i++){ last = last->next; }
			last->next = NULL;
			num_elements = quantity;
		}
	}

	void ClearTo(const unsigned int quantity)
	{
		if (quantity == 0) { clear(); }

		else if (quantity < num_elements)
		{
			DoubleNode<QueueTYPE>* p_data;
			DoubleNode<QueueTYPE>* p_next;
			p_data = init;

			for (unsigned int i = 0; i < quantity; i++){ p_data = p_data->next; }

			while (p_data != NULL)
			{
				p_next = p_data->next;
				delete p_data;
				p_data = p_next;
			}

			last = init;
			for (unsigned int i = 1; i < quantity; i++){ last = last->next; }
			last->next = NULL;
			num_elements = quantity;
		}
	}
	
	bool at(unsigned int index, QueueTYPE& data) const
	{
		DoubleNode<QueueTYPE>* tmp = init;

		for (unsigned int i = 0; i < index && tmp != NULL; ++i) { tmp = tmp->next; }

		if (tmp != NULL)
		{
			data = tmp->data;
			return true;
		}

		return false;
	}

};

#endif