/* MIT License

Copyright (C) 2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Wishes.h"
#include <QCheckBox>
#include <QRadioButton>
#include <QShowEvent>
#include <QTimer>
#include <QVBoxLayout>

Wishes::Wishes(QWidget *parent)
    : QWidget(parent)
{
}

QStringList Wishes::names() const
{
    ensureInitialized();
    QStringList result;
    for (auto *button : m_buttons)
        result.append(button->text());
    return result;
}

void Wishes::setExclusive(bool b)
{
    m_exclusive = b;
    setDirty();
}

void Wishes::setColor(const QColor &color)
{
    m_color = color;
    setDirty();
}

void Wishes::setDirty()
{
    m_dirty = true;
    if (isVisible())
        ensureInitialized();
}

void Wishes::ensureInitialized() const
{
    if (m_dirty) {
        const_cast<Wishes *>(this)->initialize();
        m_dirty = false;
    }
}

void Wishes::initialize()
{
    delete this->layout();
    qDeleteAll(m_buttons);
    m_buttons.clear();

    auto *layout = new QVBoxLayout(this);
    for (const QString &option : {"Candy", "Depeche Mode", "Eternal Life"}) {
        QAbstractButton *button;
        if (m_exclusive)
            button = new QRadioButton(option);
        else
            button = new QCheckBox(option);

        button->setAutoFillBackground(true);
        QPalette pal = button->palette();
        pal.setBrush(QPalette::Button, m_color);
        button->setPalette(pal);
        layout->addWidget(button);
        m_buttons.append(button);
    }
}

void Wishes::showEvent(QShowEvent *event)
{
    if (!event->spontaneous())
        ensureInitialized();
}
