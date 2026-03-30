#include <algorithm>
#include "estatemanager.h"
#include <fstream>

EstateManager::EstateManager() {
}

void EstateManager::addEstate(const RealEstate& re) {
    m_realEstates.push_back(re);
}

const std::vector<RealEstate>& EstateManager::getEstates() const {
    return m_realEstates;
}

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

void EstateManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& re : m_realEstates) {
            file << re.owner << "," << re.date << "," << re.colour << "," << re.cost << "\n";
        }
        file.close();
    }
}