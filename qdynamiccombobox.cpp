#include "qdynamiccombobox.h"

QDynamicComboBox::QDynamicComboBox(QWidget *parent) :
    QComboBox(parent) {
    ResID++;
    buttonID = ResID;
}

QDynamicComboBox::~QDynamicComboBox() {
}

int QDynamicComboBox::getID() {
    return buttonID;
}

int QDynamicComboBox::ResID = 0;
