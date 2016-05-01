#include <string>
#include <vector>
#include <algorithm>
#include <exception>

#include "myers.h"

Myers::Myers() : tree_(), tail_(NO_LINK)
{
}

int Myers::diffImpl(int sizeA, int sizeB, const Comparator& comparator)
{
    const int& offset = sizeA;

    VItem* v = new VItem[sizeA + sizeB + 1];

    tree_.clear();
    tail_ = NO_LINK;

    for(int d = 0; d <= sizeA + sizeB; ++d)
    {
        for(int k = -d; k <= d; k += 2)
        {
            if((k < -sizeA) || (sizeB < k))
            {
                continue;
            }

            VItem* v_k   = v + k + offset;
            VItem* v_kp1 = v_k + 1;
            VItem* v_km1 = v_k - 1;

            if(d != 0)
            {
                if(((k == -d) || (k == -sizeA)) || (((k != d) && (k != sizeB)) && ((v_km1->y + 1) < v_kp1->y)))
                {
                    v_k->y    = v_kp1->y;
                    v_k->tail = tree_.size();
                    tree_.push_back(TreeNode(DELETE, v_kp1->tail));
                }
                else
                {
                    v_k->y    = v_km1->y + 1;
                    v_k->tail = tree_.size();
                    tree_.push_back(TreeNode(ADD, v_km1->tail));
                }
            }

            while(((v_k->y - k) < sizeA) && (v_k->y < sizeB) && comparator.isEqual(v_k->y - k, v_k->y))
            {
                TreeNode node(COMMON, v_k->tail);
                v_k->tail = tree_.size();
                tree_.push_back(node);
                ++v_k->y;
            }

            if(((v_k->y - k) >= sizeA) && (v_k->y >= sizeB))
            {
                tail_ = v_k->tail;
                delete[] v;
                return d;
            }
        }
    }
    delete[] v;
    throw Exception("not found");
}

void Myers::getSES(EditSequence& ses) const
{
    ses.clear();
    for(int i = tail_; i != NO_LINK; i = tree_[i].prev)
    {
        ses.push_back(tree_[i].editType);
    }
    std::reverse(ses.begin(), ses.end());
}
