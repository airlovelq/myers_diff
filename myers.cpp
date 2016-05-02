#include <vector>

#include "myers.h"

namespace
{

static const int NO_LINK = -1;

struct VItem
{
    int y;
    int tail;

    VItem(int y = 0, int tail = NO_LINK) : y(y), tail(tail) {}
};

struct TreeNode
{
    Myers::EditType edit_type;
    int             prev;

    TreeNode(Myers::EditType edit_type, int prev) : edit_type(edit_type), prev(prev) {}
};

} // anonymous namespace

Myers::Myers() : ses_()
{
}

int Myers::diff_inpl(int size_a, int size_b, const SequencesContainer& sequences)
{
    const int& offset = size_a;

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

            std::vector<VItem>::iterator v_k   = v.begin() + k + offset;
            std::vector<VItem>::iterator v_kp1 = v_k + 1;
            std::vector<VItem>::iterator v_km1 = v_k - 1;

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

            while(((v_k->y - k) < size_a) && (v_k->y < size_b) && sequences.equals(v_k->y - k, v_k->y))
            {
                TreeNode node(COMMON, v_k->tail);
                v_k->tail = tree.size();
                tree.push_back(node);
                ++v_k->y;
            }

            if(((v_k->y - k) >= size_a) && (v_k->y >= size_b))
            {
                tail = v_k->tail;

                ses_.clear();
                for(int i = tail; i != NO_LINK; i = tree[i].prev)
                {
                    ses_.push_back(tree[i].edit_type);
                }

                return d;
            }
        }
    }
    throw Exception("not found");
}
