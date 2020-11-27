#define BOOST_TEST_MODULE vector_test
#include <boost/test/included/unit_test.hpp>
#include "MyVector.h"

BOOST_AUTO_TEST_CASE(test) {
	//typedef std::vector<int> container;
	typedef MyVector<int> container;

	container vec;
	BOOST_TEST(vec.size() == 0);
	BOOST_TEST(vec.empty() == true);
	vec.push_back(5);
	vec.push_back(7);
	BOOST_TEST(vec.size() == 2);
	BOOST_TEST(vec[0] == 5);
	BOOST_TEST(*(vec.begin()) == 5);
	BOOST_TEST(*(vec.end() - 1) == 7);

	container vec2;
	BOOST_TEST(vec2.size() == 0);
	vec2.push_back(5);
	vec2.push_back(7);
	BOOST_TEST(vec == vec2);
	BOOST_TEST(vec >= vec2);
	vec2.push_back(71);
	BOOST_TEST(vec2.size() == 3);

	BOOST_TEST(vec != vec2);
	BOOST_TEST(vec <= vec2);
	BOOST_TEST(vec < vec2);
	BOOST_TEST(vec2 > vec);

	container vec3(3, 5);
	BOOST_TEST(vec3[0] == vec[0]);
	vec3.push_back(8);
	BOOST_TEST(*(vec3.end() - 1) == 8);

	container vec4{ 15,16,17 };
	BOOST_TEST(vec4.front() == 15);
	BOOST_TEST(vec4.back() == 17);
	BOOST_TEST(vec4[0] != vec3[0]);
	BOOST_TEST(vec4 > vec2);

	{
		container vec5{ 3,3,3 };
		container vec6{ 3,3 };
		BOOST_TEST(vec5 != vec6);
		vec5.pop_back();
		BOOST_TEST(vec5 == vec6);
	}
	{
		container vec5{ 3,3,3 };
		container vec6{ 3 };
		vec6.insert(vec6.begin() + 1, 2, 3);
		BOOST_TEST(vec5 == vec6);
	}
	{
		container vec5{ 3,3,9 };
		container vec6{ 4,5 };
		BOOST_TEST(vec5 < vec6);
	}
	{
		container vec5{ 4 };
		container vec6{ 3,3,8 };
		BOOST_TEST(vec5 > vec6);
	}
	{
		container vec5{ 3,3,8 };
		container vec6{ 3,3,4 };
		BOOST_TEST(vec6 < vec5);
	}
	{
		container vec5{ 35,36,37,38,39 };
		container vec6(vec5.begin() + 2, vec5.end());
		BOOST_TEST(vec6.size() == 3);
		container vec7(vec5.begin() + 1, vec5.begin() + 3);
		BOOST_TEST(vec7.size() == 2);
	}
	{
		container vec8(5);
		vec8.push_back(4);
		BOOST_TEST(vec8.size() == 6);
	}
	{
		container vec5{ 3,3 };
		container vec6 = vec5;//copy
		BOOST_TEST(vec6.size() == 2);
		BOOST_TEST(vec5 == vec6);
	}

	{
		container vec5{ 3,3 };
		container vec6;
		vec6 = vec5;
		BOOST_TEST(vec6.size() == 2);
		BOOST_TEST(vec5 == vec6);
	}
	{
		container vec5{ 3,3 };
		container vec6{ 11,14,16,18 };
		vec6 = vec5;
		BOOST_TEST(vec6.size() == 2);
		BOOST_TEST(vec5 == vec6);
	}
	{
		container vec5{ 3,4,5,6,7 };
		vec5.erase(vec5.begin() + 1);// 3 5 6 7
		BOOST_TEST(vec5.size() == 4);
	}
	{
		container vec5{ 3,4,5,6,7 };
		vec5.erase(vec5.begin() + 1, vec5.begin() + 3);// 3 6 7
		BOOST_TEST(vec5.size() == 3);
	}
	{
		container vec5{ 3,4,5,6,7 };
		vec5.insert(vec5.begin() + 1, 55);// 3 55 4 5 6 7
		BOOST_TEST(vec5.size() == 6);
		BOOST_TEST(vec5[1] == 55);
	}
	{
		container vec5{ 3,4,5,6,7 };
		vec5.insert(vec5.begin(), 3, 55);//55 55 55 3 4 5 6 7
		BOOST_TEST(vec5.size() == 8);
	}
	{
		container vec4{ 3,4,5,6,7 };
		container vec5;
		vec5.insert(vec5.begin(), vec4.begin(), vec4.begin() + 3);//3 4 5
		BOOST_TEST(vec5.size() == 3);
	}
	{
		container vec4{ 3,4,5,6,7 };
		container vec5{ 71,72,73 };
		vec5.insert(vec5.begin() + 1, vec4.begin(), vec4.end());//71 3 4 5 6 7 72 73
		BOOST_TEST(vec5.size() == 8);
		BOOST_TEST(vec5[2] == 4);
	}
	{
		container vec4{ 3,4,5 };
		container vec5{ 71,72,73 };
		vec4.swap(vec5);
		BOOST_TEST(vec5.size() == 3);
		BOOST_TEST(vec5[2] == 5);
		//std::cout << vec4 << "\n";
	}
	{
		container vec4{ 3,4,5 };
		vec4.resize(5, 8);// 3 4 5 8 8
		vec4.resize(2);// 3 4
		BOOST_TEST(vec4.size() == 2);
		vec4.resize(4, 9);// 3 4 9 9
		BOOST_TEST(vec4.size() == 4);
		BOOST_TEST(vec4[2] == 9);
		//std::cout << vec4 << "\n";
	}
	{
		container vec4{ 3,4,5 };
		BOOST_TEST(vec4.capacity() == 3);
		vec4.reserve(10);
		BOOST_TEST(vec4.capacity() == 10);
		vec4.reserve(2);
		BOOST_TEST(vec4.capacity() == 10);
	}
}