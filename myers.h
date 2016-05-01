#include <string>
#include <vector>
#include <exception>

class Myers
{
public:
    enum EditType { DELETE, COMMON, ADD };

    typedef std::vector<EditType> EditSequence;

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
        return diff_inpl(sequence_a.size(), sequence_b.size(), ComparatorImpl<sequence_t>(sequence_a, sequence_b));
    }

    void getSES(EditSequence& ses) const;

private:
    static const int NO_LINK = -1;

    struct TreeNode
    {
        EditType edit_type;
        int      prev;

        TreeNode(EditType edit_type, int prev) : edit_type(edit_type), prev(prev) {}
    };

    struct VItem
    {
        int y;
        int tail;

        VItem(int y = 0, int tail = NO_LINK) : y(y), tail(tail) {}
    };

    struct Comparator
    {
        virtual ~Comparator() {}
        virtual bool isEqual(int x, int y) const = 0;
    };

    template<typename sequence_t>
    struct ComparatorImpl : public Comparator
    {
        const sequence_t& sequence_a;
        const sequence_t& sequence_b;

        ComparatorImpl(const sequence_t& sequence_a, const sequence_t& sequence_b) : sequence_a(sequence_a), sequence_b(sequence_b) {}

        bool isEqual(int x, int y) const
        {
            return sequence_a.at(x) == sequence_b.at(y);
        }
    };

    int diff_inpl(int size_a, int size_b, const Comparator& comparator);

    std::vector<TreeNode> tree_;
    int                   tail_;
};
