#pragma once

#include <string>

// #include <myhtml/api.h>
// #include <myhtml/myhtml.h>
#include <myhtml/myhtml.h>
#include <myhtml/serialization.h>

namespace owl::html
{

class Node;
using NodePtr = std::shared_ptr<Node>;

class HtmlDocument;
using HtmlDocumentPtr = std::shared_ptr<HtmlDocument>;

class Node final
{

public:
    Node(myhtml_tree_node_t* node, HtmlDocumentPtr parent);

    std::string_view getName() const;

    NodePtr getNext() const;
    NodePtr getFirstChild() const;

private:
    myhtml_tree_node_t*         _node = nullptr;
    std::weak_ptr<HtmlDocument> _parent;

};

class HtmlDocument final
    : public std::enable_shared_from_this<HtmlDocument>
{

public:
    HtmlDocument();
    HtmlDocument(std::string_view htmlstr);

    virtual ~HtmlDocument();

    bool parse(std::string_view htmlstr);

    NodePtr getRoot();

private:
    friend class Node;

    myhtml_t*       _html;
    myhtml_tree_t*  _tree;
};

} // namespace owl

