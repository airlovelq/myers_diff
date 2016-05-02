#ifndef EMATTSAN_SAMPLE_H__
#define EMATTSAN_SAMPLE_H__

template<typename sequence_t>
void show_diff(const std::vector<Myers::EditType>& ses, const sequence_t& sequenceA, const sequence_t& sequenceB)
{
    auto a = std::begin(sequenceA);
    auto b = std::begin(sequenceB);
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

#endif//EMATTSAN_SAMPLE_H__
