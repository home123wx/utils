#include "CaretCtrl.h"
#include "GraphBlock.h"

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

    //弱指针
    WeakPointer<CGraphBlock> pWeak;
    pWeak = NULL;
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
    printf("pWeak != NULL, %d\n", pWeak != NULL);
    printf("pWeak != p, %d\n", pWeak != p);
    printf("pWeak != p1, %d\n", pWeak != p1);
    printf("pWeak != pWeak, %d\n", pWeak != pWeak);

    delete p1;

    printf("pWeak != 3, %d\n", pWeak != 3);
    //////////////////////////////////////////////////////////////////////////
    printf("pWeak != NULL, %d\n", pWeak != NULL);
    printf("caret.pBlock != NULL, %d\n", caret.pBlock != NULL);

    if (!caret.pBlock) {
        printf("caret.pBlock == NULL, %d\n", caret.pBlock == NULL);
    }

    return 0;
}

