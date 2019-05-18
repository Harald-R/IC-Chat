#ifndef CONVERSATIONMODEL_H
#define CONVERSATIONMODEL_H

#include <QAbstractListModel>
#include "message.h"

class ConversationModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString group_id READ groupId WRITE setGroupId NOTIFY groupIdChanged)
    Q_PROPERTY(QString my_user_id READ myUserId WRITE setmyUserId NOTIFY myUserIdChanged)

public:
    enum ConversationRoles {
        AuthorRole = Qt::UserRole + 1,
        GroupIdRole,
        ContentRole,
        DateRole
    };

    ConversationModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void insert(QMap<QString, QString> message);
    void clear();
    QString groupId() const;
    QString myUserId() const;

public slots:
    void setGroupId(QString groupId);
    void setmyUserId(QString my_user_id);

signals:
    void groupIdChanged(QString groupId);
    void myUserIdChanged(QString my_user_id);

private:
    QList<Message> messages_;
    QString groupId_;
    QString myUserId_;
};

#endif // CONVERSATIONMODEL_H
