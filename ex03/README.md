# Exercise 03: Intern (Factory Pattern)

## 📋 Overview

**Objective**: Implement an `Intern` class that creates different form types using the **Factory Pattern** with member function pointers, avoiding long if/else chains.

**Key Concept**: Factory Pattern - A creational design pattern that provides an interface for creating objects without specifying their exact class.

---

## 🎯 Requirements

### The Intern Class

The intern has:
- **No grade, no name, no unique characteristics**
- One important capability: `makeForm()` function

### makeForm() Function

```cpp
AForm* makeForm(const std::string &formName, const std::string &target);
```

**Behavior:**
- Takes two strings: form name and target
- Returns pointer to appropriate form type
- Prints: `"Intern creates <form>"`
- Throws exception if form name doesn't exist

### Supported Form Types

| Form Name | Class | Target Example |
|-----------|-------|----------------|
| `"shrubbery creation"` | `ShrubberyCreationForm` | "home" |
| `"robotomy request"` | `RobotomyRequestForm` | "Bender" |
| `"presidential pardon"` | `PresidentialPardonForm` | "Arthur Dent" |

### ⚠️ Important Constraint

> **"Avoid unreadable and ugly solutions like if/else if/else forests."**

Must use elegant solution with **member function pointers** and **array-based lookup**.

---

## 💡 Implementation Strategy

### The Elegant Solution

```cpp
// Define struct mapping names to creators
struct FormType {
    std::string name;
    AForm* (Intern::*creator)(const std::string &target);
};

// Use array for lookup
FormType formTypes[] = {
    {"shrubbery creation", &Intern::createShrubberyForm},
    {"robotomy request", &Intern::createRobotomyForm},
    {"presidential pardon", &Intern::createPresidentialForm}
};

// Loop to find match (not if/else!)
for (int i = 0; i < 3; i++) {
    if (formTypes[i].name == formName) {
        return (this->*(formTypes[i].creator))(target);
    }
}
```

### Why This Is Better

| If/Else Chain | Factory Pattern |
|---------------|-----------------|
| ❌ Code duplication | ✅ Single success path |
| ❌ Hard to extend | ✅ Easy to add new types |
| ❌ Violates DRY | ✅ Data-driven |
| ❌ Error-prone | ✅ Maintainable |

---

## 📁 File Structure

```
ex03/
├── includes/
│   ├── Bureaucrat.hpp
│   ├── AForm.hpp
│   ├── ShrubberyCreationForm.hpp
│   ├── RobotomyRequestForm.hpp
│   ├── PresidentialPardonForm.hpp
│   └── Intern.hpp                    ← New!
├── srcs/
│   ├── Bureaucrat.cpp
│   ├── AForm.cpp
│   ├── ShrubberyCreationForm.cpp
│   ├── RobotomyRequestForm.cpp
│   ├── PresidentialPardonForm.cpp
│   ├── Intern.cpp                    ← New!
│   └── main.cpp
├── Makefile
└── STUDY_GUIDE.md
```

---

## 🔑 Key Concepts

### 1. Member Function Pointers

```cpp
// Syntax: ReturnType (ClassName::*pointerName)(Parameters);
AForm* (Intern::*creator)(const std::string &target);

// Taking address
&Intern::createShrubberyForm

// Calling
(this->*creator)(target)
```

### 2. Factory Pattern Components

```
┌─────────────────────────────────────┐
│         Factory Pattern             │
├─────────────────────────────────────┤
│ 1. Product Interface (AForm*)       │
│ 2. Concrete Products (Forms)        │
│ 3. Creator Methods (private)        │
│ 4. Factory Method (makeForm)        │
│ 5. Lookup Table (FormType array)    │
└─────────────────────────────────────┘
```

### 3. Exception Handling

```cpp
class FormNotFoundException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "Form type not found!";
    }
};
```

---

## 🧪 Usage Example

### Basic Usage

```cpp
Intern someRandomIntern;
AForm* rrf;

rrf = someRandomIntern.makeForm("robotomy request", "Bender");
// Output: "Intern creates robotomy request"

std::cout << *rrf << std::endl;
delete rrf;
```

### Complete Workflow

