#include "Bureaucrat.hpp"

int main(void)
{
    Bureaucrat man = Bureaucrat("man", 300);
    Bureaucrat man2 = Bureaucrat("man2", 140);
    Bureaucrat man4 = Bureaucrat("man4", 1);
    Bureaucrat man6 = Bureaucrat("man6", 20);
    Bureaucrat man5 = Bureaucrat("man5", 2);
    Bureaucrat man3 = Bureaucrat("man3", 150);
    std::cout << man;
    return 0;
}