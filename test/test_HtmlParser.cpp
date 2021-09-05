#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include <owl/HtmlParser.h>

BOOST_AUTO_TEST_SUITE(MyClass)

void print_node(owl::html::NodePtr node, int inc)
{
    while (node)
    {
        for(size_t i = 0; i < inc; i++)
        {
            printf(".");
        }

        std::cout << "name: " << node->getName() << "\n";

        print_node(node->getFirstChild(), inc+1);
        node = node->getNext();
    }
}

BOOST_AUTO_TEST_CASE(file_pattern)
{
    char html[] = "<div></div>";
    auto doc = std::make_shared<owl::html::HtmlDocument>();

    BOOST_TEST(doc->parse(html));

    auto root = doc->getRoot();
    print_node(root, 0);

    auto div = root->getFirstChild();
    BOOST_TEST(div != nullptr);
    BOOST_TEST(div->getName() == "div");
}

BOOST_AUTO_TEST_SUITE_END()    
