#include "CppUnitTest.h"
#include "../Knight.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(KnightTests)
	{
	public:

		TEST_METHOD(TestCanJump)
		{
			Knight b = Knight('W');
			Assert::IsTrue(b.canJump());
		}

		TEST_METHOD(TestColor)
		{
			Knight b = Knight('W');
			Assert::AreEqual<unsigned char>(b.color(), 'W');
		}

		TEST_METHOD(TestType)
		{
			Knight b = Knight('W');
			Assert::AreEqual<unsigned char>(b.type(), 'N');
		}

		TEST_METHOD(TestMoves)
		{
			Knight b = Knight('W');
			Assert::AreEqual<unsigned>(b.moves(), 0);
		}

		TEST_METHOD(TestMotionIsValid)
		{
			Knight b = Knight('W');
			Assert::IsTrue(b.motionIsValid(0, 0, 2, 1, nullptr));
			Assert::IsTrue(b.motionIsValid(4, 4, 5, 2, nullptr));
		}
	};
}