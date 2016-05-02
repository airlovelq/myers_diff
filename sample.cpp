#include <iostream>
#include <fstream>

#include "myers.h"
#include "sample.h"

void load(const std::string& filename, std::vector<std::string>& strings)
{
    strings.clear();

    std::ifstream src(filename.c_str());
    std::string   s;
    while(std::getline(src, s).good())
    {
        strings.push_back(s);
    }
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cout << argv[0] << " <file_a> <file_b>\n";
        return 0;
    }

    try
    {
        Myers                        myers;
        std::vector<Myers::EditType> ses;

        std::string filename_a(argv[1]);
        std::string filename_b(argv[2]);

        std::cout << "FILE NAME: " << myers.diff(filename_a, filename_b) << "\n";
        myers.get_ses(ses);
        show_diff(ses, filename_a, filename_b);

        std::cout << "\n";

        std::vector<std::string> strings_a;
        std::vector<std::string> strings_b;

        load(filename_a, strings_a);
        load(filename_b, strings_b);

        std::cout << "CONTENTS: " << myers.diff(strings_a.begin(), strings_a.end(), strings_b.begin(), strings_b.end()) << "\n";

        ses.resize(myers.ses_size());
        myers.get_ses(ses.begin(), ses.end());
        show_diff(ses, strings_a, strings_b);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
