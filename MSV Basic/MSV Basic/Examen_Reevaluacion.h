#ifndef Examen_Reevaluacion_H
#define Examen_Reevaluacion_H

#include <cstdlib>
#include <iostream>

#include "p2Log.h"

#include "p2Sstring.h"
#include "p2DynArray.h"
#include "p2List.h"
#include "p2Tree.h"
#include "p2Rectangle.h"

#define TEST(a) (a) ? printf("\tTest\t" #a "\tSuccess\n") : printf("\tTest\t" #a " \tFailure\n");

void examen()
{
	printf("Exercise 1:\n\n");
	printf("\tClase p2Rectangle:\n\n");

	p2Rectangle<int> r(10, 10, 40, 50);
	p2Rectangle<int> r2(r);

	TEST(r.position.x == 10);
	TEST(r2.position.y == 10);
	TEST(r2.GetArea() == 2000);
	TEST(r2.Intersects(r) == true);

	/*-----------------------------------------------*/

	printf("\n\nExercise 2:\n\n");
	printf("\tMetodo DoubleVocals():\n\n");

	p2SString s("Hola Mundo");

	TEST(s.DoubleVocals() == 4);
	TEST(s == "Hoolaa Muundoo");

	/*-----------------------------------------------*/

	printf("\n\nExercise 3:\n\n");
	printf("\tLista con # de elementos impares:\n\n");

	p2List<int> list;

	list.add(1);
	list.add(2);
	list.add(3);
	list.add(4);
	list.add(5);
	list.add(6);
	list.add(7);

	list.Flip();

	TEST(list[0] == 7);
	TEST(list[1] == 6);
	TEST(list[2] == 5);
	TEST(list[3] == 4);
	TEST(list[4] == 3);
	TEST(list[5] == 2);
	TEST(list[6] == 1);

	printf("\n\n\tLista con # de elementos pares:\n\n");

	p2List<int> list2;

	list2.add(1);
	list2.add(2);
	list2.add(3);
	list2.add(4);
	list2.add(5);
	list2.add(6);
	list2.add(7);
	list2.add(8);

	list2.Flip();

	TEST(list2[0] == 8);
	TEST(list2[1] == 7);
	TEST(list2[2] == 6);
	TEST(list2[3] == 5);
	TEST(list2[4] == 4);
	TEST(list2[5] == 3);
	TEST(list2[6] == 2);
	TEST(list2[7] == 1);

	/*-----------------------------------------------*/

	printf("\n\nExercise 4:\n\n");
	printf("\tMetodo PrefixList(const p2List<VALUE> list):\n\n");

	p2DynArray<int> array(5);

	array.PushBack(100);
	array.PushBack(200);
	array.PushBack(300);
	array.PushBack(400);
	array.PushBack(500);

	array.PrefixList(list);

	TEST(array.Count() == 12);
	TEST(array[0] == 7);
	TEST(array[1] == 6);
	TEST(array[2] == 5);
	TEST(array[3] == 4);
	TEST(array[4] == 3);
	TEST(array[5] == 2);
	TEST(array[6] == 1);
	TEST(array[7] == 100);
	TEST(array[8] == 200);
	TEST(array[9] == 300);
	TEST(array[10] == 400);
	TEST(array[11] == 500);


	getchar();
}

#endif