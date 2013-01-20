#include "config.h"
#include <map>
#include <string>
#include <vector>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "RapidGL/Node.h"
#include "RapidGL/Unmarshaller.h"
namespace RapidGL {


/**
 * Unit test for `Unmarshaller`.
 */
class UnmarshallerTest : public CppUnit::TestFixture {
public:

    // Threshold for floating-point comparisons
    static const double TOLERANCE = 1e-9;

    /**
     * Ensures `Unmarshaller::findValue` returns the value of a key in the map.
     */
    void testFindValueWithContained() {
        std::map<std::string,std::string> map;
        map["foo"] = "FOO";
        map["bar"] = "BAR";
        CPPUNIT_ASSERT_EQUAL(std::string("FOO"), Unmarshaller::findValue(map, "foo"));
    }

    /**
     * Ensures `Unmarshaller::findValue` returns the empty string for a key not in the map.
     */
    void testFindValueWithNotContained() {
        std::map<std::string,std::string> map;
        map["foo"] = "FOO";
        map["bar"] = "BAR";
        CPPUNIT_ASSERT_EQUAL(std::string(""), Unmarshaller::findValue(map, "baz"));
    }

    /**
     * Ensures `Unmarshaller::parseFloat` works with '1'.
     */
    void testParseFloatWithOne() {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, Unmarshaller::parseFloat("1"), TOLERANCE);
    }

    /**
     * Ensures `Unmarshaller::parseFloat` works with '1.0'.
     */
    void testParseFloatWithOnePointZero() {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f, Unmarshaller::parseFloat("1.0"), TOLERANCE);
    }

    /**
     * Ensures `Unmarshaller::parseFloat` throws if passed '1.0 '.
     */
    void testParseFloatWithOneAndSpace() {
        CPPUNIT_ASSERT_THROW(Unmarshaller::parseFloat("1.0 "), std::invalid_argument);
    }

    /**
     * Ensures `Unmarshaller::parseFloat` throws if passed '1.0  '.
     */
    void testParseFloatWithOneAndSpaces() {
        CPPUNIT_ASSERT_THROW(Unmarshaller::parseFloat("1.0  "), std::invalid_argument);
    }

    /**
     * Ensures `Unmarshaller::parseFloat` throws if passed ' 1.0'.
     */
    void testParseFloatWithSpaceAndOne() {
        CPPUNIT_ASSERT_THROW(Unmarshaller::parseFloat(" 1.0"), std::invalid_argument);
    }

    /**
     * Ensures `Unmarshaller::parseFloat` throws if passed '  1.0'.
     */
    void testParseFloatWithSpacesAndOne() {
        CPPUNIT_ASSERT_THROW(Unmarshaller::parseFloat("  1.0"), std::invalid_argument);
    }

    /**
     * Ensures `Unmarshaller::parseInt` works with '1'.
     */
    void testParseIntWithOne() {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1, Unmarshaller::parseInt("1"), TOLERANCE);
    }

    /**
     * Ensures `Unmarshaller::parseInt` throws if passed '1.0'.
     */
    void testParseIntWithOnePointZero() {
        CPPUNIT_ASSERT_THROW(Unmarshaller::parseInt("1.0"), std::invalid_argument);
    }

    /**
     * Ensurse `Unmarshaller::parseInt` throws if passed '1 '.
     */
    void testParseIntWithOneAndSpace() {
        CPPUNIT_ASSERT_THROW(Unmarshaller::parseInt("1 "), std::invalid_argument);
    }

    /**
     * Ensures `Unmarshaller::parseInt` throws if passed '1  '.
     */
    void testParseIntWithOneAndSpaces() {
        CPPUNIT_ASSERT_THROW(Unmarshaller::parseInt("1  "), std::invalid_argument);
    }

    /**
     * Ensures `Unmarshaller::parseInt` throws if passed ' 1'.
     */
    void testParseIntWithSpaceAndOne() {
        CPPUNIT_ASSERT_THROW(Unmarshaller::parseInt(" 1"), std::invalid_argument);
    }

    /**
     * Ensures `Unmarshaller::parseInt` throws if passed '  1'.
     */
    void testParseIntWithSpacesAndOne() {
        CPPUNIT_ASSERT_THROW(Unmarshaller::parseInt("  1"), std::invalid_argument);
    }

    /**
     * Ensures `Unmarshaller::tokenize` works with the empty string.
     */
    void testTokenizeWithEmptyString() {
        const std::vector<std::string> tokens = Unmarshaller::tokenize("");
        CPPUNIT_ASSERT(tokens.empty());
    }

    /**
     * Ensures `Unmarshaller::tokenize` works with the numbers one through five.
     */
    void testTokenizeWithOneThroughFive() {
        const std::vector<std::string> tokens = Unmarshaller::tokenize("1 2 3 4 5");
        CPPUNIT_ASSERT_EQUAL((size_t) 5, tokens.size());
        CPPUNIT_ASSERT_EQUAL(std::string("1"), tokens[0]);
        CPPUNIT_ASSERT_EQUAL(std::string("2"), tokens[1]);
        CPPUNIT_ASSERT_EQUAL(std::string("3"), tokens[2]);
        CPPUNIT_ASSERT_EQUAL(std::string("4"), tokens[3]);
        CPPUNIT_ASSERT_EQUAL(std::string("5"), tokens[4]);
    }

    CPPUNIT_TEST_SUITE(UnmarshallerTest);
    CPPUNIT_TEST(testFindValueWithContained);
    CPPUNIT_TEST(testFindValueWithNotContained);
    CPPUNIT_TEST(testParseFloatWithOne);
    CPPUNIT_TEST(testParseFloatWithOnePointZero);
    CPPUNIT_TEST(testParseFloatWithOneAndSpace);
    CPPUNIT_TEST(testParseFloatWithOneAndSpaces);
    CPPUNIT_TEST(testParseFloatWithSpaceAndOne);
    CPPUNIT_TEST(testParseFloatWithSpacesAndOne);
    CPPUNIT_TEST(testParseIntWithOne);
    CPPUNIT_TEST(testParseIntWithOnePointZero);
    CPPUNIT_TEST(testParseIntWithOneAndSpace);
    CPPUNIT_TEST(testParseIntWithOneAndSpaces);
    CPPUNIT_TEST(testParseIntWithSpaceAndOne);
    CPPUNIT_TEST(testParseIntWithSpacesAndOne);
    CPPUNIT_TEST(testTokenizeWithEmptyString);
    CPPUNIT_TEST(testTokenizeWithOneThroughFive);
    CPPUNIT_TEST_SUITE_END();
};

} /* namespace RapidGL */

int main(int argc, char* argv[]) {
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(RapidGL::UnmarshallerTest::suite());
    runner.run();
    return 0;
}
