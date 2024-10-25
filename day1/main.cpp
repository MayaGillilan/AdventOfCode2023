#include <iostream>
#include <string>
#include <fstream>
#include <map>

/*
  Solves trebuchet problem https://adventofcode.com/2023/day/1 - Given a file with each line containing a jumbled string,
  find the first and last digit of each line and add them together to form a number. Sum the number from each line
  and print the total sum.

  Part 2: Digits can also be spelled out, like 'one' or 'four'. This should also be accepted.

  Note: I opted not to use C++'s native regex here since it doesn't support overlapping matches
  and I wanted to stick to native functionality for the time being.
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
  const std::map<std::string, char> digitWordMap{
      {"one", '1'}, {"two", '2'}, {"three", '3'}, {"four", '4'}, {"five", '5'}, {"six", '6'}, {"seven", '7'}, {"eight", '8'}, {"nine", '9'}};

  while (std::getline(inputFile, currentLine))
  {
    size_t firstDigitPos{currentLine.find_first_of("0123456789")};
    size_t secondDigitPos{currentLine.find_last_of("0123456789")};
    char firstDigit{currentLine[firstDigitPos]};
    char secondDigit{currentLine[secondDigitPos]};

    for (const auto &[key, value] : digitWordMap)
    {
      const int firstMatchPos = currentLine.find(key);
      if (firstMatchPos != -1 && firstMatchPos < firstDigitPos)
      {
        firstDigit = value;
        firstDigitPos = firstMatchPos;
      }
      const int lastMatchPos = currentLine.rfind(key);
      if (lastMatchPos != -1 && lastMatchPos > secondDigitPos)
      {
        secondDigit = value;
        secondDigitPos = lastMatchPos;
      }
    }

    sum += std::stoi(std::string() + firstDigit + secondDigit, nullptr, 10);
  }

  std::cout << "Sum of each line's first and last digit is: " << sum << '\n';
}
