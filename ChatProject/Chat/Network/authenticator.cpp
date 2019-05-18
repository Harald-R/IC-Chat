#include "authenticator.h"

Authenticator::Authenticator()
{
}

bool Authenticator::getValidCredentials() const
{
    return validCredentials_;
}

void Authenticator::setValidCredentials(bool val)
{
    validCredentials_ = val;
    if (validCredentials_)
        emit validCredentials(val);
    else
        emit invalidCredentials(val);
}
