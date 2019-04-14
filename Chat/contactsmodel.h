#ifndef CONTACTSMODEL_H
#define CONTACTSMODEL_H

#include <QSqlQueryModel>

class ContactsModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit ContactsModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    const static char* COLUMN_NAMES[];
    const static char* SQL_SELECT;
};

#endif // CONTACTSMODEL_H
