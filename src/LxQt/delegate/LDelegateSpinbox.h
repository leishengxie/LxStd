#ifndef L_DELEGATE_SPINBOX_H
#define L_DELEGATE_SPINBOX_H
#include <QStyledItemDelegate>

class LDelegateSpinbox : public QStyledItemDelegate
{
    Q_OBJECT
public:
    LDelegateSpinbox(QObject *parent = 0);

    // 重写
    //返回一个编辑控件，用来编辑指定项的数据
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;

    //将Model中数据赋值到控件上
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    //设定模型数据，根据指定项中对应编辑控件的数据
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    //更新编辑框几何形状
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
#endif // L_DELEGATE_SPINBOX_H

//测试
/*
//构建一个4行，2列的项模型
    QStandardItemModel model(4, 2);
    //声明一个TableView
    QTableView tableView;
    //绑定模型
    tableView.setModel(&model);
    //声明一个委托
    SpinBoxDelegate delegate;
    //设定视图的委托
    tableView.setItemDelegate(&delegate);
    //ensuring that the view does not waste any of the space assigned to it for its header
    //最后一列全部填充View
    tableView.horizontalHeader()->setStretchLastSection(true);

    //初始化Model
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 2; ++column) {
            QModelIndex index = model.index(row, column, QModelIndex());
            model.setData(index, QVariant((row+1) * (column+1)));
        }

    }
    tableView.show();
    */
