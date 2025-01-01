#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <regex>

enum Flag {unknown,unique,count,uniqueAlpha,countAlpha,grep,lineNum,quit};


Flag readFlag(char* argv[]);
void uniqueWords(int argc, char* argv[], std::set<std::string>& uniqueWords);
void countOfUniqueWords(int argc, char* argv[],
                        std::map<std::string, int>& uniqueWords);
void uniqueLetters(int argc, char* argv[], std::set<std::string>& uniqueWords);
void countOfUniqueLetters(int argc, char* argv[],
                          std::map<std::string, int>& uniqueWords);
void storeLineTokens(std::set<std::string>& words, std::string line);
void storeLineTokens(std::map<std::string, int>& words, std::string line);
void storeLineTokensAlpha(std::set<std::string>& words, std::string line);
void storeLineTokensAlpha(std::map<std::string, int>& words, std::string line);
void grepSearch(int argc, char* argv[], std::map<std::string, int>& map,
          std::set<std::string>& set);

struct Options{

};

int main(int argc, char* argv[]) {
  std::cout << argv[0]<<std::endl; 
  Flag flag = readFlag(argv);
  std::set<std::string> uniqueTokens;
  std::map<std::string, int> uniqueTokensCount;
      switch (flag) {
      case unknown:
        break;
      case unique:
        uniqueWords(argc, argv, uniqueTokens);
        break;
      case count:
        countOfUniqueWords(argc, argv, uniqueTokensCount);
        break;
      case uniqueAlpha:
        uniqueLetters(argc, argv, uniqueTokens);
        break;
      case countAlpha:
        countOfUniqueLetters(argc, argv, uniqueTokensCount);
        break;
      case grep:
        grepSearch(argc, argv, uniqueTokensCount, uniqueTokens);

        break;
      case quit:
        break;
      default:
        break;
  }
}

Flag readFlag(char* argv[]) {
  std::string flag(argv[1]);
  if (flag == "-u") {
    std::cout << "in unique\n";
    return unique;
  }
  if (flag == "-c") {
    std::cout << "in count\n";
    return count;
  }
  if (flag == "-ua") {
    std::cout << "in unique\n";
    return uniqueAlpha;
  }
  if (flag == "-ca") {
    std::cout << "in count\n";
    return countAlpha;
  }
  if (flag == "-grep") {
    return grep;
  }
  if (flag == "-quit") {
    return quit;
  }

  return unknown;
}

void uniqueWords(int argc, char* argv[], std::set<std::string>& uniqueWords) { 
  std::cout << "In unique Words\n"; 
  std::vector<std::string> fileNames;

  for (int i = 2; i < argc; i++) {
    std::string fileName(argv[i]);
    std::cout << fileName << std::endl;
    fileNames.push_back(fileName);
  }
  
  for (auto cur : fileNames) {
    std::fstream file(cur);
    std::string line;
    while (getline(file, line)) {

      //Redundant, and less efficient method!
      // 
      // std::cout << line << std::endl;
      /* std::stringstream removeSpaces(line);
      while (getline(removeSpaces, line, ' ')) {
        std::stringstream removeCommas(line);

        while (getline(removeCommas, line, ',')) {
          uniqueWords.insert(line);
        }
      }*/


      storeLineTokens(uniqueWords,line);
    }
    for (const auto& cur : uniqueWords) {
      std::cout << cur << std::endl;
    }
    file.close();
  }
}

void countOfUniqueWords(int argc, char* argv[],
                        std::map<std::string, int>& uniqueWords) { 
  std::cout << "In count of Unique Words\n";
  std::vector<std::string> fileNames;

  for (int i = 2; i < argc; i++) {
    std::string fileName(argv[i]);
    std::cout << fileName << std::endl;
    fileNames.push_back(fileName);
  }
  
  for (auto cur : fileNames) {
    std::fstream file(cur);
    std::string line;
    while (getline(file, line)) {
      storeLineTokens(uniqueWords, line);
    }
    for (const auto& cur : uniqueWords) {
      std::cout << cur.first << " => " << cur.second << std::endl;
    }
    file.close();
  }
  
}

void uniqueLetters(int argc, char* argv[], std::set<std::string>& uniqueLetters) {
  std::cout << "In unique letters\n";
  std::vector<std::string> fileNames;

  for (int i = 2; i < argc; i++) {
    std::string fileName(argv[i]);
    std::cout << fileName << std::endl;
    fileNames.push_back(fileName);
  }
  for (auto cur : fileNames) {
    std::fstream file(cur);
    std::string line;
    while (getline(file, line)) {
            storeLineTokensAlpha(uniqueLetters, line);
    }
    for (const auto& cur : uniqueLetters) {
      std::cout << cur << std::endl;
    }
    file.close();
  }
}

