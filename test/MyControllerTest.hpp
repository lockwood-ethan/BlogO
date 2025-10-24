#ifndef MyControllerTest_hpp
#define MyControllerTest_hpp

#include "oatpp-test/UnitTest.hpp"

// TODO: figure out why this is throwing a compiler error
class MyControllerTest : public oatpp::test::UnitTest {
public:
	MyControllerTest() : UnitTest("TEST[MyControllerTest]") {}
	void onRun() override;
};

#endif
