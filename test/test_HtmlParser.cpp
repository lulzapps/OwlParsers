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

BOOST_AUTO_TEST_CASE(element_test)
{
    char html[] = "<div></div>";
    auto doc = std::make_shared<owl::html::HtmlDocument>();

    BOOST_TEST(doc->parse(html));

    auto root = doc->getRoot();
    BOOST_TEST(root != nullptr);
    BOOST_TEST(root->getName() == "html");

    auto head = root->getFirstChild();
    BOOST_TEST(head != nullptr);
    BOOST_TEST(head->getName() == "head");

    auto body = head->getNext();
    BOOST_TEST(body != nullptr);
    BOOST_TEST(body->getName() == "body");

    auto div = body->getFirstChild();
    BOOST_TEST(div != nullptr);
    BOOST_TEST(div->getName() == "div");
}

BOOST_AUTO_TEST_CASE(attribute_iterate_test)
{
    char html[] = R"xx(<div id="123" class="abc"></div>)xx";
    auto doc = std::make_shared<owl::html::HtmlDocument>();

    BOOST_TEST(doc->parse(html));

    auto body = doc->getBody();
    BOOST_TEST(body);

    auto div = body->getFirstChild();
    BOOST_TEST(div);
    BOOST_TEST(div->getName() == "div");

    auto attr1 = div->getFirstAttribute();
    BOOST_TEST(attr1->getKey() == "id");
    BOOST_TEST(attr1->getValue() =="123");

    auto attr2 = attr1->getNext();
    BOOST_TEST(attr2->getKey() == "class");
    BOOST_TEST(attr2->getValue() =="abc");
}

BOOST_AUTO_TEST_SUITE_END()    
