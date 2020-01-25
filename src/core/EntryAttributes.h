/*
 *  Copyright (C) 2012 Felix Geyer <debfx@fobos.de>
 *  Copyright (C) 2017 KeePassXC Team <team@keepassxc.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KEEPASSX_ENTRYATTRIBUTES_H
#define KEEPASSX_ENTRYATTRIBUTES_H

#include <QMap>
#include <QObject>
#include <QRegularExpression>
#include <QSet>
#include <QStringList>
#include <QUuid>

class EntryAttributes : public QObject
{
    Q_OBJECT

public:
    explicit EntryAttributes(QObject* parent = nullptr);
    QList<QString> keys() const;
    bool hasKey(const QString& key) const;
    QList<QString> customKeys() const;
    QString value(const QString& key) const;
    QList<QString> values(const QList<QString>& keys) const;
    bool contains(const QString& key) const;
    bool containsValue(const QString& value) const;
    bool isProtected(const QString& key) const;
    bool isReference(const QString& key) const;
    void set(const QString& key, const QString& value, bool protect = false);
    void remove(const QString& key);
    void rename(const QString& oldKey, const QString& newKey);
    void copyCustomKeysFrom(const EntryAttributes* other);
    bool areCustomKeysDifferent(const EntryAttributes* other);
    void clear();
    int attributesSize() const;
    void copyDataFrom(const EntryAttributes* other);
    QUuid referenceUuid(const QString& key) const;
    bool operator==(const EntryAttributes& other) const;
    bool operator!=(const EntryAttributes& other) const;

    static QRegularExpressionMatch matchReference(const QString& text);

    static const QString TitleKey;
    static const QString UserNameKey;
    static const QString PasswordKey;
    static const QString URLKey;
    static const QString NotesKey;
    static const QString UuidKey;
    static const QStringList DefaultAttributes;
    static const QString RememberCmdExecAttr;
    static bool isDefaultAttribute(const QString& key);

    static const QString WantedFieldGroupName;
    static const QString SearchInGroupName;
    static const QString SearchTextGroupName;

signals:
    void entryAttributesModified();
    void defaultKeyModified();
    void customKeyModified(const QString& key);
    void aboutToBeAdded(const QString& key);
    void added(const QString& key);
    void aboutToBeRemoved(const QString& key);
    void removed(const QString& key);
    void aboutToRename(const QString& oldKey, const QString& newKey);
    void renamed(const QString& oldKey, const QString& newKey);
    void aboutToBeReset();
    void reset();

private:
    QMap<QString, QString> m_attributes;
    QSet<QString> m_protectedAttributes;
};

#endif // KEEPASSX_ENTRYATTRIBUTES_H
