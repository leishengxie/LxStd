#ifndef SEARCH_EDIT_H
#define SEARCH_EDIT_H

#include <QWidget>
#include <QStyleOptionFrame>
#include <QLineEdit>
#include <QLinearGradient>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

///
/// \brief The CLMagnifyingGlass class 自绘放大镜
///
class CLMagnifyingGlass : public QWidget
{
    Q_OBJECT

public:
    explicit CLMagnifyingGlass(QWidget *parent = 0);

public:
    QSize sizeHint() const;

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent* event);

    void mouseReleaseEvent(QMouseEvent *event);
};

class CLSearchEditBase : public QWidget
{
    Q_OBJECT

public:
    CLSearchEditBase(QWidget* parent = 0);

    inline QLineEdit* lineEdit() const
    {
        return m_lineEdit;
    }


    void setShearchWidget(QWidget* widget);
    QWidget* shearchWidget() const;

    QSize sizeHint() const;

    QVariant inputMethodQuery(Qt::InputMethodQuery property) const;
protected:
    void focusInEvent(QFocusEvent* event);
    void focusOutEvent(QFocusEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void paintEvent(QPaintEvent* e);
    void resizeEvent(QResizeEvent* event);
    void inputMethodEvent(QInputMethodEvent* e);
    bool event(QEvent* event);

protected:
    void updateGeometries();
    void initStyleOption(QStyleOptionFrameV2* option) const;

    QWidget* m_wgtShearch;
    QLineEdit* m_lineEdit;
};

class CLSearchEdit : public CLSearchEditBase
{
    Q_OBJECT

signals:
    void search(const QString text);

public:
    CLSearchEdit(QWidget* parent = 0);

protected:
    void paintEvent(QPaintEvent* event);

private slots:
    void onMagnifyingGlassClicked();
    void onTextChanged(QString strText);

private:
    QLinearGradient generateGradient(const QColor & color) const;
    QColor m_defaultBaseColor;
    CLMagnifyingGlass* m_pMagnifyingGlass;
};

#endif // SEARCH_EDIT_H
