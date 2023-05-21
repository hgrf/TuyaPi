#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class IconButton : public QPushButton
{
    Q_OBJECT
public:
    explicit IconButton(QWidget *parent = nullptr);
    void setIcon(int charCode);
    void setIcon(const QString& iconString);
    void setText(const QString& text);

private:
    QLabel mLabel;

signals:

};

#endif // ICONBUTTON_H
