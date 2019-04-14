#ifndef CONVERSATIONMODEL_H
#define CONVERSATIONMODEL_H

#include <QSqlTableModel>

class ConversationModel : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(QString userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString groupId READ groupId WRITE setGroupId NOTIFY groupIdChanged)

public:
    explicit ConversationModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // ID of the current user
    QString userId() const;
    void setUserId(const QString &userId);

    // ID of the group that holds the conversation
    QString groupId() const;
    void setGroupId(const QString &groupId);

    Q_INVOKABLE void sendMessage(const QString &message);

signals:
    void userIdChanged();
    void groupIdChanged();

private:
    QString userId_;
    QString groupId_;

    const static char* COLUMN_NAMES[];
};

#endif // CONVERSATIONMODEL_H
