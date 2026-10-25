#include "pch.h"
#include "CppUnitTest.h"
#include "../lab-2.4.2/Subscriber.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestAddBookAndCount)
		{
			Subscriber sub("Franko", 101);
			Book b1 = { "Author", "Title", 2026, "Publisher", 350.0 };
			BorrowedBook bb1 = { b1, "2026-10-01", "2026-10-15", false };

			sub.addBook(bb1);

			Assert::AreEqual(1, sub.getCount());
		}

		TEST_METHOD(TestCalculateDebtPrice)
		{
			Subscriber sub("Shevchenko", 102);
			Book b1 = { "Author1", "Title1", 2026, "Publisher1", 200.0 };
			Book b2 = { "Author2", "Title2", 2025, "Publisher2", 150.0 };
			BorrowedBook bb1 = { b1, "2026-09-01", "2026-09-15", false };
			BorrowedBook bb2 = { b2, "2026-10-01", "2026-10-15", true };

			sub.addBook(bb1);
			sub.addBook(bb2);

			Assert::AreEqual(200.0, sub.calculateDebtPrice());
		}
	};
}