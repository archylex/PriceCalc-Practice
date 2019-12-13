#ifndef QDYNAMICCOMBOBOX_H
#define QDYNAMICCOMBOBOX_H

#include <QComboBox>

class QDynamicComboBox : public QComboBox {
    Q_OBJECT
public:
    explicit QDynamicComboBox(QWidget *parent = 0);
    ~QDynamicComboBox();
    static int ResID;
    int getID();


private:
    int buttonID = 0;
};

#endif // QDYNAMICCOMBOBOX_H
