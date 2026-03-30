#ifndef ESTATEMANAGER_H
#define ESTATEMANAGER_H

#include <vector>
#include <string>
#
#include "realestate.h" // Используем ваш существующий класс

class EstateManager {
public:
    // Конструктор по умолчанию
    EstateManager();

    // Остальные методы (добавление, удалm_ение, загрузка)
    void addEstate(const RealEstate& re);
    void removeContainsDate(const std::string& target);
    void removeEstate(const int& target);
    const std::vector<RealEstate>& getEstates() const;
    void saveToFile(const std::string& filename) const;

private:
    std::vector<RealEstate> m_realEstates;
};

#endif