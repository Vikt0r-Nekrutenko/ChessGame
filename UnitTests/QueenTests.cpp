#include "CppUnitTest.h"
#include "../Queen.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(QueenTests)
	{
	public:

		TEST_METHOD(TestCanJump)
		{
			Queen b = Queen('W');
			Assert::IsFalse(b.canJump());
		}

		TEST_METHOD(TestColor)
		{
			Queen b = Queen('W');
			Assert::AreEqual<unsigned char>(b.color(), 'W');
		}

		TEST_METHOD(TestType)
		{
			Queen b = Queen('W');
			Assert::AreEqual<unsigned char>(b.type(), 'Q');
		}

		TEST_METHOD(TestMoves)
		{
			Queen b = Queen('W');
			Assert::AreEqual<unsigned>(b.moves(), 0);
		}

		TEST_METHOD(TestMotionIsValid)
		{
			Queen b = Queen('W');
			Assert::IsTrue(b.motionIsValid(0, 0, 5, 5, nullptr));
			Assert::IsTrue(b.motionIsValid(4, 4, 8, 8, nullptr));
			Assert::IsTrue(b.motionIsValid(1, 7, 4, 4, nullptr));
		}
	};
}