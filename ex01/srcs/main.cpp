#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
    std::cout << "=== Test 1: Creating forms with valid grades ===" << std::endl;
    try
    {
        Form form1("Tax Form", 50, 25);
        std::cout << form1 << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 2: Creating forms with invalid grades ===" << std::endl;
    try
    {
        Form form2("Invalid Form", 0, 25);
        std::cout << form2 << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try
    {
        Form form3("Invalid Form 2", 50, 151);
        std::cout << form3 << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 3: Bureaucrat signing forms ===" << std::endl;
    try
    {
        Bureaucrat john("John", 30);
        Form permit("Building Permit", 50, 25);
        
        std::cout << john;
        std::cout << permit << std::endl;
        
        john.signForm(permit);
        std::cout << permit << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 4: Bureaucrat with insufficient grade ===" << std::endl;
    try
    {
        Bureaucrat lowRank("Bob", 100);
        Form topSecret("Top Secret", 20, 10);
        
        std::cout << lowRank;
        std::cout << topSecret << std::endl;
        
        lowRank.signForm(topSecret);
        std::cout << topSecret << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 5: Multiple signatures ===" << std::endl;
    try
    {
        Bureaucrat alice("Alice", 1);
        Form visa("Visa Application", 10, 5);
        
        std::cout << alice;
        std::cout << visa << std::endl;
        
        alice.signForm(visa);
        std::cout << visa << std::endl;
        
        // Try signing again
        alice.signForm(visa);
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}