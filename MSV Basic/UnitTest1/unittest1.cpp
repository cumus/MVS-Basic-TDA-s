#include "stdafx.h"
#include "CppUnitTest.h"

#include "../MSV Basic/p2Sstring.h"
#include "../MSV Basic/p2DynArray.h"
#include "../MSV Basic/p2List.h"
#include "../MSV Basic/p2Tree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(SString_cut)
		{
			p2SString s1("Hola mundo");
			s1.Cut(2, 5);
			Assert::AreEqual((int)strcmp("Houndo", s1.GetString()), 0);
			s1.Cut(3, 0);
			Assert::AreEqual((int)strcmp("Hou", s1.GetString()), 0);
		}



		TEST_METHOD(DynArray_Operator_concat)
		{
			p2DynArray<int> array(5);
			array.PushBack(1);
			array.PushBack(2);
			array.PushBack(4);
			array.PushBack(5);
			array.PushBack(8);

			p2DynArray<int> array2;
			array2.PushBack(991);
			array2.PushBack(992);
			array2.PushBack(993);

			array += array2;

			Assert::AreEqual((int)array.Count(), 8);
			Assert::AreEqual((int)array[0], 1);
			Assert::AreEqual((int)array[1], 2);
			Assert::AreEqual((int)array[2], 4);
			Assert::AreEqual((int)array[3], 5);
			Assert::AreEqual((int)array[4], 8);
			Assert::AreEqual((int)array[5], 991);
			Assert::AreEqual((int)array[6], 992);
			Assert::AreEqual((int)array[7], 993);
		}



		TEST_METHOD(ListInsert)
		{
			p2List<int> mylist;

			p2List<int> mylist2;
			mylist2.add(1);
			mylist2.add(2);
			mylist2.add(3);

			p2List<int> mylist3;
			mylist3.add(4);
			mylist3.add(5);
			mylist3.add(6);

			mylist.InsertAfter(0, mylist2);

			Assert::AreEqual(mylist[0], 1);
			Assert::AreEqual(mylist[1], 2);
			Assert::AreEqual(mylist[2], 3);

			mylist.InsertAfter(1, mylist3);

			Assert::AreEqual(mylist[0], 1);
			Assert::AreEqual(mylist[1], 2);
			Assert::AreEqual(mylist[2], 4);
			Assert::AreEqual(mylist[3], 5);
			Assert::AreEqual(mylist[4], 6);
			Assert::AreEqual(mylist[5], 3);

			mylist.InsertAfter(0, mylist3);

			Assert::AreEqual(mylist[0], 1);
			Assert::AreEqual(mylist[1], 4);
			Assert::AreEqual(mylist[2], 5);
			Assert::AreEqual(mylist[3], 6);
			Assert::AreEqual(mylist[4], 2);
			Assert::AreEqual(mylist[5], 4);
			Assert::AreEqual(mylist[6], 5);
			Assert::AreEqual(mylist[7], 6);
			Assert::AreEqual(mylist[8], 3);

			Assert::IsTrue((p2List_item<int>*) &mylist[0] == mylist.start);
			Assert::IsTrue((p2List_item<int>*) &mylist[8] == mylist.end);

		}

	};
}