// Copyright (c) Abdulhamid Yusuf. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#ifndef SUBRESIS_CHUNK_H
#define SUBRESIS_CHUNK_H

#include <string>

using std::string;

class Chunk {
    string header;
    string support;
    string resistance;

public:
    void setHeader(const string &content);

    void setSupport(const string &content);

    void setResistance(const string &content);

    [[nodiscard]] const string &getHeader() const;

    [[nodiscard]] const string &getSupport() const;

    [[nodiscard]] const string &getResistance() const;

public:
    bool isValid();

public:
    void reset();
};


#endif //SUBRESIS_CHUNK_H
