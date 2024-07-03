#ifndef SHELL_H
#define SHELL_H

#include <string>

enum commands {
  quit,
  echo,
  invalid,
  type,
  pwd,
  cd
};

commands checkCommand(std::string command);
std::string getPath(std::string commandPath);
void getWorkingDirectory();
void changeWorkingDirectory(std::string input);
void verifyType(std::string input);
void validate(std::string input);


#endif // SHELL_H
