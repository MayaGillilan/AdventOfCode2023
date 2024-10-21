#include <iostream>
#include <string>
#include <fstream>

/*
  Solves trebuchet problem https://adventofcode.com/2023/day/1 - Given a file with each line containing a jumbled string,
  find the first and last digit of each line and add them together to form a number. Sum the number from each line
  and print the total sum.
*/

int main()
{
  std::ifstream inputFile("input.txt");

  if (!inputFile)
  {
    std::cerr << "Error: File not found\n";
    return 1;
  }

  if (!inputFile.is_open())
  {
    std::cerr << "Error: Failed to open file\n";
    return 1;
  }

  std::string currentLine{};
  int sum{};

  while (std::getline(inputFile, currentLine))
  {
    size_t firstDigitPos{currentLine.find_first_of("0123456789")};
    size_t secondDigitPos{currentLine.find_last_of("0123456789")};
    sum += std::stoi(std::string() + currentLine[firstDigitPos] + currentLine[secondDigitPos], nullptr, 10);
  }

  std::cout << "Sum of each line's first and last digit is: " << sum << '\n';
}
