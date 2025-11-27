// ===========================================================================
// ListView.h
// ===========================================================================

#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>

#include "ListView.h"

ListView::ListView() : m_cols{ 0 } {}

void ListView::setColumns(int cols) {
    m_cols = cols;
}

void ListView::setColumnHeader(std::initializer_list<std::string> titles) {

    if (titles.size() != m_cols) {
        std::ostringstream oss;
        oss << "Invalid size of data row: " << titles.size() << "!";
        throw std::out_of_range(oss.str());
    }

    m_titles.resize(0);

    std::for_each(
        std::begin(titles),
        std::end(titles),
        [this](const std::string& elem) {
            m_titles.push_back(elem);
        }
    );
}

void ListView::addData(std::vector<std::string> data) {
    if (data.size() != m_cols) {
        std::ostringstream oss;
        oss << "Invalid size of data row: " << data.size() << "!";
        throw std::out_of_range(oss.str());
    }

    m_data.push_back(data);
}

void ListView::show() {
    std::ostringstream oss;
    for (size_t i = 0; i < m_cols; ++i) {
        if (i == 0)
            oss << "| ";
        oss << m_titles[i] << " | ";
    }
    std::cout << oss.str() << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    for (size_t i = 0; i < m_data.size(); ++i) {
        std::vector<std::string> data = m_data[i];
        for (size_t k = 0; k < m_cols; ++k) {
            if (i == 0)
                oss << "| ";
            oss << data[i] << " | ";
        }
        std::cout << oss.str() << std::endl;
    }
    std::cout << "-----------------------------------" << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
