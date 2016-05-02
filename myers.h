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

    Myers() : ses_() {}

    template<typename sequence_t>
    int diff(const sequence_t& sequence_a, const sequence_t& sequence_b)
    {
        return diff(std::begin(sequence_a), std::end(sequence_a), std::begin(sequence_b), std::end(sequence_b));
    }

    template<typename iterator_t>
    int diff(iterator_t first_a, iterator_t last_a, iterator_t first_b, iterator_t last_b)
    {
        const int size_a = std::distance(first_a, last_a);
        const int size_b = std::distance(first_b, last_b);
        const int offset = size_a;

        std::vector<VItem> v(size_a + size_b + 1);

        std::vector<TreeNode> tree;
        int tail = NO_LINK;

        for(int d = 0; d <= size_a + size_b; ++d)
        {
            for(int k = -d; k <= d; k += 2)
            {
                if((k < -size_a) || (size_b < k))
                {
                    continue;
                }

                auto v_k   = v.begin() + k + offset;
                auto v_kp1 = v_k + 1;
                auto v_km1 = v_k - 1;

                if(d != 0)
                {
                    if(((k == -d) || (k == -size_a)) || (((k != d) && (k != size_b)) && ((v_km1->y + 1) < v_kp1->y)))
                    {
                        v_k->y    = v_kp1->y;
                        v_k->tail = tree.size();
                        tree.push_back(TreeNode(DELETE, v_kp1->tail));
                    }
                    else
                    {
                        v_k->y    = v_km1->y + 1;
                        v_k->tail = tree.size();
                        tree.push_back(TreeNode(ADD, v_km1->tail));
                    }
                }

                while(((v_k->y - k) < size_a) && (v_k->y < size_b) && (*(first_a + v_k->y - k) == *(first_b + v_k->y)))
                {
                    TreeNode node(COMMON, v_k->tail);
                    v_k->tail = tree.size();
                    tree.push_back(node);
                    ++v_k->y;
                }

                if(((v_k->y - k) >= size_a) && (v_k->y >= size_b))
                {
                    ses_.clear();
                    for(int i = v_k->tail; i != NO_LINK; i = tree[i].prev)
                    {
                        ses_.push_back(tree[i].edit_type);
                    }

                    return d;
                }
            }
        }
        throw Exception("not found");
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
    void get_ses(iterator_t first, iterator_t last) const
    {
        std::copy_n(ses_.rbegin(), std::min(ses_.size(), static_cast<std::vector<EditType>::size_type>(std::distance(first, last))), first);
    }

private:
    static const int NO_LINK = -1;

    struct VItem
    {
        int y;
        int tail;

        VItem(int y = 0, int tail = NO_LINK) : y(y), tail(tail) {}
    };

    struct TreeNode
    {
        EditType edit_type;
        int      prev;

        TreeNode(EditType edit_type, int prev) : edit_type(edit_type), prev(prev) {}
    };

    std::vector<EditType> ses_;
};
