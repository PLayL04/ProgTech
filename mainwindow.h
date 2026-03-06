#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QToolBar>
#include <vector>
#include "realestate.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default; // деструктор выполняется при уничтожении объекта

private slots:
    void onAddClicked();
    void onRemoveClicked();
    void onFileClicked();
    void onRemoveContainsClicked();

private:
    QToolBar *toolBar;
    QTableWidget *table;
    QPushButton *btnAdd;
    QPushButton *btnRemove;
    QLineEdit *containsEdit;

    // Вектор для хранения всех добавленных экземпляров
    std::vector<RealEstate> m_realEstates;

    // Вспомогательный метод для обновления интерфейса
    void updateTable();
};

#endif // MAINWINDOW_H
