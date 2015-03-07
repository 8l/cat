#include <cat/string_view.hpp>
#include <vector>

#include "yats.hpp"

using namespace yats;
using namespace cat;

// Tests:
//

Context(test_read)
{
    Test (consume)
    {
        string_view spaces("    ");
        string_view s(" hello world ");

        Assert( cat::consume('x', spaces) == nullopt);
        Assert( cat::consume('x', s) == nullopt);
        Assert( cat::consume('h', s).value() == string_view{"ello world "});

        Assert( cat::consume("ciao", spaces) == nullopt);
        Assert( cat::consume("ciao", s) == nullopt);
        Assert( cat::consume("hello", s).value() == string_view{" world "});
    }

    Test(trim)
    {
        Assert(cat::trim("") == string_view{});
        Assert(cat::trim("   ") == string_view{});
        Assert(cat::trim("hello world") == string_view{"hello world"});
        Assert(cat::trim("    hello world") == string_view{"hello world"});
        Assert(cat::trim("hello world   ") == string_view{"hello world"});
        Assert(cat::trim("   hello world   ") == string_view{"hello world"});
    }

    Test(split)
    {
        Assert(cat::split("", "***") == std::vector<std::string>{""});
        Assert(cat::split("***", "***") == std::vector<std::string>{"", ""});
        Assert(cat::split("aaa", "***") == std::vector<std::string>{"aaa"});
        Assert(cat::split("***aaa", "***") == std::vector<std::string>{"", "aaa"});
        Assert(cat::split("aaa***", "***") == std::vector<std::string>{"aaa", ""});
        Assert(cat::split("aaa***bbb", "***") == std::vector<std::string>{"aaa", "bbb"});
    }
}


int
main(int argc, char*  argv[])
{
    return yats::run(argc, argv);
}

