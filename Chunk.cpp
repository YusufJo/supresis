// Copyright (c) Abdulhamid Yusuf. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.

#include "Chunk.h"

void Chunk::setHeader(const string &content) {
    header = content;
}

void Chunk::setSupport(const string &content) {
    support = content;
}

void Chunk::setResistance(const string &content) {
    resistance = content;
}

bool Chunk::isValid() {
    return !header.empty() && !support.empty() && !resistance.empty();
}

void Chunk::reset() {
    header.clear();
    support.clear();
    resistance.clear();
}

const string &Chunk::getHeader() const {
    return header;
}

const string &Chunk::getSupport() const {
    return support;
}

const string &Chunk::getResistance() const {
    return resistance;
}

