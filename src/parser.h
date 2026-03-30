#ifndef H_PARSER
#define H_PARSER

#include <QString>
#include <QFile>
#include <QTextStream>
#include "estatemanager.h"

class Parser {
public:
    Parser(EstateManager* manager);
    void processFile(const QString& filePath);

private:
    EstateManager* m_manager;
    void handleAdd(const QString& data);
    void handleRem(const QString& condition);
    void handleSave(const QString& filename);
};

#endif