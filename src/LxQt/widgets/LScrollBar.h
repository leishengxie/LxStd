/*************************************************************************
 *
 * 无限加载与瀑布流的结合在Web前端开发中的效果非常新颖，对于网页内容具备较好的表现形式。
 * 无限加载并没有一次性将内容全部加载进来，而是通过监听滚动条事件来刷新内容的。
 * 当用户往下拖动滚动条或使用鼠标滚轮的时候，页面会自动加载剩余的内容
 *
 */
#ifndef CLSCROLLBAR_H
#define CLSCROLLBAR_H
#include <QScrollBar>

///
/// \brief The CLScrollBar class 用于滚动分页器的滚动条定制
/// --滚动条滚动到底部是触发信号
///
class CLScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit CLScrollBar(QWidget *parent = Q_NULLPTR);
    explicit CLScrollBar(Qt::Orientation ori, QWidget *parent = Q_NULLPTR);

signals:
    void reachedBottom();


private slots:
    void onValueChanged(int nValue);

private:
    void init();

};

#endif // CLSCROLLBAR_H