```cpp
// 1. Create intern
Intern intern;

// 2. Make form
AForm *form = intern.makeForm("presidential pardon", "Arthur Dent");

// 3. Use with bureaucrat
Bureaucrat president("President", 1);
president.signForm(*form);
president.executeForm(*form);

// 4. Clean up
delete form;
```

### Error Handling

```cpp
try {
    Intern intern;
    AForm *form = intern.makeForm("invalid form", "target");
    delete form;
}
catch (Intern::FormNotFoundException &e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

---

## ✅ Testing Checklist

### Required Tests

- [ ] Create each valid form type
- [ ] Verify correct form returned
- [ ] Test with invalid form names
- [ ] Integration with Bureaucrat
- [ ] Exception handling
- [ ] Memory leak check (no leaks!)
- [ ] Copy constructor works
- [ ] Assignment operator works

### Edge Cases

- [ ] Empty form name
- [ ] Case sensitivity (should fail)
- [ ] Extra spaces (should fail)
- [ ] Multiple forms from one intern
- [ ] Form deletion doesn't affect intern

---

## 🎓 Learning Objectives

After completing this exercise, you should understand:

1. **Factory Pattern**
   - Purpose and benefits
   - When to use it
   - How to implement it

2. **Member Function Pointers**
   - Syntax and declaration
   - Taking addresses of member functions
   - Calling through pointers

3. **Design Principles**
   - Separation of concerns
   - Open/Closed Principle
   - Don't Repeat Yourself (DRY)
   - Data-driven programming

4. **Code Quality**
   - Avoiding code smells
   - Writing maintainable code
   - Scalability considerations

---

## 🔍 Common Issues

### Issue 1: Syntax Errors with Function Pointers

**Problem:**
```cpp
AForm* creator(const std::string &target);  // Wrong!
```

**Solution:**
```cpp
AForm* (Intern::*creator)(const std::string &target);  // Correct!
```

### Issue 2: Calling Function Pointers

**Problem:**
```cpp
return formTypes[i].creator(target);  // Won't compile!
```

**Solution:**
```cpp
return (this->*(formTypes[i].creator))(target);  // Correct!
```

### Issue 3: Memory Leaks

**Problem:**
```cpp
AForm *form = intern.makeForm(...);
// Forgot to delete!
```

**Solution:**
```cpp
AForm *form = intern.makeForm(...);
// ... use form ...
delete form;  // Always delete!
```

---

## 🚀 Extension Ideas

Want to go further? Try:

1. **Add More Form Types**
   - Vacation request
   - Budget approval
   - Hire form

2. **Improve Lookup**
   - Use `std::map` for O(log n) lookup
   - Case-insensitive matching
   - Alias support ("robo" → "robotomy request")

3. **Better Error Messages**
   - Suggest similar form names
   - List all available forms
   - Detailed error reporting

4. **Configuration**
   - Load form types from file
   - Runtime registration
   - Plugin system

---

## 📚 Resources

- **STUDY_GUIDE.md**: Deep dive into Factory Pattern and function pointers
- **VISUAL_GUIDE.md**: Visual diagrams and code flow
- **ex02/**: Review abstract classes and polymorphism
- **ex01/**: Review basic form and bureaucrat interaction

---

## ⚡ Quick Start

### Compile

```bash
make
```

### Run

```bash
./Bureaucrat
```

### Clean

```bash
make fclean
```

---

## 🎯 Success Criteria

Your implementation is complete when:

✅ **Functionality**
- All three form types can be created
- Invalid names throw exceptions
- Integration with Bureaucrat works

✅ **Design**
- Uses Factory Pattern correctly
- No if/else chain for form creation
- Member function pointers used properly

✅ **Quality**
- No memory leaks
- Exception-safe
- Follows Orthodox Canonical Form

✅ **Testing**
- All edge cases covered
- Error handling verified
- Output matches expected format

---

## 💬 Subject Quote

> "Avoid unreadable and ugly solutions like if/else if/else forests."

This exercise teaches you that **how you solve a problem** is just as important as **solving it**. The Factory Pattern with function pointers is elegant, maintainable, and scalable—exactly what professional C++ developers strive for!

---

**Happy coding! May your interns create many forms! 📝✨**
