#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <owl/HtmlParser.h>

BOOST_AUTO_TEST_SUITE(MyClass)

BOOST_AUTO_TEST_CASE(file_pattern)
{
    char html[] = "<div></div>";
    owl::html::Tree tree;

    BOOST_TEST(tree.parse(html));
}

BOOST_AUTO_TEST_SUITE_END()    