#ifndef ESTATEMANAGER_H
#define ESTATEMANAGER_H

#include <vector>
#include <string>
#include "realestate.h" // Используем ваш существующий класс

class EstateManager {
public:
    // Конструктор по умолчанию
    EstateManager();

    // Остальные методы (добавление, удаление, загрузка)
    void addEstate(const RealEstate& re);
    void removeContainsDate(const std::string& target);
    const std::vector<RealEstate>& getEstates() const;

private:
    std::vector<RealEstate> m_realEstates;
};

#endif