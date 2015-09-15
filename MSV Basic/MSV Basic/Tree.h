
#include "p2List.h"
#include "p2Stack.h"
#include <assert.h>

#ifndef __Tree__
#define __Tree__

template <class TreeNodeTYPE>
class TreeNode
{
public:

	TreeNodeTYPE data;
	TreeNode* parent;
	p2List<TreeNode*> childs;

protected:

	TreeNode<TreeNodeTYPE>* _Find(const TreeNodeTYPE& father)
	{
		if (father == data) // if father is data, father is found
		{
			return this;
		}

		TreeNode<TreeNodeTYPE>* found_father = NULL;

		for (p2List_item<TreeNodeTYPE*>* children = childs.start; children != NULL; children = children->next) // search for all sons
		{
			found_father = childen->_Find(father);
			
			if (found_father != NULL) // if found_father is not null, found_father has been found
			{
				return found_father;
			}
		}

		return NULL; // if node has no sons, return NULL
	}


public:

	// ----------------------- Constructors -----------------------

	TreeNode() : parent(NULL) {}

	TreeNode(const TreeNodeTYPE& data) : parent(NULL), data(data) {}

	TreeNode(const TreeNodeTYPE& data, const TreeNode& parent) : parent(parent), data(data) {}


	// ----------------------- Destructor -----------------------

	~TreeNode()
	{
		Clear();
	}


	// ----------------------- Data Management Functions -----------------------

	void Append_Child(TreeNode* node)
	{
		assert(node);

		node->parent = this; // set parent's node
		childs.add(node); // append to childs list
	}

	void Clear()
	{
		delete childs;
		delete data;
	}

	// Recursive Path Journey

	void _PreorderRecursive(p2List<TreeNodeTYPE> list)
	{
		if (data != NULL)
		{
			list.add(data);

			for (p2List_item<TreeNodeTYPE*>* children = childs.start; children != NULL; children = children->next)
			{
				children->data._PreorderRecursive(list);
			}
		}
	}

	void _InorderRecursive(p2List<TreeNodeTYPE> list)
	{
		if (data != NULL)
		{
			unsigned int max = childs.count();

			if (max > 0)
			{
				p2List_item<TreeNodeTYPE*>* children = childs.start;

				max /= 2;

				for (unsigned int i = 0; i < max; i++, children = children->next)
				{
					children->data._InorderRecursive(list);
				}

				list.add(data);

				for (; children != NULL; children = children->next)
				{
					children->data._InorderRecursive(list);
				}
			}
		}
	}


	void _PostorderRecursive(p2List<TreeNodeTYPE> list)
	{
		if (data != NULL)
		{
			for (p2List_item<TreeNodeTYPE*>* children = childs.start; children != NULL; children = children->next)
			{
				children->data._PostorderRecursive(list);
			}

			list.add(data);
		}
	}


	// ----------------------- Utility Functions -----------------------

	TreeNode<TreeNodeTYPE>* Find(const TreeNodeTYPE& father)
	{
		assert(father);
		
		return _Find(father);
	}

	// -------------- CalcAdditionPreorderRecursive --------------

	void _CalcAdditionPreorderRecursive(int suma)
	{
		if (data != NULL)
		{
			suma += data;

			for (p2List_item<TreeNodeTYPE*>* children = childs.start; children != NULL; children = children->next)
			{
				children->data._CalcAdditionPreorderRecursive(suma);
			}
		}
	}



};




template <class TreeTYPE>
class Tree
{
private:

	TreeNode<TreeTYPE> root;

public:

	// ----------------------- Constructor -----------------------

	Tree(const TreeTYPE& data)
	{
		assert(data);

		root.data = data;
	}


	// ----------------------- Destructor -----------------------

	virtual ~Tree()
	{
		root.Clear();
	}


	// ----------------------- Data Management Functions -----------------------

