#include "CppUnitTest.h"
#include "../ChessModel.h"
#include "../Piece.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(ModelTests)
	{
	public:

		TEST_METHOD(InitModelTest)
		{
			ChessModel model;
			for (int i = 0; i < model.getN() * 2; i++)
			{
				Assert::IsNotNull(model.get(i));
			}

			for (int i = model.getN() * 6; i < model.getN() * model.getN(); i++)
			{
				Assert::IsNotNull(model.get(i));
			}
		}

		TEST_METHOD(CoordIsValidTest)
		{
			ChessModel model;
			Assert::IsTrue(model.coordIsValid('a', '1', 'a', '2'));
			Assert::IsTrue(model.coordIsValid('h', '1', 'h', '8'));

			Assert::IsFalse(model.coordIsValid('A', '/', 'a', '2'));
			Assert::IsFalse(model.coordIsValid('Z', '1', 'a', '9'));
		}

		TEST_METHOD(PieceCanJumpToTest)
		{
			ChessModel model;
			Assert::IsFalse(model.pieceCanJumpTo(0, 0, 2, 2));
			Assert::IsTrue(model.pieceCanJumpTo(0, 1, 0, 4));
			Assert::IsFalse(model.pieceCanJumpTo(0, 1, 0, 8));
		}

		TEST_METHOD(IsCheckTest)
		{
			ChessModel model;
			const int whiteQueenIndx = model.getN() + 4;
			Assert::IsFalse(model.isCheck(whiteQueenIndx));
		}

		TEST_METHOD(CastlingIsPossibleTest)
		{
			ChessModel model;
			const int wKingX = 3;
			const int wKingY = 0;
			const int wRightRookX = 7;
			const int wRightRookY = 0;

			bool isPossible = true;
			if (model.castlingIsPossible(wKingX, wKingY, wRightRookX, wRightRookY) == CastlingType::NONE)
			{
				isPossible = false;
			}
			Assert::IsFalse(isPossible);
		}

		TEST_METHOD(IsCheckmateTest)
		{
			ChessModel model;
			
			const int whiteQueenIndx = model.getN() + 4;
			Assert::IsFalse(model.isCheckmate(whiteQueenIndx));
		}
	};
}