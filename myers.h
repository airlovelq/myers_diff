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
    int diff(const sequence_t& sequenceA, const sequence_t& sequenceB)
    {
        return diffImpl(sequenceA.size(), sequenceB.size(), ComparatorImpl<sequence_t>(sequenceA, sequenceB));
    }

    void getSES(EditSequence& ses) const;

private:
    static const int NO_LINK = -1;

    struct TreeNode
    {
        EditType editType;
        int      prev;

        TreeNode(EditType editType, int prev) : editType(editType), prev(prev) {}
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
        const sequence_t& sequenceA;
        const sequence_t& sequenceB;

        ComparatorImpl(const sequence_t& sequenceA, const sequence_t& sequenceB) : sequenceA(sequenceA), sequenceB(sequenceB) {}

        bool isEqual(int x, int y) const
        {
            return sequenceA.at(x) == sequenceB.at(y);
        }
    };

    int diffImpl(int sizeA, int sizeB, const Comparator& comparer);

    std::vector<TreeNode> tree_;
    int                   tail_;
};
