#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <sstream>

enum commands {
  quit,
  echo,
  invalid,
  type
};

std::string getPath(std::string commandPath) {
  std::string directory = std::getenv("PATH");
  std::stringstream ss(directory);
  std::string path;

  while(!ss.eof()) {
    std::getline(ss, path, ':');
    std::string absPath = path + '/' + commandPath;
    
    if (std::filesystem::exists(absPath)) {
      return absPath;
    }
  }

  return "";
}

commands checkCommand(std::string command) {
  if (command == "exit" || command == "exit 0") return quit;
  else if (command.substr(0, 4) == "echo") return echo;
  else if (command.substr(0, 4) == "type") return type;

  else return invalid;
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
   
  // Uncomment this block to pass the first stage
  while (true) {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);
    
    switch (checkCommand(input)) {
      case invalid:
        std::cout << input << ": command not found" << std::endl;
        break;
      case quit:
        return 0;
      case echo:
        std::cout << input.substr(5, input.length() - 5) << std::endl;
        break;
      case type: { 
        std::string inputType = input.substr(5);
        if (checkCommand(inputType) != invalid) {
          std::cout << inputType << " is a shell builtin" << std::endl;
        }
        else {
          std::string envPath = getPath(inputType);

          if (envPath.empty()) {
            std::cout << inputType << ": not found" << std::endl;
          }
          else {
            std::cout << inputType<< " is " << envPath << std::endl;
          }
        }
        break;
      }
    }
  } 
}
