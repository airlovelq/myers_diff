#ifndef EMATTSAN_SAMPLE_H__
#define EMATTSAN_SAMPLE_H__

#include <iostream>

template<typename iterator_t, typename contailer_t>
struct SesShower
{
    const contailer_t& ses;
    const iterator_t& first_a;
    const iterator_t& first_b;

    SesShower(const contailer_t& ses, const iterator_t& first_a, const iterator_t& first_b) : ses(ses), first_a(first_a), first_b(first_b) {}
};

template<typename iterator_t, typename contailer_t>
std::ostream& operator << (std::ostream& out, const SesShower<iterator_t, contailer_t>& shower)
{
    iterator_t a = shower.first_a;
    iterator_t b = shower.first_b;
    typename contailer_t::const_iterator end_of_ses = std::end(shower.ses);
    for(typename contailer_t::const_iterator i = std::begin(shower.ses); i != end_of_ses; ++i)
    {
        switch(*i)
        {
        case Myers::DELETE:
            out << "- " << *a;
            ++a;
            break;

        case Myers::COMMON:
            out << "  " << *a;
            ++a;
            ++b;
            break;

        case Myers::ADD:
            out << "+ " << *b;
            ++b;
            break;

        default:
            break;
        }
        out << "\n";
    }

    return out;
}

template<typename iterator_t, typename contailer_t>
SesShower<iterator_t, contailer_t> show_diff(const contailer_t& ses, const iterator_t& first_a, const iterator_t& first_b)
{
    return SesShower<iterator_t, contailer_t>(ses, first_a, first_b);
}

#endif//EMATTSAN_SAMPLE_H__
