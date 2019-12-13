#ifndef ADDTOPRICEDIALOG_H
#define ADDTOPRICEDIALOG_H

#include <QDialog>

namespace Ui {
class addToPriceDialog;
}

class addToPriceDialog : public QDialog {
    Q_OBJECT

public:
    explicit addToPriceDialog(QWidget *parent = 0);
    ~addToPriceDialog();
    QString getCollection() const;
    QString getModel() const;
    QString getType() const;
    QString getPattern() const;
    int getPrice() const;
    void setFieldTitleD(QString text);
    void setFieldTitleA(QString text);
    void hideFieldB();
    void showFieldB();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::addToPriceDialog *ui;
};

#endif // ADDTOPRICEDIALOG_H
