#ifndef GROUPSMODEL_H
#define GROUPSMODEL_H

#include <QAbstractListModel>

class GroupsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AnimalRoles {
        IdRole = Qt::UserRole + 1,
        NameRole
    };

    GroupsModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void replaceUserGroups(QList<QPair<QString,QString>> userGroups);

    QList<QPair<QString,QString>> getUserGroups();

private:
    QVector<QString> groups_;
    QList<QPair<QString,QString>> userGroups_;
};

#endif // GROUPSMODEL_H
