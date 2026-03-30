#include "parser.h"

Parser::Parser(EstateManager* manager) : m_manager(manager) {}

void Parser::processFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        if (line.startsWith("ADD ")) {
            handleAdd(line.mid(4).trimmed());
        } else if (line.startsWith("REM ")) {
            handleRem(line.mid(4).trimmed());
        } else if (line.startsWith("SAVE ")) {
            handleSave(line.mid(5).trimmed());
        }
    }
    file.close();
}

void Parser::handleAdd(const QString& data) {
    QStringList parts = data.split(";", Qt::SkipEmptyParts);
    if (parts.size() >= 4) {
        // owner, date, colour, cost
        RealEstate re(parts[0].trimmed().toStdString(),
                      parts[1].trimmed().toStdString(),
                      parts[2].trimmed().toStdString(),
                      parts[3].trimmed().toInt()
                      );
        m_manager->addEstate(re);
    }
}

void Parser::handleRem(const QString& data) {
    QStringList parts = data.split(" ", Qt::SkipEmptyParts);
    if (parts.size() >= 3) {
        QString field = parts[0].toLower();
        QString op = parts[1];
        int value = parts[2].toInt();

        if (field == "cost" || field == "sum") {
            auto& estates = const_cast<std::vector<RealEstate>&>(m_manager->getEstates());
            estates.erase(
                std::remove_if(estates.begin(), estates.end(), [&](const RealEstate& re) {
                    if (op == "<") return re.cost < value;
                    if (op == ">") return re.cost > value;
                    if (op == "==") return re.cost == value;
                    return false;
                }),
                estates.end()
                );
        }
    }
}

void Parser::handleSave(const QString& data) {
    m_manager->saveToFile(data.toStdString());
}