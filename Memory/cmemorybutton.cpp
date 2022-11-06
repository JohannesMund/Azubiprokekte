#include "cmemorybutton.h"

#include <QEvent>

CMemoryButton::CMemoryButton(const int internalValue) : QPushButton(""), _internalValue(internalValue)
{
    setCheckable(true);
    setMinimumSize(QSize(16, 16));
    setMaximumSize(QSize(256, 256));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(this, &QAbstractButton::clicked, this, &CMemoryButton::buttonClicked);

    setIcon(QPixmap(":/cards/img/back.png"));
}

int CMemoryButton::getInternalValue() const
{
    return _internalValue;
}

void CMemoryButton::buttonClicked(const bool checked)
{
    if (checked)
    {
        reveal();
    }
}

void CMemoryButton::unreveal()
{
    setChecked(false);
    setIcon(QPixmap(":/cards/img/back.png"));
    setText("");
    setEnabled(true);
}

void CMemoryButton::resizeEvent(QResizeEvent* e)
{
    if (width() > height())
    {
        setIconSize(QSize(height() - 5, height() - 5));
    }
    else
    {
        setIconSize(QSize(width() - 5, width() - 5));
    }
    QPushButton::resizeEvent(e);
}

void CMemoryButton::reveal()
{
    QString ressourceText = QString(":/cards/img/%1.png").arg(_internalValue);

    QIcon icon;
    setText("");

    icon.addPixmap(QPixmap(ressourceText), QIcon::Active);
    // Wir setzen explizit die gleiche Grafik für Disabled, damit wird die nicht grau.
    icon.addPixmap(QPixmap(ressourceText), QIcon::Disabled);
    setIcon(icon);

    setEnabled(false);

    emit buttonSelected();
}
