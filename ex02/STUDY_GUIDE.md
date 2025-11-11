# Exercise 02: Abstract Classes and Polymorphism - COMPREHENSIVE STUDY GUIDE

## 📚 What This Exercise Teaches

This exercise introduces **abstract classes**, **polymorphism**, **virtual functions**, **inheritance hierarchies**, and **dynamic dispatch** in C++. You'll learn how to design extensible class hierarchies and leverage the power of object-oriented programming.

---

## 🎯 Core Concepts Learned

### 1. **Abstract Classes**

#### What is an Abstract Class?

An abstract class is a class that **cannot be instantiated** directly. It serves as a base class for other classes and defines an interface that derived classes must implement.

```cpp
class AForm {  // 'A' prefix commonly means "Abstract"
public:
    // Pure virtual function - makes this class abstract
    virtual void execute(Bureaucrat const &executor) const = 0;
    
    // Virtual destructor - essential for polymorphism
    virtual ~AForm();
};
```

**Key Points:**
- Contains at least one **pure virtual function** (`= 0`)
- Cannot create objects of this type: `AForm form;  // ERROR!`
- Can have pointers/references: `AForm *ptr;  // OK`
- Derived classes must implement all pure virtual functions

#### Why Use Abstract Classes?

**1. Define Interface Contracts**
```cpp
// AForm defines the contract: all forms must be executable
class AForm {
public:
    virtual void execute(Bureaucrat const &executor) const = 0;
};

// Each derived class MUST implement execute()
class ShrubberyCreationForm : public AForm {
public:
    virtual void execute(Bureaucrat const &executor) const {
        // Implementation specific to shrubbery
    }
};
```

**2. Prevent Direct Instantiation**
```cpp
AForm form;  // ERROR - can't instantiate abstract class
ShrubberyCreationForm shrub("home");  // OK - concrete class
```

**3. Enable Polymorphism**
```cpp
AForm *forms[3];
forms[0] = new ShrubberyCreationForm("home");
forms[1] = new RobotomyRequestForm("target");
forms[2] = new PresidentialPardonForm("criminal");

// Same interface, different behavior!
for (int i = 0; i < 3; i++) {
    forms[i]->execute(bureaucrat);
}
```

---

### 2. **Virtual Functions and Dynamic Dispatch**

#### The `virtual` Keyword

```cpp
class Base {
public:
    virtual void func() {  // Can be overridden
        std::cout << "Base::func()" << std::endl;
    }
};

class Derived : public Base {
public:
    virtual void func() {  // Overrides Base::func()
        std::cout << "Derived::func()" << std::endl;
    }
};
```

#### Static vs Dynamic Binding

**Static Binding (Without `virtual`):**
```cpp
class Base {
public:
    void func() { std::cout << "Base" << std::endl; }
};

class Derived : public Base {
public:
    void func() { std::cout << "Derived" << std::endl; }
};

Base *ptr = new Derived();
ptr->func();  // Prints "Base" - calls based on pointer type
```

**Dynamic Binding (With `virtual`):**
```cpp
class Base {
public:
    virtual void func() { std::cout << "Base" << std::endl; }
};

class Derived : public Base {
public:
    virtual void func() { std::cout << "Derived" << std::endl; }
};

Base *ptr = new Derived();
ptr->func();  // Prints "Derived" - calls based on actual object type
```

#### How Virtual Functions Work

**Vtable (Virtual Table):**
- Compiler creates a hidden table of function pointers for each class with virtual functions
- Each object has a hidden pointer (vptr) to its class's vtable
- When calling a virtual function, the program looks up the correct function in the vtable at runtime

```
Object Memory Layout:
┌─────────────────┐
│ vptr ───────────┼──> Vtable
├─────────────────┤    ┌──────────────┐
│ member1         │    │ execute() ───┼──> ShrubberyCreationForm::execute()
├─────────────────┤    ├──────────────┤
│ member2         │    │ ~AForm() ────┼──> ShrubberyCreationForm::~ShrubberyCreationForm()
└─────────────────┘    └──────────────┘
```

---

### 3. **Pure Virtual Functions**

#### Syntax and Meaning

