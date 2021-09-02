#include <owl/HtmlParser.h>

namespace owl::html
{

Tree::Tree()
{
    _html = HtmlPtr(myhtml_create());
    myhtml_init(_html.get(), MyHTML_OPTIONS_DEFAULT, 1, 0);

    _tree = TreePtr(myhtml_tree_create());
    myhtml_tree_init(_tree.get(), _html.get());
}

Tree::Tree(std::string_view htmlstr)
    : Tree()
{
    myhtml_parse(_tree.get(), MyENCODING_UTF_8, htmlstr.data(), htmlstr.size());
}

Tree::~Tree()
{
    myhtml_tree_destroy(_tree.get());
}

bool Tree::parse(std::string_view htmlstr)
{
    return myhtml_parse(_tree.get(), MyENCODING_UTF_8, htmlstr.data(), htmlstr.size()) == MyHTML_STATUS_OK;
}

}