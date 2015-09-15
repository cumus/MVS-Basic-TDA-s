#ifndef Vec3_H
#define Vec3_H

#include "p2Assert.h"

template <class VALUE>
class Vec3
{
private:

	VALUE* data[];

public:

	Vec3() : data(NULL)
	{
		data = new VALUE[3];
	}

	Vec3(const VALUE x, const VALUE y, const VALUE z): data(NULL)
	{
		data = new VALUE[3];
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	Vec3(const Vec3 vector) : data(NULL)
	{
		data = new VALUE[3];
		data[0] = vector[0];
		data[1] = vector[1];
		data[2] = vector[2];
	}

	~Vec3()
	{
		delete[] data;
	}







	//Operators

	VALUE& operator [](const unsigned int index)
	{
		return index < 3 ? data[index] : data[0];
	}

	const VALUE& operator [](const unsigned int index) const
	{
		return index < 3 ? data[index] : data[0];
	}

	Vec3& operator + (const Vec3 vector)
	{
		return new Vec3(vector[0] + data[0], vector[1] + data[1], vector[2] + data[2]);
	}

	Vec3& operator += (const Vec3 vector)
	{
		data[0] += vector[0];
		data[1] += vector[1];
		data[2] += vector[2];

		return this;
	}

	Vec3& operator - (const Vec3 vector)
	{
		return new Vec3(data[0] - vector[0], data[1] - vector[1], data[2] - vector[2]);
	}

	Vec3& operator -= (const Vec3 vector)
	{
		data[0] -= vector[0];
		data[1] -= vector[1];
		data[2] -= vector[2];

		return this;
	}

	Vec3& operator * (const VALUE value)
	{
		return new Vec3(data[0] * value, data[1] * value, data[2] * value);
	}

	Vec3& operator *= (const VALUE value)
	{
		data[0] *= value;
		data[1] *= value;
		data[2] *= value;

		return this;
	}


}

#endif