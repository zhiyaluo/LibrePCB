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

#ifndef LIBREPCB_DESIGNATORSTRING_H
#define LIBREPCB_DESIGNATORSTRING_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/
#include <QtCore>

/*****************************************************************************************
 *  Namespace / Forward Declarations
 ****************************************************************************************/
namespace librepcb {

/*****************************************************************************************
 *  Class DesignatorString
 ****************************************************************************************/

/**
 * @brief The DesignatorString class
 *
 * @author ubruhin
 * @date 2017-01-17
 */
class DesignatorString final
{
    public:

        // Constructors / Destructor

        /**
         * @brief Default constructor (creates an invalid #DesignatorString object)
         */
        DesignatorString() noexcept;

        /**
         * @brief Constructor which creates a #DesignatorString object from a given QString
         *
         * @param string    See #setString()
         */
        explicit DesignatorString(const QString& value) noexcept;

        /**
         * @brief Copy constructor
         *
         * @param other     Another #DesignatorString object
         */
        DesignatorString(const DesignatorString& other) noexcept;

        /**
         * Destructor
         */
        ~DesignatorString() noexcept;


        // Getters

        /**
         * @brief Check if the object represents a valid designator string
         *
         * @return true = valid, false = invalid
         */
        bool isValid() const noexcept {return false;}

        /**
         * @brief Convert the #DesignatorString to a QString
         *
         * @return The #DesignatorString as a QString (empty if invalid)
         */
        QString toQString() const noexcept {return mValue;}


        // Setters

        /**
         * @brief Set the value (designator string) of the object
         *
         * If the value is valid, the object will be valid too. Otherwise the object will
         * be invalid.
         *
         * @param string   The new designator string
         *
         * @return validity of the #DesignatorString (true = valid, false = invalid)
         */
        bool setValue(const QString& value) noexcept;


        // Operator overloadings
        DesignatorString& operator=(const DesignatorString& rhs) noexcept;

        //@{
        /**
         * @brief Comparison operators
         *
         * @param rhs   The other object to compare
         *
         * @return  If at least one of both objects is invalid, false will be returned
         *          (except #operator!=() which would return true in this case)!
         */
        bool operator>(const DesignatorString& rhs) const noexcept;
        bool operator<(const DesignatorString& rhs) const  noexcept;
        bool operator>=(const DesignatorString& rhs) const noexcept;
        bool operator<=(const DesignatorString& rhs) const noexcept;
        bool operator==(const DesignatorString& rhs) const noexcept;
        bool operator!=(const DesignatorString& rhs) const noexcept;
        //@}


        // Static Methods

        /**
         * @brief checkValidity
         * @param value
         * @return
         */
        static bool checkValidity(const QString& value) noexcept;


    private: // Methods

        /**
         * @brief Compare method for operator overloadings
         *
         * @param other     The other object for the comparison
         *
         * @return -1:  this < other
         *          0:  this == other (or at least one of the objects is invalid)
         *          1:  this > other
         */
        int compare(const DesignatorString& other) const noexcept;


    private: // Data
        QString mValue;
};

/*****************************************************************************************
 *  End of File
 ****************************************************************************************/

} // namespace librepcb

#endif // LIBREPCB_DESIGNATORSTRING_H
