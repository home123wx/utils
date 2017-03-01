#include "WeakPointer.hpp"

class CGraphBlock : public WeakTagPointer<CGraphBlock> {
public:
    void doing()
    {
        printf("CGraphBlock do something!\n");
    }
};

class CTextBlock : public CGraphBlock {
public:
    void doing()
    {
        printf("CTextBlock do something!\n");
    }
};

void Fun(CGraphBlock* p)
{

}

int main(int argc, char* argv[])
{
    CGraphBlock* p = new CGraphBlock;
    CTextBlock* p1 = new CTextBlock;

    p->doing();
    p1->doing();

    WeakPointer<CGraphBlock> pTmp;
    pTmp = NULL;

    WeakPointer<CGraphBlock> pWeak;
    {
        WeakPointer<CTextBlock> pWeak1;
        pWeak1 = p1;
        pWeak = pWeak1;
        pWeak1 = pWeak1;
        if (pWeak1 != NULL) {
            (*pWeak1).doing();
        }

        if (pWeak == pWeak1) {
            printf("相同\n");
        }
    }

	if (pWeak == p1) {
    	printf("相同\n");
	}

	if (pWeak == p) {
    	printf("相同\n");
	} else {
    	printf("不同\n");
	}	

    //////////////////////////////////////////////////////////////////////////
    if (pWeak != NULL) {
        printf("pweak 有效\n");
        pWeak->doing();
    }
    //////////////////////////////////////////////////////////////////////////

    delete p1;

    //////////////////////////////////////////////////////////////////////////
    if (pWeak != NULL) {
        printf("pweak 有效\n");
        pWeak->doing();
    } else {
        printf("pweak 无效\n");
    }
    //////////////////////////////////////////////////////////////////////////

	return 0;
}

