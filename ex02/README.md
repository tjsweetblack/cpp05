# Exercise 02: No, you need form 28B, not 28C...

## Overview
This exercise extends ex01 by introducing **abstract classes** and **polymorphism**. The `Form` class is renamed to `AForm` (Abstract Form) and becomes an abstract base class with three concrete implementations.

---

## What's New in Ex02

### Abstract Base Class (AForm)
- Renamed from `Form` to `AForm` to indicate it's abstract
- Contains a **pure virtual function**: `execute()`
- Cannot be instantiated directly
- Serves as a base for concrete form types
- Has a **virtual destructor** for proper cleanup

### Three Concrete Form Classes

#### 1. ShrubberyCreationForm
- **Required grades:** sign 145, exec 137
- **Behavior:** Creates a file `<target>_shrubbery` with ASCII trees
- **Target:** Location where shrubbery should be planted

#### 2. RobotomyRequestForm
- **Required grades:** sign 72, exec 45  
- **Behavior:** Makes drilling noises, then 50% success rate robotomy
- **Target:** The entity to be robotomized

#### 3. PresidentialPardonForm
- **Required grades:** sign 25, exec 5
- **Behavior:** Informs that target has been pardoned by Zaphod Beeblebrox
- **Target:** The person being pardoned

### New Method: execute()
- **Pure virtual in AForm:** `virtual void execute(Bureaucrat const &executor) const = 0;`
- **Implemented in each concrete class** with specific behavior
- **Checks requirements:**
  - Form must be signed
  - Executor's grade must be high enough
  - Throws appropriate exceptions if requirements not met

### Updated Bureaucrat Class
- **New method:** `executeForm(AForm const &form) const`
- Attempts to execute the form
- Prints success message or error message

---

## Key Concepts Demonstrated

### 1. Abstract Classes
```cpp
class AForm {
public:
    virtual void execute(Bureaucrat const &executor) const = 0;  // Pure virtual
    virtual ~AForm();  // Virtual destructor
};

// Cannot do this:
AForm form;  // ERROR: Cannot instantiate abstract class

// Can do this:
AForm *form = new ShrubberyCreationForm("home");  // OK: Polymorphism
```

### 2. Polymorphism
```cpp
// Same interface, different behaviors
AForm *forms[3];
forms[0] = new ShrubberyCreationForm("home");
forms[1] = new RobotomyRequestForm("target");
forms[2] = new PresidentialPardonForm("criminal");

for (int i = 0; i < 3; i++) {
    forms[i]->execute(bureaucrat);  // Different behavior each time!
}
```

### 3. Virtual Destructors
```cpp
AForm *form = new ShrubberyCreationForm("test");
delete form;  // Calls both destructors properly
// Without virtual destructor, only AForm destructor would be called!
```

### 4. Protected Methods
```cpp
class AForm {
protected:
    void checkExecution(const Bureaucrat &executor) const;
    // Derived classes can use this, external code cannot
};
```

### 5. Template Method Pattern
```cpp
// Base class provides template
void AForm::checkExecution(...) {
    // Common validation for all forms
}

// Derived classes use it
void ShrubberyCreationForm::execute(...) {
    checkExecution(executor);  // Reuse base class logic
    // Then do specific behavior
}
```

---

## Implementation Details

### Class Hierarchy
```
AForm (Abstract Base)
├── ShrubberyCreationForm
├── RobotomyRequestForm
└── PresidentialPardonForm
```

### Grade Requirements
| Form Type | Sign Grade | Execute Grade |
|-----------|------------|---------------|
| ShrubberyCreation | 145 | 137 |
| RobotomyRequest | 72 | 45 |
| PresidentialPardon | 25 | 5 |

### Exceptions
- `AForm::GradeTooHighException` - Grade < 1
- `AForm::GradeTooLowException` - Grade > 150 or insufficient for action
- `AForm::FormNotSignedException` - Trying to execute unsigned form

---

## How It Works

### Creating and Executing a Form

```cpp
// 1. Create a bureaucrat and form
Bureaucrat alice("Alice", 1);
ShrubberyCreationForm shrub("garden");

// 2. Sign the form
alice.signForm(shrub);
// Output: Alice signed ShrubberyCreationForm

// 3. Execute the form
alice.executeForm(shrub);
// Output: Created shrubbery file: garden_shrubbery
//         Alice executed ShrubberyCreationForm
```

