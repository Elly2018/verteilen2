#include <iostream>
#include <string>
#include <algorithm>
#include "argh.h"
#include "category.h"

/// @brief Handle the help category
/// @param cmdl argument worker
/// @return True if it catch result
bool handle_help(argh::parser& cmdl){

    std::string help_sub_text = "";
    
    if (cmdl.flags().count("h") || cmdl.flags().count("help")){
        print_help();
        return true;
    }

    if(cmdl.params().count("help")){
        help_sub_text = cmdl.params().at("help");
    }

    if(cmdl.params().count("h")){
        help_sub_text = cmdl.params().at("h");
    }

    std::transform(help_sub_text.begin(), help_sub_text.end(), help_sub_text.begin(), [](unsigned char c){ return std::tolower(c); });

    if(help_sub_text.size() > 0){
        if(help_sub_text == "master"){
            print_help_master();
        }
        else if(help_sub_text == "client"){
            print_help_client();
        }
        else if(help_sub_text == "proxy"){
            print_help_proxy();
        }
        else{
            printf("Cannot find the module: %s\n", help_sub_text.c_str());
            printf("Type --help to find the CLI usage\n");
        }
        return true;
    }

    return false;
}

bool handle_master(argh::parser& cmdl){

}

bool handle_client(argh::parser& cmdl){
    
}

bool handle_proxy(argh::parser& cmdl){
    
}

int main(int argc, char* argv[])
{
    argh::parser cmdl;
    cmdl.parse(argc, argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);
    if(handle_help(cmdl)){
        return EXIT_SUCCESS;
    }

    printf("Finish Program...\n");

    return EXIT_SUCCESS;
}