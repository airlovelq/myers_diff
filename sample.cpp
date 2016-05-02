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

        std::string filenameA(argv[1]);
        std::string filenameB(argv[2]);

        std::cout << "FILE NAME: " << myers.diff(filenameA, filenameB) << "\n";
        myers.get_ses(ses);
        show_diff(ses, filenameA, filenameB);

        std::cout << "\n";

        std::vector<std::string> stringsA;
        std::vector<std::string> stringsB;

        load(filenameA, stringsA);
        load(filenameB, stringsB);

        std::cout << "CONTENTS: " << myers.diff(stringsA.begin(), stringsA.end(), stringsB.begin(), stringsB.end()) << "\n";

        ses.resize(myers.ses_size());
        myers.get_ses(ses.begin(), ses.end());
        show_diff(ses, stringsA, stringsB);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
