#include "CppUnitTest.h"
#include "../CircularBufferLib/CircularBuffer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CircularBufferUnitTest
{
	TEST_CLASS(CircularBufferUnitTest)
	{
	public:
		TEST_METHOD(ConstructorSizeOne)
		{
			CircularBuffer<int, 1> buf;
			Assert::AreEqual(size_t{ 0 }, buf.size());
		}
		TEST_METHOD(ConstructorSize10)
		{
			CircularBuffer<int, 10> buf;
			Assert::AreEqual(size_t{ 0 }, buf.size());
		}
		TEST_METHOD(pushAndPopSize1NotExceedSize)
		{
			CircularBuffer<int, 1> buf;

			Assert::IsTrue(buf.push(43));
			Assert::AreEqual(size_t{ 1 }, buf.size());
			int v;
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(43, v);
			Assert::AreEqual(size_t{ 0 }, buf.size());
		}
		TEST_METHOD(pushAndPopSize5NotExceedSize)
		{
			CircularBuffer<int, 5> buf;

			Assert::IsTrue(buf.push(23));
			Assert::IsTrue(buf.push(4));
			Assert::IsTrue(buf.push(6));
			Assert::IsTrue(buf.push(12));
			Assert::IsTrue(buf.push(91));
			Assert::AreEqual(size_t{ 5 }, buf.size());
			int v;
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(23, v);
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(4, v);
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(6, v);
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(12, v);
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(91, v);
		}
		TEST_METHOD(pushAndPopSize1ExceedSize)
		{
			CircularBuffer<int, 1> buf;

			Assert::IsTrue(buf.push(2));
			Assert::IsFalse(buf.push(7));
			Assert::AreEqual(size_t{ 1 }, buf.size());
			int v;
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(2, v);
			Assert::AreEqual(size_t{ 0 }, buf.size());
		}
		TEST_METHOD(pushAndPopSize3ExceedSize)
		{
			CircularBuffer<int, 3> buf;

			Assert::IsTrue(buf.push(2));
			Assert::IsTrue(buf.push(7));
			Assert::IsTrue(buf.push(15));
			Assert::IsFalse(buf.push(34));
			Assert::AreEqual(size_t{ 3 }, buf.size());
			int v;
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(2, v);
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(7, v);
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(15, v);
			Assert::AreEqual(size_t{ 0 }, buf.size());
		}
		TEST_METHOD(popFromSize1EmptyBuffer)
		{
			CircularBuffer<int, 1> buf;
			int v;
			Assert::IsFalse(buf.pop(v));
		}
		TEST_METHOD(popFromSize3EmptyBuffer)
		{
			CircularBuffer<int, 3> buf;
			int v;
			Assert::IsFalse(buf.pop(v));
		}
		TEST_METHOD(pushPopIntoEmpty)
		{
			CircularBuffer<int, 5> buf;
			Assert::IsTrue(buf.push(5));
			Assert::AreEqual(size_t{ 1 }, buf.size());
			int v;
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(5, v);
			Assert::AreEqual(size_t{ 0 }, buf.size());
		}
		TEST_METHOD(pushPopArroundIntoEmpty)
		{
			int v;
			CircularBuffer<int, 5> buf;
			Assert::IsTrue(buf.push(4));
			Assert::IsTrue(buf.push(3));
			Assert::IsTrue(buf.pop(v));
			Assert::IsTrue(buf.pop(v));

			Assert::IsTrue(buf.push(5));
			Assert::AreEqual(size_t{ 1 }, buf.size());

			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(5, v);
			Assert::AreEqual(size_t{ 0 }, buf.size());
		}
		TEST_METHOD(pushPopIntoNotEmpty)
		{
			CircularBuffer<int, 5> buf;
			Assert::IsTrue(buf.push(5));
			Assert::IsTrue(buf.push(3));
			Assert::IsTrue(buf.push(7));
			int v;
			Assert::AreEqual(size_t{ 3 }, buf.size());
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(5, v);
			Assert::AreEqual(size_t{ 2 }, buf.size());
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(3, v);
			Assert::AreEqual(size_t{ 1 }, buf.size());
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(7, v);
			Assert::AreEqual(size_t{ 0 }, buf.size());
		}
		TEST_METHOD(pushPopArroundIntoNotEmpty)
		{
			int v;
			CircularBuffer<int, 5> buf;
			Assert::IsTrue(buf.push(9));
			Assert::IsTrue(buf.push(5));
			Assert::IsTrue(buf.pop(v));
			Assert::IsTrue(buf.push(3));
			Assert::IsTrue(buf.push(7));
			
			Assert::AreEqual(size_t{ 3 }, buf.size());
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(5, v);
			Assert::AreEqual(size_t{ 2 }, buf.size());
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(3, v);
			Assert::AreEqual(size_t{ 1 }, buf.size());
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(7, v);
			Assert::AreEqual(size_t{ 0 }, buf.size());
		}
		TEST_METHOD(pushPopWillBecomeFull)
		{
			CircularBuffer<int, 4> buf;
			Assert::IsTrue(buf.push(5));
			Assert::IsTrue(buf.push(3));
			Assert::IsTrue(buf.push(7));
			Assert::IsTrue(buf.push(4));
			int v;
			Assert::AreEqual(size_t{ 4 }, buf.size());
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(5, v);
			Assert::AreEqual(size_t{ 3 }, buf.size());
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(3, v);
			Assert::AreEqual(size_t{ 2 }, buf.size());
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(7, v);
			Assert::AreEqual(size_t{ 1 }, buf.size());
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(4, v);
			Assert::AreEqual(size_t{ 0 }, buf.size());
		}
		TEST_METHOD(pushPopArroundWillBecomeFull)
		{
			int v;
			CircularBuffer<int, 4> buf;
			Assert::IsTrue(buf.push(5));
			Assert::IsTrue(buf.push(3));
			Assert::IsTrue(buf.push(5));
			Assert::IsTrue(buf.pop(v));
			Assert::IsTrue(buf.pop(v));
			Assert::IsTrue(buf.push(3));
			Assert::IsTrue(buf.push(7));
			Assert::IsTrue(buf.push(4));

			Assert::AreEqual(size_t{ 4 }, buf.size());
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(5, v);
			Assert::AreEqual(size_t{ 3 }, buf.size());
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(3, v);
			Assert::AreEqual(size_t{ 2 }, buf.size());
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(7, v);
			Assert::AreEqual(size_t{ 1 }, buf.size());
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(4, v);
			Assert::AreEqual(size_t{ 0 }, buf.size());
		}
		TEST_METHOD(pushIntoFull)
		{
			CircularBuffer<int, 4> buf;
			Assert::IsTrue(buf.push(5));
			Assert::IsTrue(buf.push(2));
			Assert::IsTrue(buf.push(8));
			Assert::IsTrue(buf.push(4));
			Assert::AreEqual(size_t{ 4 }, buf.size());

			Assert::IsFalse(buf.push(7));
		}
		TEST_METHOD(pushArroundIntoFull)
		{
			int v;
			CircularBuffer<int, 4> buf;
			Assert::IsTrue(buf.push(5));
			Assert::IsTrue(buf.push(2));
			Assert::IsTrue(buf.push(8));
			Assert::IsTrue(buf.pop(v));
			Assert::IsTrue(buf.push(4));
			Assert::IsTrue(buf.push(5));
			Assert::AreEqual(size_t{ 4 }, buf.size());

			Assert::IsFalse(buf.push(7));
		}
		TEST_METHOD(popFromEmpty)
		{
			int v;
			CircularBuffer<int, 4> buf;
			Assert::IsFalse(buf.pop(v));
		}
		TEST_METHOD(popArroundFromEmpty)
		{
			int v;
			CircularBuffer<int, 4> buf;
			Assert::IsTrue(buf.push(5));
			Assert::IsTrue(buf.push(2));
			Assert::IsTrue(buf.push(8));
			Assert::IsTrue(buf.pop(v));
			Assert::IsTrue(buf.pop(v));
			Assert::IsTrue(buf.pop(v));
			Assert::AreEqual(size_t{ 0 }, buf.size());

			Assert::IsFalse(buf.pop(v));
		}
	};
}