### Execution Flow

1. **Bureaucrat::executeForm()** is called
2. Catches any exceptions and prints appropriate message
3. Calls **form.execute(bureaucrat)**
4. Because execute() is virtual, the actual object type's method is called
5. Inside the concrete class's execute():
   - Calls **checkExecution()** to validate
   - Performs form-specific action

### Validation Order

```cpp
void AForm::checkExecution(const Bureaucrat &executor) const {
    // 1. Check if signed
    if (!is_signed)
        throw FormNotSignedException();
    
    // 2. Check executor's grade
    if (executor.getGrade() > grade_to_execute)
        throw GradeTooLowException();
}
```

---

## Compilation

```bash
make
```

## Running

```bash
./Bureaucrat
```

## Expected Output

The program tests:
- ✅ Valid execution (signed + sufficient grade)
- ✅ Execution without signing (fails)
- ✅ Execution with insufficient grade (fails)
- ✅ Each form type's specific behavior
- ✅ Polymorphism with base class pointers
- ✅ Edge cases (exact grade requirements)

---

## Files Structure

```
ex02/
├── Makefile
├── includes/
│   ├── AForm.hpp
│   ├── Bureaucrat.hpp
│   ├── ShrubberyCreationForm.hpp
│   ├── RobotomyRequestForm.hpp
│   └── PresidentialPardonForm.hpp
├── srcs/
│   ├── AForm.cpp
│   ├── Bureaucrat.cpp
│   ├── ShrubberyCreationForm.cpp
│   ├── RobotomyRequestForm.cpp
│   ├── PresidentialPardonForm.cpp
│   └── main.cpp
├── STUDY_GUIDE.md      ← Comprehensive concepts explanation
└── VISUAL_GUIDE.md     ← Diagrams and flowcharts
```

---

## Study Materials

### 📚 STUDY_GUIDE.md
Comprehensive guide covering:
- Abstract classes in depth
- Virtual functions and dynamic dispatch
- Pure virtual functions
- Inheritance and polymorphism
- Virtual destructors (why essential)
- Protected members
- Template Method pattern
- Common mistakes and how to avoid them
- Real-world applications
- Complete code flow examples

### 📊 VISUAL_GUIDE.md
Visual reference including:
- Class hierarchy diagrams
- Polymorphism flow charts
- Virtual function call flow
- Memory layout with vtables
- Constructor/destructor call chains
- Pure virtual function concept
- Protected member access diagrams
- Grade requirements visualization
- Object slicing warnings

---

## Key Takeaways

### Design Benefits
✅ **Extensibility:** Add new form types without changing existing code  
✅ **Code Reuse:** Common logic in base class (checkExecution)  
✅ **Polymorphism:** Same interface, different behaviors  
✅ **Type Safety:** Compiler enforces implementation of pure virtual functions  
✅ **Clean Design:** Separation of concerns, each form knows its own behavior  

### C++ Features Mastered
✅ Abstract classes and pure virtual functions  
✅ Dynamic polymorphism with virtual functions  
✅ Virtual destructors for proper cleanup  
✅ Protected members for derived class utilities  
✅ Inheritance hierarchies  
✅ Vtables and dynamic dispatch  
✅ Object-oriented design patterns  

---

## Testing Checklist

- [ ] Cannot instantiate AForm directly
- [ ] Can create concrete form objects
- [ ] Polymorphism works with base class pointers
- [ ] Each form type has correct behavior
- [ ] Execution requires form to be signed
- [ ] Execution requires sufficient executor grade
- [ ] Proper exceptions thrown for violations
- [ ] Virtual destructors work correctly
- [ ] ShrubberyCreationForm creates file
- [ ] RobotomyRequestForm has ~50% success rate
- [ ] PresidentialPardonForm prints pardon message

---

## Next Steps

This exercise builds the foundation for:
- **Ex03:** Likely adds more features (Intern class, form creation)
- **Advanced polymorphism:** Multiple inheritance, virtual base classes
- **Design patterns:** Factory, Strategy, Observer
- **Real-world OOP:** GUI frameworks, game engines, plugin systems

---

**Remember:** Understanding polymorphism is crucial for modern C++ programming. Take time to fully grasp these concepts!
