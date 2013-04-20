#include "stdafx.h"
#include "CppUnitTest.h"
#include <nek/utility/move.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nektest
{		
	TEST_CLASS(utility_test)
	{
	public:
		
		struct move_test_class
		{
			move_test_class(){}
			move_test_class(const move_test_class&)
			{
				Logger::WriteMessage("copy\n");
			}
			move_test_class(move_test_class&&)
			{
				Logger::WriteMessage("move\n");
			}
		};

		TEST_METHOD(move_test)
		{
			using namespace nek;
			move_test_class m;
			move_test_class n = m;
			move_test_class o = move(m);
		}

	};
}