	bool Add(const TreeTYPE& data, const TreeTYPE& father = NULL)
	{
		assert(data);

		if (father == NULL || root.data == father) // if father is root or no father specified, no need to search
		{
			root.Append_Child(new TreeNode<TreeTYPE>(data, root));
			return true;
		}
		else
		{
			// find where to add the new node
			TreeNode<TreeTYPE>* parent = root.Find(father);

			if (parent != NULL)
			{
				// append new child to tree
				parent->Append_Child(new TreeNode<TreeTYPE>(data, father));
				return true;
			}
		}

		return false; // father not found
	}


	
	void Clear(TreeNode& node)
	{
		if (node == NULL || node.parent == NULL) // Clear tree completely
		{
			root.Clear();
		}
		else // Clear indicated node only
		{
			node.parent->childs.del(node); // delete node from parent's child list
		}
	}
	


	void PreorderRecursive(p2List<TreeTYPE> list)
	{
		assert(list);

		root._PreorderRecursive(list);
	}

	void InorderRecursive(p2List<TreeTYPE> list)
	{
		assert(list);

		root._InorderRecursive(list);
	}

	void PostorderRecursive(p2List<TreeTYPE> list)
	{
		assert(list);

		root._PostorderRecursive(list);
	}

	void PreorderIterative(p2List<TreeTYPE> list)
	{
		assert(list);

		p2Stack<TreeNode<TreeTYPE>*> stack;
		TreeNode<TreeTYPE>* node;
		p2List_item<TreeTYPE*>* child;

		stack.Push(root);

		while (stack.Pop(node)) // while stack is not empty, pop next node
		{
			list.add(node->data); // add node to list

			for (child = node->childs.end; child != NULL; child = child->prev)
			{
				stack.Push(child->data); // push from last child to first: LIFO
			}
		}
	}

	void InorderIterative(p2List<TreeTYPE> list)
	{
		assert(list);

		p2Stack<TreeNode<TreeTYPE>*> stack;
		TreeNode<TreeTYPE>* node = &root;
		p2List_item<TreeTYPE*>* last = NULL;
		unsigned int middle = 0;

		stack.push(node);

		while (stack.pop(node))
		{
			last = node->children.getLast();

			if (last_item != NULL && !(list->isOnList(node->children.getFirst())))
			{
				middle = node->children.count() / 2;

				for (unsigned int i = 0; i < middle; i++, last = last->previous)
				{
					stack.push(last->data);
				}

				stack.push(node);

				for (unsigned int i = middle; i < node->children.count(); i++, last = last->previous)
				{
					stack.push(last->data);
				}
			}
			else
			{
				list->add(node);
			}
		}
	}


	void PostorderIterative(p2List<TreeTYPE> list)
	{
		assert(list);

		p2Stack<TreeNode<TreeTYPE>*> stack;
		TreeNode<TreeTYPE>* node = &root;
		p2List_item<TreeTYPE*>* child;

		while (true)
		{
			while (node != NULL)
			{
				stack.Push(node); // travel through the first child of every node
				node = node->childs.start;
			}

			if (stack.Pop(node))
			{
				list.add(node->data);

				// now we get the next child
				if (node->parent != NULL)
				{
					child = node->parent->childs.start;

					while (child->data != node) // travel through childs's list until we find node
					{
						child = child->next;
					}

					if (child->next != NULL) // if child is not the last one, we assign node to the next child's data
					{
						node = child->next->data;
					}
					else // if we checked the last child, we set node to NULL so the next Pop pop's the node's father
					{
						node = NULL;
					}
				}
				else{ break; } // if the node's parent is null, means that node we added is the tree's root
			}
			else{ break; } // if stack is empty, means we added all nodes' datas to the list
		}
	}

	// recorrido preorder
	int CalcAdditionRecursive()
	{
		int suma = 0;

		root._CalcAdditionPreorderRecursive(suma);

		return suma;
	}


	int CalcAdditionIterative()
	{
		p2Stack<TreeNode<TreeTYPE>*> stack;
		TreeNode<TreeTYPE>* node = &root;
		p2List_item<TreeTYPE*>* child;

		int suma = 0;

		stack.Push(node);

		while (stack.Pop(node)) // while stack is not empty, pop next node
		{
			suma += node->data; // add node to list

			for (child = node->childs.end;
				child != NULL;
				child = child->prev)
			{
				stack.Push(child->data); // push from last child to first: LIFO
			}
		}

		return suma;
	}



};

#endif


