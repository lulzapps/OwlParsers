#pragma once

#include <string>

// #include <myhtml/api.h>
// #include <myhtml/myhtml.h>
#include <myhtml/myhtml.h>
#include <myhtml/serialization.h>

namespace owl::html
{

using HtmlPtr = std::unique_ptr<myhtml_t>;
using TreePtr = std::unique_ptr<myhtml_tree_t>;

class Node final
{
public:
private:
};

class Tree final
{

public:
    Tree();
    Tree(std::string_view htmlstr);

    virtual ~Tree();

    bool parse(std::string_view htmlstr);

private:
    HtmlPtr _html;
    TreePtr _tree;    

};

} // namespace owl

