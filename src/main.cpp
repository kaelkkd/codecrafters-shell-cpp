#include <iostream>

enum commands {
  quit,
  echo,
  invalid,
  type
};

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
        std::cout << input.substr(5, input.length()) << std::endl;
        break;
      case type:
        std::string verType = input.substr(5, input.length());
        if (checkCommand(verType) != invalid) {
          std::cout << verType << " is a shell builtin" << std::endl;
        }
        else {
          std::cout << verType << ": not found" << std::endl;
        }
    }
  } 
}
