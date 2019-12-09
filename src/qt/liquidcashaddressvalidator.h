// Copyright (c)  The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The Liquidcash Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LCASH_QT_LCASHADDRESSVALIDATOR_H
#define LCASH_QT_LCASHADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class LiquidcashAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit LiquidcashAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Liquidcash address widget validator, checks for a valid liquidcash address.
 */
class LiquidcashAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit LiquidcashAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // LCASH_QT_LCASHADDRESSVALIDATOR_H
