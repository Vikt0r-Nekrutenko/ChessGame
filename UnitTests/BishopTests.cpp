#include "CppUnitTest.h"
#include "../Bishop.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(BishopTests)
	{
	public:
		
		TEST_METHOD(TestCanJump)
		{
			Bishop b = Bishop('W');
			Assert::IsFalse(b.canJump());
		}

		TEST_METHOD(TestColor)
		{
			Bishop b = Bishop('W');
			Assert::AreEqual<unsigned char>(b.color(), 'W');
		}

		TEST_METHOD(TestType)
		{
			Bishop b = Bishop('W');
			Assert::AreEqual<unsigned char>(b.type(), 'B');
		}

		TEST_METHOD(TestMoves)
		{
			Bishop b = Bishop('W');
			Assert::AreEqual<unsigned>(b.moves(), 0);
		}

		TEST_METHOD(TestMotionIsValid)
		{
			Bishop b = Bishop('W');
			Assert::IsTrue(b.motionIsValid(0, 0, 5, 5, nullptr));
			Assert::IsTrue(b.motionIsValid(4, 4, 8, 8, nullptr));
			Assert::IsFalse(b.motionIsValid(1, 7, 5, 4, nullptr));
		}
	};
}