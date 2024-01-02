#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_Clear_clicked();

    void on_comboBox_Table_activated(const QString &arg1);

    void updateTableAndCombobox();

    void writeLogFile();

    void showInformation();

    void restartTimer(int interval, const char *slotFunction);

    void on_pushButton_Search_clicked();

    void slot_table_clicked(int column);

    void setColumnsWidth();

private:
    Ui::MainWindow *ui;
    QSqlDatabase DB_Connection;
    QTimer *m_Timer;
    QString tableName;
    QStringList ColumnHeader;
};
#endif // MAINWINDOW_H
