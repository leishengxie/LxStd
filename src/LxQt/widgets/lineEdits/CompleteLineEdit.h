#ifndef COMPLETELINEEDIT_H
#define COMPLETELINEEDIT_H


#include <QLineEdit>
#include <QStringList>

class QListView;
class QStringListModel;
class QModelIndex;

///
/// \brief The CCompleteLineEdit class 完成列表输入控件
/// 把用户可能经常输入的词汇加入到完成列表当中，为方便输入时直接选择
///
class CCompleteLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    // explicit声明为显式调用
    // 为了使控件能够在ui文件中提升，必须实现参数为QWidget *parent = Q_NULLPTR的构造函数
    explicit CCompleteLineEdit(QWidget *parent = Q_NULLPTR);
    explicit CCompleteLineEdit(QStringList m_strlstWords, QWidget *parent = 0);
    void setListWords(QStringList strlstWords)
    {
        m_strlstWords = strlstWords;
    }

public slots:
    void setCompleter(const QString &text); // 动态的显示完成列表
    void completeText(const QModelIndex &index); // 点击完成列表中的项，使用此项自动完成输入的单词

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void focusOutEvent(QFocusEvent *e);

private:
    void init();

private:
    QStringList m_strlstWords; // 整个完成列表的单词
    QListView *listView; // 完成列表
    QStringListModel *model; // 完成列表的model
};

#endif // COMPLETELINEEDIT_H