```cpp
virtual void execute(Bureaucrat const &executor) const = 0;
//      ↑                                           ↑     ↑
//   virtual                                     const   pure virtual
//   (can be overridden)                    (doesn't modify)  (must override)
```

**What `= 0` Means:**
- This function has no implementation in the base class
- Derived classes **must** provide an implementation
- Makes the class abstract

#### Why Pure Virtual?

**Without pure virtual:**
```cpp
class AForm {
public:
    virtual void execute(Bureaucrat const &executor) const {
        // What would we do here? Forms have different behaviors!
    }
};
```

**With pure virtual:**
```cpp
class AForm {
public:
    // Force derived classes to implement their specific behavior
    virtual void execute(Bureaucrat const &executor) const = 0;
};
```

---

### 4. **Inheritance and Polymorphism**

#### Class Hierarchy

```
                    AForm (Abstract)
                      |
      ┌───────────────┼───────────────┐
      |               |               |
ShrubberyCreation  Robotomy    Presidential
     Form          Request         Pardon
                    Form            Form
```

#### Implementing Derived Classes

```cpp
class ShrubberyCreationForm : public AForm {
    //                           ↑
    //                      public inheritance
private:
    std::string target;  // Derived class-specific data

public:
    // Constructor calls base class constructor
    ShrubberyCreationForm(const std::string &target)
        : AForm("ShrubberyCreationForm", 145, 137), target(target) {
    }
    
    // MUST implement pure virtual function
    virtual void execute(Bureaucrat const &executor) const {
        checkExecution(executor);  // Reuse base class logic
        // Derived class-specific implementation
        // ...
    }
};
```

#### The `public` Inheritance Model

```cpp
class Derived : public Base {
    // ↑ public: Base's public members stay public in Derived
};
```

**Inheritance Access Levels:**
| Base Class Access | public Inheritance | protected Inheritance | private Inheritance |
|-------------------|-------------------|----------------------|---------------------|
| public            | public            | protected            | private             |
| protected         | protected         | protected            | private             |
| private           | not accessible    | not accessible       | not accessible      |

---

### 5. **Virtual Destructors**

#### Why Virtual Destructors are Critical

**Without virtual destructor:**
```cpp
class Base {
public:
    ~Base() { std::cout << "~Base()" << std::endl; }
};

class Derived : public Base {
private:
    int *data;
public:
    Derived() { data = new int[100]; }
    ~Derived() {
        delete[] data;  // Free memory
        std::cout << "~Derived()" << std::endl;
    }
};

Base *ptr = new Derived();
delete ptr;  // ONLY calls ~Base()! Memory leak!
// Output: ~Base()
// Derived's destructor never called - data never freed!
```

**With virtual destructor:**
```cpp
class Base {
public:
    virtual ~Base() { std::cout << "~Base()" << std::endl; }
};

class Derived : public Base {
private:
    int *data;
public:
    Derived() { data = new int[100]; }
    virtual ~Derived() {
        delete[] data;
        std::cout << "~Derived()" << std::endl;
    }
};

Base *ptr = new Derived();
delete ptr;  // Calls BOTH destructors!
// Output: ~Derived()
//         ~Base()
// Proper cleanup!
```

**Rule:** Always make destructors virtual in base classes that will be inherited from!

---

### 6. **Protected Members**

#### Access Levels Explained

```cpp
class AForm {
private:
    std::string name;  // Only AForm can access

protected:
    void checkExecution(const Bureaucrat &executor) const;
    // AForm and derived classes can access

public:
    void beSigned(const Bureaucrat &bureaucrat);
    // Everyone can access
};
```

**Why Protected?**

```cpp
class AForm {
protected:
    void checkExecution(const Bureaucrat &executor) const {
        if (!is_signed)
            throw FormNotSignedException();
        if (executor.getGrade() > grade_to_execute)
            throw GradeTooLowException();
    }
};

class ShrubberyCreationForm : public AForm {
public:
    virtual void execute(Bureaucrat const &executor) const {
        checkExecution(executor);  // Can call protected method
        // Do shrubbery-specific stuff
    }
};
```

**Benefits:**
- Reuse common logic (DRY principle)
- Maintain encapsulation (not public)
- Provide utilities to derived classes

---

### 7. **Constructor Initialization in Inheritance**

#### Calling Base Class Constructor

