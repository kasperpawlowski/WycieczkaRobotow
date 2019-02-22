#include "basictypes.h"

DisplayableObjectType& DisplayableObjectType::operator=(const DisplayableObjectType& right)
{
    if(&right != this)
    {
        this->pos_    = right.pos_;
        this->pixmap_ = right.pixmap_;
    }
    return *this;
}
