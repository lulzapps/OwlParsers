#pragma once

#include <string>

// #include <myhtml/api.h>
// #include <myhtml/myhtml.h>
#include <myhtml/myhtml.h>
#include <myhtml/serialization.h>

namespace owl::html
{

class Attribute;
using AttributePtr = std::shared_ptr<Attribute>;

class Node;
using NodePtr = std::shared_ptr<Node>;

class HtmlDocument;
using HtmlDocumentPtr = std::shared_ptr<HtmlDocument>;

class Attribute
{

public:
    Attribute(myhtml_tree_attr_t* attr, HtmlDocumentPtr parent)
        : _attr{attr}, _parent{parent}
    {
        // nothing to do
    }

    std::string_view getKey() const
    {
        return myhtml_attribute_key(_attr, nullptr);
    }

    std::string_view getValue() const
    {
        return myhtml_attribute_value(_attr, nullptr);
    }

    AttributePtr getNext() const
    {
        if (auto parent = _parent.lock(); parent)
        {
            auto next = myhtml_attribute_next(_attr);
            return std::make_shared<Attribute>(next, parent);
        }

        return {};
    }

private:
    myhtml_tree_attr_t*         _attr = nullptr;
    std::weak_ptr<HtmlDocument> _parent;
};

class Node final
{

public:
    Node(myhtml_tree_node_t* node, HtmlDocumentPtr parent);

    std::string_view getName() const;

    NodePtr getNext() const;
    NodePtr getFirstChild() const;

    AttributePtr getFirstAttribute()
    {
        if (auto parent = _parent.lock(); parent)
        {
            myhtml_tree_attr_t* attr = myhtml_node_attribute_first(_node);
            return std::make_shared<Attribute>(attr, parent);
        }

        return {};
    }

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
    NodePtr getHead();
    NodePtr getBody();

private:
    friend class Node;

    myhtml_t*       _html;
    myhtml_tree_t*  _tree;
};

} // namespace owl