```cpp
class Derived : public Base {
public:
    Derived(params) : Base(base_params), derived_member(value) {
        //             ↑ Call base constructor FIRST
        //                                   ↑ Then initialize derived members
    }
};
```

**Example:**
```cpp
ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("ShrubberyCreationForm", 145, 137),  // Initialize base
      target(target) {                            // Initialize derived
}
```

**Order of Operations:**
1. Base class constructor executes
2. Derived class members initialized
3. Derived class constructor body executes

---

## 🔍 Complete Code Flow Example

### Creating and Executing a Form

```cpp
Bureaucrat boss("Boss", 1);
AForm *form = new ShrubberyCreationForm("home");
boss.signForm(*form);
boss.executeForm(*form);
delete form;
```

**Step-by-Step Execution:**

**1. Create Bureaucrat**
```cpp
Bureaucrat boss("Boss", 1);
```
- Bureaucrat constructor called
- Name set to "Boss", grade validated and set to 1

**2. Create Form (Polymorphically)**
```cpp
AForm *form = new ShrubberyCreationForm("home");
```
- Memory allocated for ShrubberyCreationForm object
- ShrubberyCreationForm constructor called:
  - Calls AForm constructor: `AForm("ShrubberyCreationForm", 145, 137)`
    - name = "ShrubberyCreationForm"
    - is_signed = false
    - grade_to_sign = 145
    - grade_to_execute = 137
    - Validates grades (all within 1-150) ✓
  - Sets target = "home"
- Pointer type is `AForm*` but object is `ShrubberyCreationForm`

**3. Sign the Form**
```cpp
boss.signForm(*form);
```
- Inside Bureaucrat::signForm():
  ```cpp
  try {
      form.beSigned(*this);  // Dereference pointer, pass boss
  ```
- Inside AForm::beSigned():
  ```cpp
  if (bureaucrat.getGrade() > this->grade_to_sign)
      // Check: 1 > 145? No ✓
      throw AForm::GradeTooLowException();
  this->is_signed = true;  // Form now signed
  ```
- Back in signForm():
  ```cpp
      std::cout << "Boss signed ShrubberyCreationForm" << std::endl;
  }
  ```

**4. Execute the Form**
```cpp
boss.executeForm(*form);
```
- Inside Bureaucrat::executeForm():
  ```cpp
  try {
      form.execute(*this);  // Polymorphic call!
  ```
  
**POLYMORPHISM IN ACTION:**
- `form` pointer type: `AForm*`
- Actual object type: `ShrubberyCreationForm`
- Because execute() is virtual, calls `ShrubberyCreationForm::execute()`

- Inside ShrubberyCreationForm::execute():
  ```cpp
  checkExecution(executor);  // Call protected method
  ```
  - Inside AForm::checkExecution():
    ```cpp
    if (!this->is_signed)  // Check: is_signed = true ✓
        throw FormNotSignedException();
    if (executor.getGrade() > this->grade_to_execute)
        // Check: 1 > 137? No ✓
        throw GradeTooLowException();
    ```
  - Back in ShrubberyCreationForm::execute():
    ```cpp
    std::ofstream file("home_shrubbery");
    file << "ASCII trees...";
    file.close();
    std::cout << "Created shrubbery file: home_shrubbery" << std::endl;
    ```
    
- Back in executeForm():
  ```cpp
      std::cout << "Boss executed ShrubberyCreationForm" << std::endl;
  }
  ```

**5. Delete the Form**
```cpp
delete form;
```
- Pointer type is `AForm*`
- Destructor is virtual!
- Calls ShrubberyCreationForm::~ShrubberyCreationForm() first
- Then calls AForm::~AForm()
- Memory freed

---

## 💡 Key Design Patterns

### 1. **Template Method Pattern**

The base class provides a template for execution:

```cpp
class AForm {
protected:
    void checkExecution(const Bureaucrat &executor) const {
        // Common logic for all forms
        if (!is_signed)
            throw FormNotSignedException();
        if (executor.getGrade() > grade_to_execute)
            throw GradeTooLowException();
    }

public:
    virtual void execute(Bureaucrat const &executor) const = 0;
    // Derived classes implement specific behavior
};
```

**Benefits:**
- Common logic in one place (checkExecution)
- Specific behavior in derived classes (execute implementation)
- No code duplication

