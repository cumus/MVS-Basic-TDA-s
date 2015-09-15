#ifndef __p2Rectangle_H__
#define __p2Rectangle_H__

template<class tdata>
struct Position
{
	tdata x;
	tdata y;

	inline Position()
	{
		x = 0;
		y = 0;
	}

	inline Position(const tdata _x, const tdata _y)
	{
		x = _x;
		y = _y;
	}

	void SetPosition(const tdata _x, const tdata _y)
	{
		x = _x;
		y = _y;
	}

	~Position()
	{}
};


template <class tdata>
class p2Rectangle
{
public:
	Position<tdata> position;
	tdata width;
	tdata height;

public:
	p2Rectangle()
	{
		position.SetPosition(0, 0);
		width = 0;
		height = 0;
	}

	p2Rectangle(const tdata _x, const tdata _y, const tdata _w, const tdata _h)
	{
		position.SetPosition(_x, _y);
		width = _w;
		height = _h;
	}

	p2Rectangle(const p2Rectangle<tdata>* r)
	{
		position.SetPosition(r.position.x, r.position.y);
		width = r.width;
		height = r.height;
	}

	const tdata GetArea() const
	{
		return width * height;
	}

	bool Intersects(const p2Rectangle<tdata> r) const
	{
		// asumimos que el origen de coordenadas esta en la parte superior izquierda
		return (position.x + width >= r.position.x
			 && r.position.x + r.width >= position.x
			 && position.y + height >= r.position.y
			 && r.position.y + r.height >= position.y);
	}
	

};


#endif