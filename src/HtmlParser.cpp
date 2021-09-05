#include <owl/HtmlParser.h>

namespace owl::html
{

Node::Node(myhtml_tree_node_t *node, HtmlDocumentPtr parent)
    : _node{node}, _parent{parent}
{
    // do nothing
}

std::string_view Node::getName() const
{
    auto parent = _parent.lock();
    if (parent)
    {
        auto name = myhtml_tag_name_by_id(parent->_tree, myhtml_node_tag_id(_node), NULL);
        if (name)
        {
            return name;
        }
    }

    return {};
}

NodePtr Node::getNext() const
{
    auto parent = _parent.lock();
    if (parent)
    {
        auto node = myhtml_node_next(_node);
        if (node)
        {
            return std::make_shared<Node>(node, parent);
        }
    }

    return {};
}

NodePtr Node::getFirstChild() const
{
    auto parent = _parent.lock();
    if (parent)
    {
        auto node = myhtml_node_child(_node);
        if (node)
        {
            return std::make_shared<Node>(node, parent);
        }
    }

    return {};
}

HtmlDocument::HtmlDocument()
{
    _html = myhtml_create();
    myhtml_init(_html, MyHTML_OPTIONS_DEFAULT, 1, 0);

    _tree = myhtml_tree_create();
    myhtml_tree_init(_tree, _html);
}

HtmlDocument::HtmlDocument(std::string_view htmlstr)
    : HtmlDocument()
{
    myhtml_parse(_tree, MyENCODING_UTF_8, htmlstr.data(), htmlstr.size());
}

HtmlDocument::~HtmlDocument()
{
    myhtml_tree_destroy(_tree);
}

bool HtmlDocument::parse(std::string_view htmlstr)
{
    return myhtml_parse(_tree, MyENCODING_UTF_8, htmlstr.data(), htmlstr.size()) == MyHTML_STATUS_OK;
}

NodePtr HtmlDocument::getRoot()
{
    myhtml_tree_node_t* doc = myhtml_tree_get_document(_tree);
    return std::make_shared<Node>(myhtml_node_child(doc), shared_from_this());
}

}
