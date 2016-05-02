#include <string>
#include <vector>
#include <exception>
#include <algorithm>
#include <iterator>

class Myers
{
public:
    enum EditType { DELETE, COMMON, ADD };

    class Exception : public std::exception
    {
    public:
        explicit Exception(const char* what) : std::exception(), what_(what) {}
        ~Exception() throw() {}
        const char* what() const throw() { return what_.c_str(); }

    private:
        std::string what_;
    };

    Myers();

    template<typename sequence_t>
    int diff(const sequence_t& sequence_a, const sequence_t& sequence_b)
    {
        return diff_inpl(sequence_a.size(), sequence_b.size(), SequencesContainerImpl<sequence_t>(sequence_a, sequence_b));
    }

    int ses_size() const
    {
        return ses_.size();
    }

    template<typename container_t>
    void get_ses(container_t& ses) const
    {
        std::copy(ses_.rbegin(), ses_.rend(), std::back_inserter(ses));
    }

    template<typename iterator_t>
    void get_ses(iterator_t first, iterator_t last)
    {
        std::copy_n(ses_.rbegin(), std::min(ses_.size(), static_cast<std::vector<EditType>::size_type>(std::distance(first, last))), first);
    }

private:
    struct SequencesContainer
    {
        virtual ~SequencesContainer() {}
        virtual bool equals(int x, int y) const = 0;
    };

    template<typename sequence_t>
    struct SequencesContainerImpl : public SequencesContainer
    {
        const sequence_t& sequence_a;
        const sequence_t& sequence_b;

        SequencesContainerImpl(const sequence_t& sequence_a, const sequence_t& sequence_b) : sequence_a(sequence_a), sequence_b(sequence_b) {}

        bool equals(int x, int y) const
        {
            return sequence_a.at(x) == sequence_b.at(y);
        }
    };

    int diff_inpl(int size_a, int size_b, const SequencesContainer& sequences);

    std::vector<EditType> ses_;
};
