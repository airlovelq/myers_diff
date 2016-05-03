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
    using namespace emattsan::myers;

    if(argc != 3)
    {
        std::cout << argv[0] << " <file_a> <file_b>\n";
        return 0;
    }

    try
    {
        std::string filename_a(argv[1]);
        std::string filename_b(argv[2]);

        std::vector<EditType> ses = diff(filename_a, filename_b);
        std::cout << show_diff(ses, filename_a.begin(), filename_b.begin());

        std::cout << "\n";

        std::vector<std::string> strings_a;
        std::vector<std::string> strings_b;

        load(filename_a, strings_a);
        load(filename_b, strings_b);

        ses = diff(strings_a.begin(), strings_a.end(), strings_b.begin(), strings_b.end());
        std::cout << show_diff(ses, strings_a.begin(), strings_b.begin());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
