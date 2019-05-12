#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <QObject>

class Authenticator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool validCredentials READ getValidCredentials WRITE setValidCredentials NOTIFY validCredentials)

public:
    Authenticator();
    bool getValidCredentials() const;

public slots:
    void setValidCredentials(bool validCredentials);

signals:
    void validCredentials(bool validCredentials);
    void invalidCredentials(bool invalidCredentials);

private:
    bool validCredentials_;
};

#endif // AUTHENTICATOR_H
