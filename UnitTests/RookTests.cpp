#include "CppUnitTest.h"
#include "../Rook.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(RookTests)
	{
	public:

		TEST_METHOD(TestCanJump)
		{
			Rook b = Rook('W');
			Assert::IsFalse(b.canJump());
		}

		TEST_METHOD(TestColor)
		{
			Rook b = Rook('W');
			Assert::AreEqual<unsigned char>(b.color(), 'W');
		}

		TEST_METHOD(TestType)
		{
			Rook b = Rook('W');
			Assert::AreEqual<unsigned char>(b.type(), 'R');
		}

		TEST_METHOD(TestMoves)
		{
			Rook b = Rook('W');
			Assert::AreEqual<unsigned>(b.moves(), 0);
		}

		TEST_METHOD(TestMotionIsValid)
		{
			Rook b = Rook('W');
			Assert::IsFalse(b.motionIsValid(0, 0, 5, 5, nullptr));
			Assert::IsTrue(b.motionIsValid(4, 4, 0, 4, nullptr));
			Assert::IsTrue(b.motionIsValid(1, 7, 1, 4, nullptr));
		}
	};
}