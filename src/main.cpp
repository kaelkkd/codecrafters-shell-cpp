#include <iostream>
#include "shell.h"

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
      case type: 
        verifyType(input);
        break;
      case invalid:
        validate(input);
        break;    
      case pwd:
        getWorkingDirectory();
        break;
      case cd:
        changeWorkingDirectory(input);
        break;
    }
  } 
}
