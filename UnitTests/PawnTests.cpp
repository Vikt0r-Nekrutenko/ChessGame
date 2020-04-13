#include "CppUnitTest.h"
#include "../Pawn.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(PawnTests)
	{
	public:

		TEST_METHOD(TestCanJump)
		{
			Pawn b = Pawn('W');
			Assert::IsFalse(b.canJump());
		}

		TEST_METHOD(TestColor)
		{
			Pawn b = Pawn('W');
			Assert::AreEqual<unsigned char>(b.color(), 'W');
		}

		TEST_METHOD(TestType)
		{
			Pawn b = Pawn('W');
			Assert::AreEqual<unsigned char>(b.type(), 'P');
		}

		TEST_METHOD(TestMoves)
		{
			Pawn b = Pawn('W');
			Assert::AreEqual<unsigned>(b.moves(), 0);
		}

		TEST_METHOD(TestMotionIsValid)
		{
			Pawn b = Pawn('W');
			Assert::IsTrue(b.motionIsValid(0, 0, 0, 1, nullptr));
			Assert::IsTrue(b.motionIsValid(0, 0, 0, 2, nullptr));

			b.move();
			Assert::IsFalse(b.motionIsValid(0, 0, 0, 2, nullptr));
		}

		TEST_METHOD(TestAttackDirection)
		{
			Pawn b = Pawn('W');
			Pawn o = Pawn('B');

			Assert::IsTrue(b.motionIsValid(0, 0, 1, 1, &o));
			Assert::IsTrue(b.motionIsValid(1, 1, 0, 2, &o));

			Assert::IsFalse(b.motionIsValid(1, 1, 0, 0, &o));
			Assert::IsFalse(b.motionIsValid(1, 1, 2, 0, &o));
		}
	};
}