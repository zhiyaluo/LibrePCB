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

#ifndef LIBREPCB_FIRSTRUNWIZARDPAGE_LIBRARIES_H
#define LIBREPCB_FIRSTRUNWIZARDPAGE_LIBRARIES_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/
#include <QtCore>
#include <QtWidgets>
#include <librepcbcommon/uuid.h>

/*****************************************************************************************
 *  Namespace / Forward Declarations
 ****************************************************************************************/
namespace librepcb {

class Repository;

namespace Ui {
class FirstRunWizardPage_Libraries;
}

/*****************************************************************************************
 *  Class FirstRunWizardPage_Libraries
 ****************************************************************************************/

/**
 * @brief The FirstRunWizardPage_Libraries class
 *
 * @author ubruhin
 * @date 2016-10-02
 */
class FirstRunWizardPage_Libraries final : public QWizardPage
{
        Q_OBJECT
        Q_PROPERTY(QStringList selectedLibraries MEMBER mSelectedLibraries)

    public:

        // Constructors / Destructor
        FirstRunWizardPage_Libraries(const FirstRunWizardPage_Libraries& other) = delete;
        explicit FirstRunWizardPage_Libraries(QWidget* parent = nullptr) noexcept;
        ~FirstRunWizardPage_Libraries() noexcept;

        // Inherited Methods
        void initializePage() noexcept override;

        // Operator Overloadings
        FirstRunWizardPage_Libraries& operator=(const FirstRunWizardPage_Libraries& rhs) = delete;


    signals:

        void selectedLibrariesChanged(const QStringList& libs);


    private: // Methods

        void clearLibraryList() noexcept;
        void libraryListReceived(const QJsonArray& libs) noexcept;
        void errorWhileFetchingLibraryList(const QString& errorMsg) noexcept;
        void listItemChanged(const QListWidgetItem* item) noexcept;
        Uuid getLibraryUuid(const QListWidgetItem* lib) const noexcept;
        QSet<Uuid> getLibraryDependencies(const QListWidgetItem* lib) const noexcept;


    private: // Data

        QScopedPointer<Ui::FirstRunWizardPage_Libraries> mUi;
        QScopedPointer<Repository> mRepository;
        QStringList mSelectedLibraries;
        bool mListUpdateActive;
};

/*****************************************************************************************
 *  End of File
 ****************************************************************************************/

} // namespace librepcb

#endif // LIBREPCB_FIRSTRUNWIZARDPAGE_LIBRARIES_H
