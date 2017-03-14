#include "CaretCtrl.h"
#include "GraphBlock.h"

#include <vector>
using std::vector;

void Fun(CGraphBlock* p)
{

}

int main(int argc, char* argv[])
{
    //原始指针
    CGraphBlock* p = new CGraphBlock;
    CTextBlock* p1 = new CTextBlock;

    CCaretCtrl caret;
    caret.pBlock = p1;

    vector<CCaretCtrl> vec;
    vec.push_back(caret);

    //弱指针
    WeakPointer<CGraphBlock> pWeak;
    pWeak = nullptr;
    //赋值测试
    {
        WeakPointer<CTextBlock> pWeak1;
        pWeak1 = p1;
        pWeak  = pWeak1;
        pWeak1 = pWeak1;

        printf("pWeak == pWeak1, %d\n", pWeak == pWeak1);
        printf("pWeak != pWeak1, %d\n", pWeak != pWeak1);
    }

    //等于等于测试
    printf("pWeak == p1, %d\n", pWeak == p1);
    printf("pWeak == p, %d\n", pWeak == p);
    printf("pWeak == pWeak, %d\n", pWeak == pWeak);
    //printf("pWeak == 3, %d\n", pWeak == 3);

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    if (caret.pBlock) {
        printf("caret.pBlock, %d\n", 1);
    }
    
    //不等于测试
    printf("pWeak != nullptr, %d\n", pWeak != nullptr);
    printf("pWeak != p, %d\n", pWeak != p);
    printf("pWeak != p1, %d\n", pWeak != p1);
    printf("pWeak != pWeak, %d\n", pWeak != pWeak);

    delete p1;
    printf("delete p1\n");
    delete p;
    printf("delete p\n");

    //printf("pWeak != 3, %d\n", pWeak != 3);
    printf("pWeak != nullptr, %d\n", pWeak != nullptr);
    //////////////////////////////////////////////////////////////////////////
    printf("pWeak != nullptr, %d\n", pWeak != nullptr);
    printf("caret.pBlock != nullptr, %d\n", caret.pBlock != nullptr);

    if (!caret.pBlock) {
        printf("caret.pBlock == nullptr, %d\n", caret.pBlock == nullptr);
    }

    return 0;
}

