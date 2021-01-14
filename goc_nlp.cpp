#include "goc_nlp.hpp"
#include "main_1.hpp"
using namespace Ipopt;

GOC_NLP::GOC_NLP() {}

GOC_NLP::~GOC_NLP() {}

bool GOC_NLP::eval_g
(
    Index n,
    const Number* x,
    bool new_w,
    Index m,
    Number* g
)
{
    for (size_t idx=0; idx<I.size(); idx++)
    {
        g[idx] = 

    }
    
    
}