#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include "Chunk.h"
#include "Entry.h"

using std::ifstream; using std::ofstream;
using std::cout; using std::vector;
using std::string; using std::istringstream;
using std::endl; using std::regex;
using std::smatch; using std::stof;

const char *RED = "\x1b[31m";
const char *YELLOW = "\x1b[33m";
const char *RESET = "\x1b[39;49m";

void VerifyArgs(const int &argc) {
    bool isInputFilePathProvided{argc >= 2};
    if (!isInputFilePathProvided) {
        cout << RED << "Provide a path to your input text file." << RESET << endl;
        exit(1);
    }
    bool isOutputFilePathProvided{argc >= 3};
    if (!isOutputFilePathProvided) {
        cout << RED << "Provide a path to the output file." << RESET << endl;
        exit(1);
    }
}

ifstream ReadInputFile(const char *filePath) {
    ifstream fileStream{filePath};
    if (!fileStream) {
        cout << RED << "Couldn't read file, make sure that the path is correct." << RESET << endl;
        exit(1);
    }
    return fileStream;
}

void ParseHead(const string &line, Entry &entry) {
    const regex pattern{
            R"~(\*\*.+\*\*(\d{4}-[01]\d-[0-3]\dT[0-2]\d:[0-5]\d:[0-5]\d(?:\.\d+)?Z?\+\d{2}:\d{2})\**(\w+)\s(\w+)\s\w+:\*\*)~"};
    smatch matches;
    if (!std::regex_search(line, matches, pattern)) {
        cout << RED << "FAILED TO PARSE HEAD [" << RESET << line << RED << ']' << RESET << endl;
        return;
    }
    // 1st group is datetime
    entry.setDateTime(matches.str(1));
    // 2ed group is pair
    entry.setPair(matches.str(2));
    // 3rd group is interval
    entry.setInterval(matches.str(3));
}

float ParseStrLevel(const string &level) {
    string strLevel = level;
    if (strLevel.find(',') != -1)
        strLevel.replace(level.find(','), 1, "");
    return stof(strLevel);
}

void ParseSupport(const string &line, Entry &entry) {
    istringstream lineStream{line};
    string token;
    const regex pattern{R"~(\$(\d+\,?\d+\.?\d+)\,?\s?-?\$?(\d+\,?\d+\.?\d+)?\,?)~"};
    smatch matches;
    while (lineStream >> token) {
        if (!std::regex_search(token, matches, pattern)) continue;
        entry.addSupportLevel(ParseStrLevel(matches.str(1)));
        if (!matches.str(2).empty()) entry.addSupportLevel(ParseStrLevel(matches.str(2)));
    }
}

void ParseResistance(const string &line, Entry &entry) {
    istringstream lineStream{line};
    string token;
    const regex pattern{R"~(\$(\d+\,?\d+\.?\d+)\,?\s?-?\$?(\d+\,?\d+\.?\d+)?\,?)~"};
    smatch matches;
    while (lineStream >> token) {
        if (!std::regex_search(token, matches, pattern)) continue;
        entry.addResistanceLevel(ParseStrLevel(matches.str(1)));
        if (!matches.str(2).empty()) entry.addResistanceLevel(ParseStrLevel(matches.str(2)));
    }
}

void WriteEntry(Entry &entry, ofstream &outputFile) {
    outputFile << entry.getPair() << ',' << entry.getInterval() << ','
               << '"' << entry.getSupportStr() << '"' << ','
               << '"' << entry.getResistanceStr() << '"' << ','
               << entry.getDateTime() << endl;
}

void IssueValidationWarning(const string &unparsedLine) {
    cout << YELLOW << "WARNING: [" << RESET << unparsedLine << YELLOW << "] WAS NOT PARSED" << RESET << endl;
}

bool ValidateLine(ifstream &inputFile, string &line, const string &searchToken) {
    getline(inputFile, line);
    if (line.rfind(searchToken) == -1) {
        IssueValidationWarning(line);
        return false;
    }
    return true;
}

bool ValidateChunk(ifstream &inputFile, Chunk &chunk) {
    string line;
    if (!ValidateLine(inputFile, line, "Thumbs up once read**")) return false;
    chunk.setHeader(line);
    if (!ValidateLine(inputFile, line, "Support:**")) return false;
    chunk.setSupport(line);
    if (!ValidateLine(inputFile, line, "Resistance:**")) return false;
    chunk.setResistance(line);
    return true;
}

void WriteCSVHeaders(ofstream &outputFile) {
    outputFile << "pair,interval,support,resistance,datetime" << endl;
}

void ParseInputFile(ifstream &inputFile, const char *outputFilePath) {
    ofstream outputFile;
    string line;
    Chunk chunk{};
    Entry entry{};
    bool isCSVHeaderWritten{};

    while (inputFile.peek() != ifstream::traits_type::eof()) {
        if (!ValidateChunk(inputFile, chunk)) continue;
        // parsing a new Chunk
        ParseHead(chunk.getHeader(), entry);
        ParseSupport(chunk.getSupport(), entry);
        ParseResistance(chunk.getResistance(), entry);
        if (!entry.isValid()) continue;
        if (!isCSVHeaderWritten) {
            outputFile.open(outputFilePath);
            WriteCSVHeaders(outputFile);
            isCSVHeaderWritten = true;
        }
        WriteEntry(entry, outputFile);
        // prepare object for new data
        chunk.reset();
        entry.reset();
    }
    outputFile.close();
}

int main(int argc, char **argv) {
    VerifyArgs(argc);
    ifstream inputFile{ReadInputFile(argv[1])};
    ParseInputFile(inputFile, argv[2]);
    inputFile.close();
    return 0;
}
