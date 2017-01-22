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
#include "designatorstring.h"

/*****************************************************************************************
 *  Namespace
 ****************************************************************************************/
namespace librepcb {

/*****************************************************************************************
 *  Constructors / Destructor
 ****************************************************************************************/

DesignatorString::DesignatorString() noexcept
{
}

DesignatorString::DesignatorString(const QString& value) noexcept
{
    setValue(value);
}

DesignatorString::DesignatorString(const DesignatorString& other) noexcept :
    mValue(other.mValue)
{

}

DesignatorString::~DesignatorString() noexcept
{
}

/*****************************************************************************************
 *  Setters
 ****************************************************************************************/

bool DesignatorString::setValue(const QString& value) noexcept
{
    if (checkValidity(value)) {
        mValue = value;
        return true;
    } else {
        // TODO: should we invalidate the object or just keep the old value?
        //mValue = QString();
        return false;
    }
}

/*****************************************************************************************
 *  Operators
 ****************************************************************************************/

DesignatorString& DesignatorString::operator=(const DesignatorString& rhs) noexcept
{
    mValue = rhs.mValue;
    return *this;
}

bool DesignatorString::operator>(const DesignatorString& rhs) const noexcept
{
    if (isValid() && rhs.isValid()) {
        return (compare(rhs) > 0);
    } else {
        return false;
    }
}

bool DesignatorString::operator<(const DesignatorString& rhs) const  noexcept
{
    if (isValid() && rhs.isValid()) {
        return (compare(rhs) < 0);
    } else {
        return false;
    }
}

bool DesignatorString::operator>=(const DesignatorString& rhs) const noexcept
{
    if (isValid() && rhs.isValid()) {
        return (compare(rhs) >= 0);
    } else {
        return false;
    }
}

bool DesignatorString::operator<=(const DesignatorString& rhs) const noexcept
{
    if (isValid() && rhs.isValid()) {
        return (compare(rhs) <= 0);
    } else {
        return false;
    }
}

bool DesignatorString::operator==(const DesignatorString& rhs) const noexcept
{
    if (isValid() && rhs.isValid()) {
        return (compare(rhs) == 0);
    } else {
        return false;
    }
}

bool DesignatorString::operator!=(const DesignatorString& rhs) const noexcept
{
    return !(*this == rhs);
}

/*****************************************************************************************
 *  Private Methods
 ****************************************************************************************/

int DesignatorString::compare(const DesignatorString& other) const noexcept
{
    QString val1 = mValue.toUpper();
    QString val2 = other.mValue.toUpper();
    if (val1.isEmpty() || val2.isEmpty() || (val1 == val2)) {
        return 0;
    } else {
        return val1 < val2 ? -1 : 1;
    }
}

/*****************************************************************************************
 *  Static Methods
 ****************************************************************************************/

bool DesignatorString::checkValidity(const QString& value) noexcept
{
    if (value.length() > )
    QString allowedChars =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "\\/+-_.:";
    //ret.remove(QRegularExpression(QString("[^%1]").arg(validChars)));
    return false;
}

/*****************************************************************************************
 *  End of File
 ****************************************************************************************/

} // namespace librepcb
