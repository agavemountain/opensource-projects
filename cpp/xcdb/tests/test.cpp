#define BOOST_TEST_MODULE xcdb_unit_tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (EntryTest)

BOOST_AUTO_TEST_CASE(ShouldPass) {
    BOOST_CHECK_EQUAL(1, 1);
}

BOOST_AUTO_TEST_SUITE_END()
