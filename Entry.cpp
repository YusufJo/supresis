// Copyright (c) Abdulhamid Yusuf. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#include <sstream>
#include "Entry.h"

void Entry::setDateTime(const string &dt) {
    Entry::dateTime = dt;
}

void Entry::setPair(const string &p) {
    Entry::pair = p;
}

void Entry::setInterval(const string &i) {
    Entry::interval = i;
}

void Entry::reset() {
    dateTime.clear();
    pair.clear();
    interval.clear();
    support.clear();
    resistance.clear();
}

void Entry::addSupportLevel(const float &level) {
    support.push_back(level);
}

void Entry::addResistanceLevel(const float &level) {
    resistance.push_back(level);
}

bool Entry::isValid() {
    return !dateTime.empty() && !pair.empty() && !interval.empty() && !support.empty() && !resistance.empty();
}

const string &Entry::getDateTime() const {
    return dateTime;
}

const string &Entry::getPair() const {
    return pair;
}

const string &Entry::getInterval() const {
    return interval;
}

string Entry::getSupportStr() {
    string result{};
    for (int i = 0; i < support.size(); i++) {
        result += to_string_with_precision(support[i], 3);
        if (i != support.size() - 1) result += ", ";
    }
    return result;
}

string Entry::getResistanceStr() {
    string result{};
    for (int i = 0; i < resistance.size(); i++) {
        result += to_string_with_precision(resistance[i], 3);
        if (i != resistance.size() - 1) result += ", ";
    }
    return result;
}

string Entry::to_string_with_precision(const float &num, const int &precision) {
    std::ostringstream out;
    out.precision(precision);
    out << std::fixed << num;
    return out.str();
}