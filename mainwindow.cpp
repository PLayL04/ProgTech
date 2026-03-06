#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit> // для текста
#include <QSpinBox> // для чисел
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QToolBar>
#include <QFileDialog>
#include <QFile>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    resize(500, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    toolBar = new QToolBar(this);
    toolBar->addAction("Open File", this, &MainWindow::onFileClicked);
    mainLayout->addWidget(toolBar);

    // Настройка таблицы
    table = new QTableWidget(0, 4, this);
    table->setHorizontalHeaderLabels({"Owner", "Date", "Colour", "Cost"});
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

    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(btnRemove, &QPushButton::clicked, this, &MainWindow::onRemoveClicked);

    QHBoxLayout *removeContainsLayout = new QHBoxLayout();
    QPushButton *btnRemoveContains = new QPushButton("Remove what contains", this);
    containsEdit = new QLineEdit(this);
    removeContainsLayout->addWidget(btnRemoveContains);
    removeContainsLayout->addWidget(containsEdit);
    mainLayout->addLayout(removeContainsLayout);

    connect(btnRemoveContains, &QPushButton::clicked, this, &MainWindow::onRemoveContainsClicked);
}

void MainWindow::onAddClicked()
{
    // Создаем диалоговое окно для ввода данных
    QDialog dialog(this);
    dialog.setWindowTitle("Add estate");
    QFormLayout form(&dialog);

    QLineEdit *ownerEdit = new QLineEdit(&dialog);
    QLineEdit *dateEdit = new QLineEdit(&dialog);
    QLineEdit *colourEdit = new QLineEdit(&dialog);
    QSpinBox *costSpin = new QSpinBox(&dialog);
    costSpin->setMaximum(1000000000);
    costSpin->setMinimum(1);

    form.addRow("Ownner:", ownerEdit);
    form.addRow("Date:", dateEdit);
    form.addRow("Colour", colourEdit);
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
                      colourEdit->text().toStdString(),
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
    table->setRowCount(0);

    for (const auto& re : m_realEstates) {
        int row = table->rowCount();
        table->insertRow(row);

        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(re.owner)));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(re.date)));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(re.colour)));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(re.cost)));
    }
}

void MainWindow::onFileClicked() {
    // 1. Получаем путь к файлу
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", "", "Text Files (*.txt)");

    // Проверка: если пользователь закрыл окно выбора, ничего не делаем
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not open file");
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();

        QStringList fields = line.split(",", Qt::SkipEmptyParts);

        if (fields.size() >= 3) {
            QString in_owner = fields[0].trimmed();
            QString in_date  = fields[1].trimmed();
            QString in_cost  = fields[2].trimmed();

            RealEstate re(in_owner.toStdString(),
                          in_date.toStdString(),
                          in_cost.toInt());
            m_realEstates.push_back(re);
        }
    }

    file.close();
    updateTable();
}

void MainWindow::onRemoveContainsClicked()
{
    QString filterText = containsEdit->text();

    if (filterText.isEmpty()) {
        QMessageBox::information(this, "Info", "Enter a date substring to remove");
        return;
    }

    std::string target = filterText.toStdString();

    // Используем идиому erase-remove для удаления элементов из вектора m_realEstates
    m_realEstates.erase(
        std::remove_if(m_realEstates.begin(), m_realEstates.end(),
                       [&target](const RealEstate& re) {
                           // Условие: если в строке date содержится искомая подстрока
                           return re.date.find(target) != std::string::npos;
                       }),
        m_realEstates.end()
        );

    updateTable();

    containsEdit->clear();
}
