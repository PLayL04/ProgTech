#include <algorithm>
#include "estatemanager.h"

// Конструктор
EstateManager::EstateManager() {
    // В большинстве случаев здесь ничего не нужно делать,
    // так как m_realEstates (std::vector) инициализируется сам.

    // Но если вы хотите, чтобы при старте программы всегда были
    // какие-то тестовые данные, их можно добавить здесь:
    // m_realEstates.push_back(RealEstate("Test Owner", "2026.01.01", "Red", 5000));
}

void EstateManager::addEstate(const RealEstate& re) {
    m_realEstates.push_back(re);
}

const std::vector<RealEstate>& EstateManager::getEstates() const {
    return m_realEstates;
}

// Сюда же переезжает логика фильтрации из вашего MainWindow::onRemoveContainsClicked
void EstateManager::removeContainsDate(const std::string& target) {
    m_realEstates.erase(
        std::remove_if(m_realEstates.begin(), m_realEstates.end(),
                       [&target](const RealEstate& re) {
                           return re.date.find(target) != std::string::npos;
                       }),
        m_realEstates.end()
        );
}

void EstateManager::removeEstate(const int& target) {
    m_realEstates.erase(m_realEstates.begin() + target);
}