### 2. **Polymorphic Container Pattern**

Store different form types in a single container:

```cpp
AForm *forms[3];
forms[0] = new ShrubberyCreationForm("home");
forms[1] = new RobotomyRequestForm("target");
forms[2] = new PresidentialPardonForm("criminal");

// Process all forms uniformly
for (int i = 0; i < 3; i++) {
    bureaucrat.signForm(*forms[i]);
    bureaucrat.executeForm(*forms[i]);
    delete forms[i];
}
```

**Benefits:**
- Uniform interface
- Extensible (add new form types without changing this code)
- Runtime polymorphism

### 3. **Factory-Like Construction**

Each derived class has specific requirements:

```cpp
// Different grade requirements per form type
ShrubberyCreationForm: sign 145, exec 137
RobotomyRequestForm:   sign 72,  exec 45
PresidentialPardonForm: sign 25,  exec 5
```

Hardcoded in constructors:
```cpp
ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("ShrubberyCreationForm", 145, 137), target(target) {
}
```

**Benefits:**
- Users don't need to know grade requirements
- Encapsulates form specifications
- Prevents misuse

---

## 🧪 Testing Strategy

### Test Hierarchy Structure
```cpp
// Can't instantiate abstract class
AForm form;  // Should not compile

// Can instantiate concrete classes
ShrubberyCreationForm shrub("home");  // OK
```

### Test Polymorphism
```cpp
AForm *form = new ShrubberyCreationForm("test");
form->execute(bureaucrat);  // Calls derived class method
delete form;  // Calls derived destructor first
```

### Test Each Form Type
```cpp
// Shrubbery: creates file
ShrubberyCreationForm shrub("test");
// Check that test_shrubbery file is created

// Robotomy: 50% success rate
RobotomyRequestForm robot("target");
// Run multiple times, expect ~50% success

// Presidential: just prints message
PresidentialPardonForm pardon("criminal");
// Verify message format
```

### Test Execution Requirements
```cpp
// Not signed
bureaucrat.executeForm(unsignedForm);  // Should fail

// Insufficient grade
lowRankBureaucrat.executeForm(signedForm);  // Should fail

// Both signed and sufficient grade
highRankBureaucrat.signForm(form);
highRankBureaucrat.executeForm(form);  // Should succeed
```

---

## 🚫 Common Mistakes to Avoid

### 1. **Forgetting Virtual Destructor**
```cpp
// ❌ WRONG:
class AForm {
public:
    ~AForm();  // Not virtual!
};

// ✅ CORRECT:
class AForm {
public:
    virtual ~AForm();  // Virtual!
};
```

### 2. **Not Implementing Pure Virtual Functions**
```cpp
// ❌ WRONG:
class ShrubberyCreationForm : public AForm {
    // Missing execute() implementation
};  // ERROR: Still abstract, can't instantiate!

// ✅ CORRECT:
class ShrubberyCreationForm : public AForm {
public:
    virtual void execute(Bureaucrat const &executor) const {
        // Implementation
    }
};
```

### 3. **Forgetting to Call Base Constructor**
```cpp
// ❌ WRONG:
ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : target(target) {
    // Base class default constructor called - wrong grades!
}

// ✅ CORRECT:
ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("ShrubberyCreationForm", 145, 137), target(target) {
}
```

### 4. **Not Using checkExecution()**
```cpp
// ❌ WRONG (duplicated code):
void ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
    if (!getIsSigned())
        throw FormNotSignedException();
    if (executor.getGrade() > getGradeToExecute())
        throw GradeTooLowException();
    // ... rest of implementation
}

// ✅ CORRECT (reuse base class method):
void ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
    checkExecution(executor);  // DRY principle
    // ... rest of implementation
}
```

### 5. **Slicing When Passing by Value**
```cpp
// ❌ WRONG:
void processForm(AForm form) {  // Passed by value - SLICES!
    form.execute(bureaucrat);
}

ShrubberyCreationForm shrub("test");
processForm(shrub);  // Only AForm part copied, loses derived info!

// ✅ CORRECT:
void processForm(AForm &form) {  // Pass by reference
    form.execute(bureaucrat);
}

// OR use pointer:
void processForm(AForm *form) {
    form->execute(bureaucrat);
}
```

