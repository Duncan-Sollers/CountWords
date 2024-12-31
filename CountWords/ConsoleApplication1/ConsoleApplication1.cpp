#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <regex>

enum Flag {unknown,unique,count};
Flag readFlag(char* argv[]);
void uniqueWords(int argc, char* argv[]);
void countOfUniqueWords(int argc, char* argv[]);
void storeLineTokens(std::set<std::string>& words, std::string line);
void storeLineTokens(std::map<std::string, int>& words, std::string line);

int main(int argc, char* argv[]) {
  std::cout << argv[0]<<std::endl; 
  Flag flag = readFlag(argv);
  switch (flag) {
    case unknown:
      break;
    case unique:
      uniqueWords(argc,argv);
      break;
    case count:
      countOfUniqueWords(argc,argv);
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
  return unknown;
}

void uniqueWords(int argc,char* argv[]) { 
  std::cout << "In unique Words\n"; 
  std::vector<std::string> fileNames;

  for (int i = 2; i < argc; i++) {
    std::string fileName(argv[i]);
    std::cout << fileName << std::endl;
    fileNames.push_back(fileName);
  }
  std::set<std::string> uniqueWords;
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

void countOfUniqueWords(int argc, char* argv[]){ 
  std::cout << "In count of Unique Words\n";
  std::vector<std::string> fileNames;

  for (int i = 2; i < argc; i++) {
    std::string fileName(argv[i]);
    std::cout << fileName << std::endl;
    fileNames.push_back(fileName);
  }
  std::map<std::string,int> uniqueWords;
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