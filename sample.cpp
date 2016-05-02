#include <iostream>
#include <fstream>

#include "myers.h"

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

template<typename sequence_t>
void showDiff(const std::vector<Myers::EditType>& ses, const sequence_t& sequenceA, const sequence_t& sequenceB)
{
    typename sequence_t::const_iterator a = sequenceA.begin();
    typename sequence_t::const_iterator b = sequenceB.begin();
    for(std::vector<Myers::EditType>::const_iterator i = ses.begin(); i != ses.end(); ++i)
    {
        switch(*i)
        {
        case Myers::DELETE:
            std::cout << "- " << *a;
            ++a;
            break;

        case Myers::COMMON:
            std::cout << "  " << *a;
            ++a;
            ++b;
            break;

        case Myers::ADD:
            std::cout << "+ " << *b;
            ++b;
            break;

        default:
            break;
        }
        std::cout << "\n";
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
        showDiff(ses, filenameA, filenameB);

        std::cout << "\n";

        std::vector<std::string> stringsA;
        std::vector<std::string> stringsB;

        load(filenameA, stringsA);
        load(filenameB, stringsB);

        std::cout << "CONTENTS: " << myers.diff(stringsA, stringsB) << "\n";
        ses.clear();
        myers.get_ses(ses);
        showDiff(ses, stringsA, stringsB);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