---

## 🎓 Advanced Concepts

### Vtable Deep Dive

**Memory Layout:**
```
ShrubberyCreationForm object:
┌──────────────┐
│ vptr         │───> ShrubberyCreationForm vtable
├──────────────┤     ┌───────────────────────────────┐
│ name         │     │ execute() ────────────────────┼──> ShrubberyCreationForm::execute()
├──────────────┤     ├───────────────────────────────┤
│ is_signed    │     │ ~ShrubberyCreationForm() ─────┼──> ShrubberyCreationForm::~ShrubberyCreationForm()
├──────────────┤     └───────────────────────────────┘
│ grade_to_sign│
├──────────────┤
│ grade_to_exec│
├──────────────┤
│ target       │
└──────────────┘
```

**Function Call Resolution:**
```cpp
AForm *form = new ShrubberyCreationForm("test");
form->execute(bureaucrat);

1. Compiler generates: form->vptr->execute(form, bureaucrat)
2. Runtime looks up execute in vtable
3. Finds ShrubberyCreationForm::execute()
4. Calls that function
```

### Cost of Virtuality

**Space Overhead:**
- Each object with virtual functions: +8 bytes (64-bit) for vptr
- Each class with virtual functions: vtable stored once

**Time Overhead:**
- Virtual function call: one extra indirection (vtable lookup)
- Usually negligible compared to actual function work

**When to Use:**
- Need runtime polymorphism: Use virtual
- Performance critical, no inheritance: Don't use virtual

---

## 🔗 How This Builds on Ex00 and Ex01

| Concept | Ex00 | Ex01 | Ex02 |
|---------|------|------|------|
| **Classes** | Single class | Two classes | Class hierarchy |
| **Exceptions** | Basic throw/catch | Inter-class | Inherited |
| **Methods** | Regular | Inter-object calls | Virtual methods |
| **Polymorphism** | None | None | Full polymorphism |
| **Abstraction** | Concrete class | Concrete classes | Abstract base class |
| **Code Reuse** | None | getters/setters | Inheritance + protected methods |
| **Extensibility** | Low | Medium | High (add new forms easily) |

---

## ✅ Mastery Checklist

- [ ] I understand what abstract classes are and why they're used
- [ ] I can explain the difference between regular and pure virtual functions
- [ ] I know why virtual destructors are essential
- [ ] I understand how vtables and dynamic dispatch work
- [ ] I can implement an inheritance hierarchy correctly
- [ ] I know when to use protected vs private vs public
- [ ] I understand how to call base class constructors
- [ ] I can use polymorphism with base class pointers
- [ ] I know how to properly delete polymorphic objects
- [ ] I understand the Template Method pattern
- [ ] I can avoid object slicing
- [ ] I know how to reuse base class logic in derived classes

---

## 🎯 Real-World Applications

### Where You'll Use This

**1. GUI Frameworks**
```cpp
class Widget {
public:
    virtual void draw() = 0;
    virtual ~Widget() {}
};

class Button : public Widget {
    virtual void draw() { /* draw button */ }
};

class TextBox : public Widget {
    virtual void draw() { /* draw textbox */ }
};
```

**2. Game Engines**
```cpp
class GameObject {
public:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual ~GameObject() {}
};

class Player : public GameObject { /* ... */ };
class Enemy : public GameObject { /* ... */ };
class Item : public GameObject { /* ... */ };
```

**3. Plugin Systems**
```cpp
class Plugin {
public:
    virtual void initialize() = 0;
    virtual void execute() = 0;
    virtual ~Plugin() {}
};

// Load plugins at runtime
Plugin *plugin = loadPlugin("myplugin.so");
plugin->initialize();
plugin->execute();
```

---

## 📖 Further Reading

- **Virtual functions:** Understanding vtables and vptrs in depth
- **Abstract classes:** Interface-based design patterns
- **SOLID principles:** Especially Liskov Substitution Principle
- **Design patterns:** Strategy, Template Method, Factory
- **Multiple inheritance:** Diamond problem and virtual inheritance

---

**Remember:** Polymorphism is one of the most powerful features of OOP. Master it here, and you'll be able to design flexible, extensible systems throughout your programming career!
