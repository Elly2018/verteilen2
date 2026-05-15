#include <iostream>
#include "argh.h"

int main(int argc, char* argv[])
{
    argh::parser cmdl;
    cmdl.parse(argc, argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);

    if (cmdl[{ "-v", "--verbose" }])
        std::cout << "Verbose, I am.\n";

    return EXIT_SUCCESS;
}