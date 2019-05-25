/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * https://librepcb.org/
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

/*******************************************************************************
 *  Includes
 ******************************************************************************/
#include "comboboxdelegate.h"

#include <QtCore>

/*******************************************************************************
 *  Namespace
 ******************************************************************************/
namespace librepcb {

/*******************************************************************************
 *  Constructors / Destructor
 ******************************************************************************/

ComboBoxDelegate::ComboBoxDelegate(QObject* parent) noexcept
  : QStyledItemDelegate(parent) {
}

ComboBoxDelegate::~ComboBoxDelegate() noexcept {
}

/*******************************************************************************
 *  Inherited from QStyledItemDelegate
 ******************************************************************************/

QWidget* ComboBoxDelegate::createEditor(QWidget*                    parent,
                                        const QStyleOptionViewItem& option,
                                        const QModelIndex& index) const {
  Q_UNUSED(option);
  Q_UNUSED(index);
  QComboBox* cbx = new QComboBox(parent);
  cbx->setFrame(false);
  cbx->setSizePolicy(QSizePolicy::Ignored, cbx->sizePolicy().verticalPolicy());
  QVector<QPair<QString, QVariant>> items =
      index.data(Qt::UserRole).value<QVector<QPair<QString, QVariant>>>();
  foreach (const auto& item, items) { cbx->addItem(item.first, item.second); }
  return cbx;
}

void ComboBoxDelegate::setEditorData(QWidget*           editor,
                                     const QModelIndex& index) const {
  QComboBox* cbx = static_cast<QComboBox*>(editor);
  cbx->setCurrentIndex(cbx->findData(index.data(Qt::EditRole), Qt::UserRole));
}

void ComboBoxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                    const QModelIndex& index) const {
  QComboBox* cbx = static_cast<QComboBox*>(editor);
  model->setData(index, cbx->currentData(Qt::UserRole), Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget*                    editor,
                                            const QStyleOptionViewItem& option,
                                            const QModelIndex& index) const {
  Q_UNUSED(index);
  editor->setGeometry(option.rect);
}

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace librepcb
