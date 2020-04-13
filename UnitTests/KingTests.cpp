#include "CppUnitTest.h"
#include "../King.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(KingTests)
	{
	public:

		TEST_METHOD(TestCanJump)
		{
			King b = King('W');
			Assert::IsFalse(b.canJump());
		}

		TEST_METHOD(TestColor)
		{
			King b = King('W');
			Assert::AreEqual<unsigned char>(b.color(), 'W');
		}

		TEST_METHOD(TestType)
		{
			King b = King('W');
			Assert::AreEqual<unsigned char>(b.type(), 'K');
		}

		TEST_METHOD(TestMoves)
		{
			King b = King('W');
			Assert::AreEqual<unsigned>(b.moves(), 0);
		}

		TEST_METHOD(TestMotionIsValid)
		{
			King b = King('W');
			Assert::IsFalse(b.motionIsValid(0, 0, 5, 5, nullptr));
			Assert::IsFalse(b.motionIsValid(4, 4, 8, 8, nullptr));
			Assert::IsFalse(b.motionIsValid(1, 7, 5, 4, nullptr));

			Assert::IsTrue(b.motionIsValid(1, 1, 0, 1, nullptr));
			Assert::IsTrue(b.motionIsValid(4, 4, 5, 5, nullptr));
			Assert::IsTrue(b.motionIsValid(1, 7, 1, 6, nullptr));
		}
	};
}