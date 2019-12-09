// Copyright (c) 2018 The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The Liquidcash Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LCASHCOIN_ASSETFILTERPROXY_H
#define LCASHCOIN_ASSETFILTERPROXY_H

#include <QSortFilterProxyModel>

class AssetFilterProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit AssetFilterProxy(QObject *parent = 0);

    void setAssetNamePrefix(const QString &assetNamePrefix);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex & source_parent) const;

private:
    QString assetNamePrefix;
};


#endif //LCASHCOIN_ASSETFILTERPROXY_H