void countOfUniqueLetters(int argc, char* argv[],
                          std::map<std::string, int>& uniqueLetters) {
  std::cout << "In count of Unique letters\n";
  std::vector<std::string> fileNames;

  for (int i = 2; i < argc; i++) {
    std::string fileName(argv[i]);
    std::cout << fileName << std::endl;
    fileNames.push_back(fileName);
  }
  for (auto cur : fileNames) {
    std::fstream file(cur);
    std::string line;
    while (getline(file, line)) {
      storeLineTokensAlpha(uniqueLetters, line);
    }
    for (const auto& cur : uniqueLetters) {
      std::cout << cur.first << " => " << cur.second << std::endl;
    }
    file.close();
  }
}

void storeLineTokens(std::set<std::string>& words, std::string line) {
  // Define a regex pattern to match words (sequences of alphanumeric
  // characters)
  std::regex word_regex(R"(\w+)"); //tested with https://regex101.com

  // Create an iterator to match words using regex
  std::sregex_token_iterator it(line.begin(), line.end(), word_regex);
  std::sregex_token_iterator end;

  // Store the tokens (words) in a vector
  for (; it != end; ++it) {
    words.insert(it->str());
  }
}

void storeLineTokens(std::map<std::string, int>& words, std::string line) {
  // Define a regex pattern to match words (sequences of alphanumeric
  // characters)
  std::regex word_regex(R"(\w+)");  // tested with https://regex101.com

  // Create an iterator to match words using regex
  std::sregex_token_iterator it(line.begin(), line.end(), word_regex);
  std::sregex_token_iterator end;

  // Store the tokens (words) in a vector
  for (; it != end; ++it) {
   
    words[it->str()]++;
  }
}

void storeLineTokensAlpha(std::set<std::string>& letters, std::string line) {
  // Define a regex pattern to match words (sequences of alphanumeric
  // characters)
  std::regex word_regex(R"(\w)");  // tested with https://regex101.com https://www.rexegg.com/regex-quickstart.php

  // Create an iterator to match words using regex
  std::sregex_token_iterator it(line.begin(), line.end(), word_regex);
  std::sregex_token_iterator end;

  // Store the tokens (words) in a vector
  for (; it != end; ++it) {
    letters.insert(it->str());
  }
}

void storeLineTokensAlpha(std::map<std::string, int>& letters, std::string line) {
  // Define a regex pattern to match words (sequences of alphanumeric
  // characters)
  std::regex word_regex(R"(\w)");  // tested with https://regex101.com

  // Create an iterator to match words using regex
  std::sregex_token_iterator it(line.begin(), line.end(), word_regex);
  std::sregex_token_iterator end;

  // Store the tokens (words) in a vector
  for (; it != end; ++it) {
    letters[it->str()]++;
  }
}

void grepSearch(int argc, char* argv[], std::map<std::string, int>& map,
  std::set<std::string>& set) {
  std::string line;
  
  
  std::string lineFlag("-l");
  bool outputLN = false;
  if (lineFlag == argv[2]) {
    outputLN = true;
  }
 

  std::vector<std::string> fileNames;
  int start = 3;
  if (outputLN) {
    start++;
  }
  std::string regSetting = argv[start - 1];
  std::regex regToSearch(regSetting);
  std::cout << std::boolalpha<< outputLN << std::endl;

  for (int i = start; i < argc; i++) {
    std::string fileName(argv[i]);
    std::cout << fileName << std::endl;
    fileNames.push_back(fileName);
  }
  for (auto cur : fileNames) {
    std::cout << "inloop " + cur << std::endl;
    std::fstream file(cur);
    std::string line;
    int lineNumber = 0;
    while (getline(file, line)) {
      //std::cout << line << std::endl;
      std::sregex_token_iterator it(line.begin(), line.end(), regToSearch);
      std::sregex_token_iterator end;
      lineNumber++;
       for (; it != end; ++it) {
        if (outputLN) {
          std::cout << lineNumber << ": " << it->str() << std::endl;
        } else {
          std::cout << it->str() << std::endl;
        }
        break;
        }
    }
    file.close();
  }
  
}