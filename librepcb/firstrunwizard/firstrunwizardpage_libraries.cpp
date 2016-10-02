/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * http://librepcb.org/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/
#include <QtCore>
#include <QtWidgets>
#include "firstrunwizardpage_libraries.h"
#include "ui_firstrunwizardpage_libraries.h"
#include <librepcbcommon/uuid.h>
#include <librepcbcommon/network/repository.h>

/*****************************************************************************************
 *  Namespace
 ****************************************************************************************/
namespace librepcb {

/*****************************************************************************************
 *  Constructors / Destructor
 ****************************************************************************************/

FirstRunWizardPage_Libraries::FirstRunWizardPage_Libraries(QWidget *parent) noexcept :
    QWizardPage(parent), mUi(new Ui::FirstRunWizardPage_Libraries), mListUpdateActive(false)
{
    mUi->setupUi(this);
    registerField("LibrariesToInstall", this, "selectedLibraries", "selectedLibrariesChanged");
    connect(mUi->listWidget, &QListWidget::itemChanged,
            this, &FirstRunWizardPage_Libraries::listItemChanged);

    mRepository.reset(new Repository(QUrl("https://api.librepcb.org")));
    connect(mRepository.data(), &Repository::libraryListReceived,
            this, &FirstRunWizardPage_Libraries::libraryListReceived);
    connect(mRepository.data(), &Repository::errorWhileFetchingLibraryList,
            this, &FirstRunWizardPage_Libraries::errorWhileFetchingLibraryList);
}

FirstRunWizardPage_Libraries::~FirstRunWizardPage_Libraries() noexcept
{
}

/*****************************************************************************************
 *  Inherited Methods
 ****************************************************************************************/

void FirstRunWizardPage_Libraries::initializePage() noexcept
{
    mUi->listWidget->clear();
    mSelectedLibraries.clear();
    emit selectedLibrariesChanged(mSelectedLibraries);
    mRepository->requestLibraryList();
}

/*****************************************************************************************
 *  Private Methods
 ****************************************************************************************/

void FirstRunWizardPage_Libraries::libraryListReceived(const QJsonArray& libs) noexcept
{
    foreach (const QJsonValue& libVal, libs) {
        QJsonObject lib = libVal.toObject();
        QString name = lib.value("name").toObject().value("en_US").toString();
        QString desc = lib.value("description").toObject().value("en_US").toString();
        bool recommended = lib.value("recommended").toBool();

        mListUpdateActive = true;
        QListWidgetItem* item = new QListWidgetItem(mUi->listWidget);
        item->setText(QString("%1 - %2").arg(name, desc));
        item->setData(Qt::UserRole, lib);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        mListUpdateActive = false;
        item->setCheckState(recommended ? Qt::Checked : Qt::Unchecked);
    }
}

void FirstRunWizardPage_Libraries::errorWhileFetchingLibraryList(const QString& errorMsg) noexcept
{
    QListWidgetItem* item = new QListWidgetItem(errorMsg, mUi->listWidget);
    item->setBackgroundColor(Qt::red);
    item->setForeground(Qt::white);
}

void FirstRunWizardPage_Libraries::listItemChanged(const QListWidgetItem* item) noexcept
{
    if (mListUpdateActive || (!item)) return;

    if (item->checkState() == Qt::Checked) {
        // one more library is checked, check all dependencies too
        QSet<Uuid> libs;
        for (int i = 0; i < mUi->listWidget->count(); i++) {
            QListWidgetItem* item = mUi->listWidget->item(i); Q_ASSERT(item);
            if (item && (item->checkState() == Qt::Checked)) {
                libs.unite(getLibraryDependencies(item));
            }
        }
        for (int i = 0; i < mUi->listWidget->count(); i++) {
            QListWidgetItem* item = mUi->listWidget->item(i); Q_ASSERT(item);
            if (item && (libs.contains(getLibraryUuid(item)))) {
                item->setCheckState(Qt::Checked);
            }
        }
    } else {
        // one library was unchecked, uncheck all libraries with missing dependencies
        QSet<Uuid> libs;
        for (int i = 0; i < mUi->listWidget->count(); i++) {
            QListWidgetItem* item = mUi->listWidget->item(i); Q_ASSERT(item);
            if (item && (item->checkState() == Qt::Checked)) {
                libs.insert(getLibraryUuid(item));
            }
        }
        for (int i = 0; i < mUi->listWidget->count(); i++) {
            QListWidgetItem* item = mUi->listWidget->item(i); Q_ASSERT(item);
            if (item && (!libs.contains(getLibraryDependencies(item)))) {
                item->setCheckState(Qt::Unchecked);
            }
        }
    }

    // get list of selected libraries
    mSelectedLibraries.clear();
    for (int i = 0; i < mUi->listWidget->count(); i++) {
        QListWidgetItem* item = mUi->listWidget->item(i); Q_ASSERT(item);
        if (item && (item->checkState() == Qt::Checked)) {
            Uuid uuid = getLibraryUuid(item);
            if ((!uuid.isNull()) && (!mSelectedLibraries.contains(uuid.toStr()))) {
                mSelectedLibraries.append(uuid.toStr());
            }
        }
    }
    emit selectedLibrariesChanged(mSelectedLibraries);
}

Uuid FirstRunWizardPage_Libraries::getLibraryUuid(const QListWidgetItem* lib) const noexcept
{
    if ((lib) && (lib->data(Qt::UserRole).canConvert<QJsonObject>())) {
        QJsonObject obj = lib->data(Qt::UserRole).toJsonObject();
        Uuid uuid(obj.value("uuid").toString());
        if (!uuid.isNull()) {
            return uuid;
        } else {
            qWarning() << "Invalid dependency UUID:" << obj.value("uuid").toString();
            return Uuid();
        }
    } else {
        return Uuid();
    }
}

QSet<Uuid> FirstRunWizardPage_Libraries::getLibraryDependencies(const QListWidgetItem* lib) const noexcept
{
    QSet<Uuid> deps;
    if ((lib) && (lib->data(Qt::UserRole).canConvert<QJsonObject>())) {
        QJsonObject obj = lib->data(Qt::UserRole).toJsonObject();
        foreach (const QJsonValue& value, obj.value("dependencies").toArray()) {
            Uuid uuid(value.toString());
            if (!uuid.isNull()) {
                deps.insert(uuid);
            } else {
                qWarning() << "Invalid dependency UUID:" << value.toString();
            }
        }
    }
    return deps;
}

/*****************************************************************************************
 *  End of File
 ****************************************************************************************/

} // namespace librepcb
