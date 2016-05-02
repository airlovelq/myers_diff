#ifndef EMATTSAN_SAMPLE_H__
#define EMATTSAN_SAMPLE_H__

template<typename iterator_t, typename contailer_t>
void show_diff(const contailer_t& ses, const iterator_t& first_a, const iterator_t& first_b)
{
    iterator_t a = first_a;
    iterator_t b = first_b;
    typename contailer_t::const_iterator end_of_ses = std::end(ses);
    for(typename contailer_t::const_iterator i = std::begin(ses); i != end_of_ses; ++i)
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
