#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <fstream>

enum commands {
  quit,
  echo,
  invalid,
  type,
  pwd
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

void getWorkingDirectory() {
  std::filesystem::path cwd = std::filesystem::current_path();
  std::string cwdString = cwd.generic_string();
  std::cout << cwdString << std::endl;
}

commands checkCommand(std::string command) {
  if (command == "exit" || command == "exit 0") return quit;
  else if (command.substr(0, 4) == "echo") return echo;
  else if (command.substr(0, 4) == "type") return type;
  else if (command.substr(0, 3) == "pwd") return pwd;

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
      case invalid: {
        std::string command = input.substr(0, input.find(' '));
        std::string commandPath = getPath(command);

        if (commandPath.empty()) {
          std::cout << input << ": command not found" << std::endl;
        } 
        else {
          int result = std::system(input.c_str());
          if (result != 0) {
            std::cout << input << ": command failed" << std::endl;
          }
        }
        break;
      }
      case pwd:
        getWorkingDirectory();
        break;
    }
  } 
}
