#pragma once

#include <string>

namespace owl
{

class Parser
{

public:

    std::string name() const { return _name; }


private:
    std::string _name;

};

} // namespace owl

