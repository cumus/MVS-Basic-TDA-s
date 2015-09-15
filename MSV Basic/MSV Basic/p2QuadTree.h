// ----------------------------------------------------
// Quadtree implementation --
// ----------------------------------------------------

/*
#ifndef __P2QUADTREE_H__
#define __P2QUADTREE_H__

#include "Collider.h"
#include "p2DynArray.h"
#include "Globals.h"

#define QUADTREE_MAX_ITEMS 2

// Helper function to check if one rectangle complately contains another
bool Contains(const SDL_Rect& a, const SDL_Rect& b);
bool Intersects(const SDL_Rect& a, const SDL_Rect& b);

// Tree node -------------------------------------------------------
class p2QuadTreeNode
{

public:

	SDL_Rect				rect;
	p2DynArray<Collider*>	objects;
	p2QuadTreeNode*			parent;
	p2QuadTreeNode*			childs[4];

public:

	p2QuadTreeNode(SDL_Rect r) : 
		rect(r),
		objects(QUADTREE_MAX_ITEMS)
	{
		parent = childs[0] = childs[1] = childs[2] = childs[3] = NULL;
	}

	~p2QuadTreeNode()
	{
		for(int i = 0; i < 4; ++i)
			if(childs[i] != NULL) delete childs[i];
	}
	 
	void Insert(Collider* col)
	{
		// RICARD TO DO: Insertar un nou Collider al quadtree
		// En principi cada node pot enmagatzemar QUADTREE_MAX_ITEMS nodes (encara que podrien ser més)
		// Si es detecten més, el node s'ha de tallar en quatre
		// Si es talla, s'ha de redistribuir tots els seus colliders pels nous nodes (childs) sempre que pugui
		// Nota: un Collider pot estar a més de un node del quadtree
		// Nota: si un Collider intersecciona als quatre childs, deixar-lo al pare

		// First, we check the number of Colliders on the node. Maximum = 2!
		// If there is room for one more, we added. If not, the code jumps to else
		// statement...
		if (objects.Count() < QUADTREE_MAX_ITEMS && childs[0] == NULL)
		{
			objects.PushBack(col);
		}
		else
		{
			// ...where the method checks whether any child exists. If not, we create the four new children, 
			// taking into account the parent dimensions (the object calling this method).
			if (childs[0] == NULL) 
			{
				int mid_width = this->rect.w / 2;
				int mid_height = this->rect.h / 2;

				SDL_Rect rect0 = { this->rect.x, this->rect.y, mid_width, mid_height };
				SDL_Rect rect1 = { this->rect.x + mid_width, this->rect.y, mid_width, mid_height };
				SDL_Rect rect2 = { this->rect.x, this->rect.y + mid_height, mid_width, mid_height };
				SDL_Rect rect3 = { this->rect.x + mid_width, this->rect.y + mid_height, mid_width, mid_height };

				childs[0] = new p2QuadTreeNode(rect0);
				childs[1] = new p2QuadTreeNode(rect1);
				childs[2] = new p2QuadTreeNode(rect2);
				childs[3] = new p2QuadTreeNode(rect3);

				childs[0]->parent = childs[1]->parent = childs[2]->parent = childs[3]->parent = this;

				// Before adding the new collider, we move the objects in the parent node to the
				// corresponding child.

				p2DynArray<Collider*> objects_tmp = objects;
				objects.Clear();

				for (unsigned int i = 0; i < QUADTREE_MAX_ITEMS; i++)
				{
					if (Intersects(col->rect, childs[0]->rect) &&
						Intersects(col->rect, childs[1]->rect) &&
						Intersects(col->rect, childs[2]->rect) &&
						Intersects(col->rect, childs[3]->rect))
					{
						// The Collider remains on the parent node if intersects with 
						// the four subdivisions.
						objects.PushBack(objects_tmp[i]);
					}
					else
					{
						for (unsigned int j = 0; j < 4; j++)
						{
							if (Intersects(objects_tmp[i]->rect, childs[j]->rect))
								childs[j]->objects.PushBack(objects_tmp[i]);
						}
					}
				}
			}
			

			// We add the collider to the corresponding child or to the parent
			// node if it shares all of its children.
			if (Intersects(col->rect, childs[0]->rect) &&
				Intersects(col->rect, childs[1]->rect) &&
				Intersects(col->rect, childs[2]->rect) &&
				Intersects(col->rect, childs[3]->rect))
				objects.PushBack(col);
			else
			{
				for (unsigned int i = 0; i < 4; i++)
				{
					if (Intersects(col->rect, childs[i]->rect) == true)
					{
						childs[i]->Insert(col);
					}
				}
			}
		}
	}

	int CollectCandidates(p2DynArray<Collider*>& nodes, const SDL_Rect& r) const
	{
		// RICARD TO DO:
		// Omplir el array "nodes" amb tots els colliders candidats
		// de fer intersecció amb el rectangle r
		// retornar el número d'interseccions calculades en el procés
		// Nota: és una funció recursiva.

		int tests = 0;

		if (Intersects(rect, r) == true)
		{
			for (unsigned int i = 0; i < objects.Count(); i++)
			{
				tests++;
				nodes.PushBack(objects[i]);
			}
		}
					
		if (childs[0] != NULL)
			for (unsigned int i = 0; i < 4; i++)
				tests += childs[i]->CollectCandidates(nodes, r);
		
		return tests;
	}

	void CollectRects(p2DynArray<p2QuadTreeNode*>& nodes) 
	{
		nodes.PushBack(this);

		for(int i = 0; i < 4; ++i)
			if(childs[i] != NULL) childs[i]->CollectRects(nodes);
	}

};

// Tree class -------------------------------------------------------
class p2QuadTree
{
public:

	// Constructor
	p2QuadTree() : root(NULL)
	{}

	// Destructor
	virtual ~p2QuadTree()
	{
		Clear();
	}

	void SetBoundaries(const SDL_Rect& r)
	{
		if(root != NULL)
			delete root;

		root = new p2QuadTreeNode(r);
	}

	void Insert(Collider* col)
	{
		if(root != NULL)
		{
			if(Intersects(root->rect, col->rect))
				root->Insert(col);
		}
	}

	void Clear()
	{
		if(root != NULL)
		{
			delete root;
			root = NULL;
		}
	}

	int CollectCandidates(p2DynArray<Collider*>& nodes, const SDL_Rect& r) const
	{
		int tests = 0;
		if(root != NULL && Intersects(root->rect, r))
			tests = root->CollectCandidates(nodes, r);
		return tests;
	}

	void CollectRects(p2DynArray<p2QuadTreeNode*> &nodes) const
	{
		if(root != NULL)
			root->CollectRects(nodes);
	}

public:

	p2QuadTreeNode*	root;

};

#endif // __p2QuadTree_H__

*/