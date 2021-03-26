#ifndef CMYMENU_H
#define CMYMENU_H

#include <QWidget>
#include <QHBoxLayout>
#include <QMenu>

#include "buttons/LsxRadioButton.h"


class CLsxTabMenu: public QWidget
{
    Q_OBJECT
public:
    CLsxTabMenu(QWidget *parent = 0);
    CLsxTabMenu(CLsxRadioButton *btn, ...);
    CLsxTabMenu(const char *pText, ...);
    ~CLsxTabMenu();

signals:
    void itemClick(int nIndex);
    void itemClick(QString text);

private slots:
    void btnClick(CLsxRadioButton* lsxRadioButton);

private:
    void init();

private:
    QHBoxLayout* m_hLay;
    QVector<CLsxRadioButton*> m_vecBtn;
    int m_nLastSelectedIndex; //last select
    int m_nIndex; //current select
};



#endif // CMYMENU_H
