#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

void testShrubberyCreation() {
    std::cout << "\n========== SHRUBBERY CREATION FORM TESTS ==========" << std::endl;
    
    try {
        std::cout << "\n--- Test 1: Valid execution ---" << std::endl;
        Bureaucrat alice("Alice", 100);
        ShrubberyCreationForm shrub("home");
        
        std::cout << alice << std::endl;
        std::cout << shrub << std::endl;
        
        alice.signForm(shrub);
        alice.executeForm(shrub);
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 2: Execution without signing ---" << std::endl;
        Bureaucrat bob("Bob", 100);
        ShrubberyCreationForm shrub("garden");
        
        std::cout << bob << std::endl;
        std::cout << shrub << std::endl;
        
        bob.executeForm(shrub);  // Should fail - not signed
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 3: Insufficient grade to execute ---" << std::endl;
        Bureaucrat charlie("Charlie", 140);
        ShrubberyCreationForm shrub("park");
        
        std::cout << charlie << std::endl;
        std::cout << shrub << std::endl;
        
        charlie.signForm(shrub);
        charlie.executeForm(shrub);  // Should fail - grade 140 > 137
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void testRobotomyRequest() {
    std::cout << "\n========== ROBOTOMY REQUEST FORM TESTS ==========" << std::endl;
    
    try {
        std::cout << "\n--- Test 1: Valid execution ---" << std::endl;
        Bureaucrat dave("Dave", 40);
        RobotomyRequestForm robot("Bender");
        
        std::cout << dave << std::endl;
        std::cout << robot << std::endl;
        
        dave.signForm(robot);
        dave.executeForm(robot);
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 2: Multiple execution attempts ---" << std::endl;
        Bureaucrat eve("Eve", 30);
        RobotomyRequestForm robot("Target");
        
        eve.signForm(robot);
        std::cout << "Attempt 1:" << std::endl;
        eve.executeForm(robot);
        std::cout << "Attempt 2:" << std::endl;
        eve.executeForm(robot);
        std::cout << "Attempt 3:" << std::endl;
        eve.executeForm(robot);
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 3: Insufficient grade to sign ---" << std::endl;
        Bureaucrat frank("Frank", 100);
        RobotomyRequestForm robot("Victim");
        
        std::cout << frank << std::endl;
        std::cout << robot << std::endl;
        
        frank.signForm(robot);  // Should fail - grade 100 > 72
        frank.executeForm(robot);
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void testPresidentialPardon() {
    std::cout << "\n========== PRESIDENTIAL PARDON FORM TESTS ==========" << std::endl;
    
    try {
        std::cout << "\n--- Test 1: Valid execution ---" << std::endl;
        Bureaucrat president("President", 1);
        PresidentialPardonForm pardon("Arthur Dent");
        
        std::cout << president << std::endl;
        std::cout << pardon << std::endl;
        
        president.signForm(pardon);
        president.executeForm(pardon);
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 2: Insufficient grade to execute ---" << std::endl;
        Bureaucrat manager("Manager", 20);
        PresidentialPardonForm pardon("Ford Prefect");
        
        std::cout << manager << std::endl;
        std::cout << pardon << std::endl;
        
        manager.signForm(pardon);    // Can sign (grade 20 <= 25)
        manager.executeForm(pardon);  // Can't execute (grade 20 > 5)
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 3: Insufficient grade to sign ---" << std::endl;
        Bureaucrat intern("Intern", 50);
        PresidentialPardonForm pardon("Trillian");
        
        std::cout << intern << std::endl;
        std::cout << pardon << std::endl;
        
        intern.signForm(pardon);     // Should fail - grade 50 > 25
        intern.executeForm(pardon);
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void testPolymorphism() {
    std::cout << "\n========== POLYMORPHISM TEST ==========" << std::endl;
    
    try {
        std::cout << "\n--- Using base class pointers ---" << std::endl;
        Bureaucrat boss("Boss", 1);
        
        AForm *forms[3];
        forms[0] = new ShrubberyCreationForm("office");
        forms[1] = new RobotomyRequestForm("Employee");
        forms[2] = new PresidentialPardonForm("Criminal");
        
        for (int i = 0; i < 3; i++) {
            std::cout << "\n--- Processing form " << i + 1 << " ---" << std::endl;
            std::cout << *forms[i] << std::endl;
            boss.signForm(*forms[i]);
            boss.executeForm(*forms[i]);
        }
        
        // Clean up
        for (int i = 0; i < 3; i++) {
            delete forms[i];
        }
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void testEdgeCases() {
    std::cout << "\n========== EDGE CASES ==========" << std::endl;
    
    try {
        std::cout << "\n--- Test 1: Exact grade requirements ---" << std::endl;
        Bureaucrat exact1("Exact1", 145);
        ShrubberyCreationForm shrub("test");
        
        exact1.signForm(shrub);  // Grade 145 == requirement
        
        Bureaucrat exact2("Exact2", 137);
        exact2.executeForm(shrub);  // Grade 137 == requirement
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    
    try {
        std::cout << "\n--- Test 2: Grade boundaries ---" << std::endl;
        PresidentialPardonForm pardon("Test");
        
        Bureaucrat high("High", 5);
        high.signForm(pardon);
        high.executeForm(pardon);  // Should succeed
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

int main(void) {
    testShrubberyCreation();
    testRobotomyRequest();
    testPresidentialPardon();
    testPolymorphism();
    testEdgeCases();
    
    std::cout << "\n========== ALL TESTS COMPLETED ==========" << std::endl;
    return 0;
}
