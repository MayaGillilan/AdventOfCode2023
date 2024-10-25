#include <iostream>
#include <string>
#include <fstream>
#include <regex>

#define RED_MAX 12
#define GREEN_MAX 13
#define BLUE_MAX 14

/*
  Day 2: https://adventofcode.com/2023/day/2
  Determines which games are valid based on the highest values of red, green, and blue cubes drawn
  from each game. In each game, a number of random cubes are drawn multiple times then put back.

  Part 2 TBD
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
  const std::regex redMatcher{"([0-9]+)\\sred"};
  const std::regex greenMatcher{"([0-9]+)\\sgreen"};
  const std::regex blueMatcher{"([0-9]+)\\sblue"};
  std::string_view gameText{"Game "};

  while (std::getline(inputFile, currentLine))
  {
    // Each line is always preceded by the game number as "Game N:"
    const int gameNumber{std::stoi(currentLine.substr(gameText.length(), currentLine.find(':')))};
    int highestRed{0};
    int highestGreen{0};
    int highestBlue{0};
    int currentLinePos{0};

    while (currentLinePos < currentLine.length())
    {
      const std::string currentSubstr = currentLine.substr(
          currentLinePos,
          currentLine.find(';', currentLinePos) - currentLinePos);
      std::smatch redMatch;
      std::smatch greenMatch;
      std::smatch blueMatch;

      std::regex_search(currentSubstr, redMatch, redMatcher);
      std::regex_search(currentSubstr, greenMatch, greenMatcher);
      std::regex_search(currentSubstr, blueMatch, blueMatcher);

      if (!redMatch.empty())
      {
        const int redValue{std::stoi(redMatch.str(1))};
        if (redValue > highestRed)
        {
          highestRed = redValue;
        }
      }
      if (!greenMatch.empty())
      {
        const int greenValue{std::stoi(greenMatch.str(1))};
        if (greenValue > highestGreen)
        {
          highestGreen = greenValue;
        }
      }
      if (!blueMatch.empty())
      {
        const int blueValue{std::stoi(blueMatch.str(1))};
        if (blueValue > highestBlue)
        {
          highestBlue = blueValue;
        }
      }
      currentLinePos += currentSubstr.length() + 1;
    }
    // sum if game is valid (all highest values are less than maxValues)
    if (highestRed <= RED_MAX && highestGreen <= GREEN_MAX && highestBlue <= BLUE_MAX)
    {
      sum += gameNumber;
    }
  }

  std::cout << "Sum of valid games: " << sum << '\n';
}