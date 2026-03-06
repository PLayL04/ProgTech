#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    resize(500, 300);

    // Основной слой (вертикальный)
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Настройка таблицы
    table = new QTableWidget(0, 3, this);
    table->setHorizontalHeaderLabels({"Owner", "Date", "Cost"});
    // Растягиваем столбцы на всю ширину
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Выделение только целыми строками (не отдельными ячейками)
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers); // Запрет на редактирование прямо в ячейках
    mainLayout->addWidget(table);

    // Настройка кнопок
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnAdd = new QPushButton("Add", this);
    btnRemove = new QPushButton("Remove", this);

    btnLayout->addWidget(btnAdd);
    btnLayout->addWidget(btnRemove);
    mainLayout->addLayout(btnLayout);

    // Подключение сигналов к слотам
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(btnRemove, &QPushButton::clicked, this, &MainWindow::onRemoveClicked);
}

void MainWindow::onAddClicked()
{
    // Создаем диалоговое окно для ввода данных
    QDialog dialog(this);
    dialog.setWindowTitle("Add estate");
    QFormLayout form(&dialog);

    QLineEdit *ownerEdit = new QLineEdit(&dialog);
    QLineEdit *dateEdit = new QLineEdit(&dialog);
    QSpinBox *costSpin = new QSpinBox(&dialog);
    costSpin->setMaximum(1000000000); // Увеличиваем лимит стоимости

    form.addRow("Ownner:", ownerEdit);
    form.addRow("Date:", dateEdit);
    form.addRow("Cost:", costSpin);

    // Кнопки Ок/Отмена
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // Если пользователь нажал "Ок", создаем экземпляр и добавляем в вектор
    if (dialog.exec() == QDialog::Accepted) {
        RealEstate re(ownerEdit->text().toStdString(),
                      dateEdit->text().toStdString(),
                      costSpin->value());
        m_realEstates.push_back(re);
        updateTable();
    }
}

void MainWindow::onRemoveClicked()
{
    int currentRow = table->currentRow();
    if (currentRow >= 0) {
        // Удаляем из вектора и обновляем таблицу
        m_realEstates.erase(m_realEstates.begin() + currentRow);
        updateTable();
    } else {
        QMessageBox::warning(this, "Err", "Row not selected");
    }
}

void MainWindow::updateTable()
{
    // Очищаем таблицу перед полным обновлением
    table->setRowCount(0);

    // Перебираем вектор и заполняем таблицу
    for (const auto& re : m_realEstates) {
        int row = table->rowCount();
        table->insertRow(row);

        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(re.owner)));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(re.date)));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(re.cost)));
    }
}
