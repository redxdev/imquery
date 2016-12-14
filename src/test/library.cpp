#include <scripttest.h>
#include <gtest/gtest.h>

#include <cmath>

using namespace imq;

static const char* abs_test = "a = abs(-1); b = abs(-1.); c = abs(123); d = abs(54.);";
static const char* trig_test = "a = sin(1.3); b = cos(0.53); c = tan(0.3);";
static const char* min_test = "a = min(5, 10); b = min(10, 5); c = min(5., 10.); d = min(5., 10.);";
static const char* max_test = "a = max(5, 10); b = max(10, 5); c = max(5., 10.); d = max(5., 10.);";
static const char* clamp_test = "a = clamp(1, 0, 5); b = clamp(10, 0, 5); c = clamp(-5, 0, 5); d = clamp(1., 0., 5.); e = clamp(10., 0., 5.); f = clamp(-5., 0., 5.);";
static const char* pow_test = "a = pow(2, 10); b = pow(2, -10); c = pow(-3, 3); d = pow(-3, -5);";
static const char* sqrt_test = "a = sqrt(4); b = sqrt(10); c = sqrt(99); d = sqrt(144);";

TEST(Library, Math)
{
	ScriptTest st;

	ASSERT_TRUE(st.run(abs_test));
	EXPECT_TRUE(st.equal("a", QValue::Integer(1)));
	EXPECT_TRUE(st.equal("b", QValue::Float(1.f)));
	EXPECT_TRUE(st.equal("c", QValue::Integer(123)));
	EXPECT_TRUE(st.equal("d", QValue::Float(54.f)));

	ASSERT_TRUE(st.run(trig_test));
	EXPECT_TRUE(st.equal("a", QValue::Float(std::sin(1.3f))));
	EXPECT_TRUE(st.equal("b", QValue::Float(std::cos(0.53f))));
	EXPECT_TRUE(st.equal("c", QValue::Float(std::tan(0.3f))));

	ASSERT_TRUE(st.run(min_test));
	EXPECT_TRUE(st.equal("a", QValue::Integer(5)));
	EXPECT_TRUE(st.equal("b", QValue::Integer(5)));
	EXPECT_TRUE(st.equal("c", QValue::Float(5.f)));
	EXPECT_TRUE(st.equal("d", QValue::Float(5.f)));

	ASSERT_TRUE(st.run(max_test));
	EXPECT_TRUE(st.equal("a", QValue::Integer(10)));
	EXPECT_TRUE(st.equal("b", QValue::Integer(10)));
	EXPECT_TRUE(st.equal("c", QValue::Float(10.f)));
	EXPECT_TRUE(st.equal("d", QValue::Float(10.f)));

	ASSERT_TRUE(st.run(clamp_test));
	EXPECT_TRUE(st.equal("a", QValue::Integer(1)));
	EXPECT_TRUE(st.equal("b", QValue::Integer(5)));
	EXPECT_TRUE(st.equal("c", QValue::Integer(0)));
	EXPECT_TRUE(st.equal("d", QValue::Float(1.f)));
	EXPECT_TRUE(st.equal("e", QValue::Float(5.f)));
	EXPECT_TRUE(st.equal("f", QValue::Float(0.f)));

	ASSERT_TRUE(st.run(pow_test));
	EXPECT_TRUE(st.equal("a", QValue::Float(std::pow(2.f, 10.f))));
	EXPECT_TRUE(st.equal("b", QValue::Float(std::pow(2.f, -10.f))));
	EXPECT_TRUE(st.equal("c", QValue::Float(std::pow(-3.f, 3.f))));
	EXPECT_TRUE(st.equal("d", QValue::Float(std::pow(-3.f, -5.f))));

	ASSERT_TRUE(st.run(sqrt_test));
	EXPECT_TRUE(st.equal("a", QValue::Float(std::sqrt(4.f))));
	EXPECT_TRUE(st.equal("b", QValue::Float(std::sqrt(10.f))));
	EXPECT_TRUE(st.equal("c", QValue::Float(std::sqrt(99.f))));
	EXPECT_TRUE(st.equal("d", QValue::Float(std::sqrt(144.f))));
}