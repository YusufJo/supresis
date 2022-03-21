// Copyright (c) Abdulhamid Yusuf. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#ifndef SUBRESIS_ENTRY_H
#define SUBRESIS_ENTRY_H

#include <string>
#include <vector>

using std::string; using std::vector;

class Entry {
    string dateTime;
    string pair;
    string interval;
    vector<float> support;
    vector<float> resistance;

public:
    void setDateTime(const string &dateTime);

    void setPair(const string &pair);

    void setInterval(const string &interval);

    [[nodiscard]] const string &getDateTime() const;

    [[nodiscard]] const string &getPair() const;

    [[nodiscard]] const string &getInterval() const;

    string getSupportStr();

    string getResistanceStr();

    void addSupportLevel(const float &level);

    void reset();

    void addResistanceLevel(const float &d);

    bool isValid();

private:
    static string to_string_with_precision(const float &num, const int &precision);
};


#endif //SUBRESIS_ENTRY_H
