#ifndef _GRAPH_BLOCK_H_
#define _GRAPH_BLOCK_H_

#include "WeakPointer.hpp"

class CGraphBlock : public WeakTagPointer<CGraphBlock> {
public:
    void doing(const char* s)
    {
        printf("%s\n", s);
    }
};

class CTextBlock : public CGraphBlock {

};

#endif //_GRAPH_BLOCK_H_
