# Exercise 00: Bureaucrat - Study Guide

## 📚 What This Exercise Teaches

This exercise introduces **C++ exception handling** and **object-oriented design** through a simple bureaucrat system with grade validation.

---

## 🎯 Core Concepts Learned

### 1. **Exception Handling in C++**

#### What are Exceptions?
Exceptions are a way to handle errors in C++ without cluttering your code with if-else checks everywhere. When something goes wrong, you "throw" an exception, and somewhere else in your code, you "catch" it.

#### The `std::exception` Base Class
```cpp
class GradeTooHighException : public std::exception
{
    public:
    virtual const char *what() const throw();
};
```

**Key Points:**
- We inherit from `std::exception` to create custom exceptions
- The `what()` method returns an error message string
- `const throw()` means this function won't throw any exceptions itself (exception specification)
- `virtual` allows derived classes to override this method
- `const` after the method name means it doesn't modify the object

#### Try-Catch Blocks
```cpp
try
{
    Bureaucrat bob("Bob", 200);  // This will throw an exception
}
catch (std::exception &e)
{
    std::cerr << "Error: " << e.what() << std::endl;
}
```

**What happens:**
1. Code in the `try` block executes
2. If an exception is thrown, execution jumps to the `catch` block
3. The `catch` block handles the error gracefully
4. Program continues after the catch block (doesn't crash)

---

### 2. **Const Correctness**

#### Const Member Variables
```cpp
class Bureaucrat {
    public:
    const std::string name;  // Cannot be changed after initialization
    int grade;               // Can be modified
};
```

**Why use const?**
- Prevents accidental modification
- Makes code intentions clear
- Enforces business logic (a bureaucrat's name shouldn't change)

#### Const Member Functions
```cpp
std::string getName() const;  // Promises not to modify the object
int getGrade() const;
```

**Rules:**
- Const functions can only call other const functions
- They can't modify member variables (unless marked `mutable`)
- They can be called on const objects

---

### 3. **Initialization Lists**

```cpp
Bureaucrat::Bureaucrat(const std::string _name, int _grade) : name(_name)
{
    setGrade(_grade);
}
```

**Why use initialization lists?**
- **Required** for const members (can't assign in body)
- More efficient (direct initialization vs assignment)
- Executes before the constructor body

**Order matters:**
- Members are initialized in the order they're declared in the class
- NOT the order in the initialization list

---

### 4. **Operator Overloading**

#### The Insertion Operator (<<)
```cpp
std::ostream& operator<<(std::ostream &out, const Bureaucrat &src)
{
    return (out << src.name << ", bureaucrat grade " << src.grade << std::endl);
}
```

**What this does:**
- Allows you to use `std::cout << bureaucrat;`
- Takes an output stream and the object to print
- Returns the stream to allow chaining: `cout << b1 << b2 << b3;`
- Must be a free function (not a member) to have `cout` on the left

#### The Assignment Operator (=)
```cpp
Bureaucrat& operator=(const Bureaucrat &src)
{
    if (this == &src)  // Self-assignment check
        return *this;
    
    this->setGrade(src.getGrade());
    return (*this);
}
```

**Key concepts:**
- Always check for self-assignment: `if (this == &src)`
- Return `*this` to allow chaining: `a = b = c;`
- Can't assign const members (name), only non-const ones
- Should maintain object invariants (validate the grade)

---

### 5. **Grade Validation Logic**

```cpp
void Bureaucrat::setGrade(int _grade)
{
    if (_grade > 150)
        throw Bureaucrat::GradeTooLowException();
    
    if (_grade < 1)
        throw Bureaucrat::GradeTooHighException();
    
    grade = _grade;
}
```

**Business Rules:**
- Grade range: 1 to 150
- Grade 1 = highest rank (most powerful)
- Grade 150 = lowest rank (least powerful)
- **Counter-intuitive:** Lower number = higher rank!

**Why throw in setGrade()?**
- Centralizes validation in one place
- Called from constructor, copy constructor, and assignment operator
- Ensures the object is **never** in an invalid state

---

### 6. **Increment/Decrement Grade Methods**

```cpp
void Bureaucrat::incrementGrade()
{
    if (grade - 1 < 1)
        throw Bureaucrat::GradeTooHighException();
    grade--;  // DECREASE number to INCREASE rank
}

void Bureaucrat::decrementGrade()
{
    if (grade + 1 > 150)
        throw Bureaucrat::GradeTooLowException();
    grade++;  // INCREASE number to DECREASE rank
}
```

**Important:**
- **Increment grade** = decrease the number (1 is better than 2)
- **Decrement grade** = increase the number (150 is worse than 149)
- Always validate before modifying

---

## 🔍 Code Flow Explanation

### When You Create a Bureaucrat:

```cpp
Bureaucrat alice("Alice", 50);
```

**Step-by-step:**
1. Memory allocated for the object
2. Initialization list runs: `name("Alice")`
3. Constructor body executes: `setGrade(50)`
4. `setGrade()` validates: 50 is between 1 and 150 ✓
5. Grade is set to 50
6. Object is now ready to use

### When You Create with Invalid Grade:

```cpp
try {
    Bureaucrat bob("Bob", 200);
} catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
}
```

**Step-by-step:**
1. Memory allocated
2. Initialization list: `name("Bob")`
3. Constructor calls `setGrade(200)`
4. `setGrade()` checks: 200 > 150 ✗
5. **Exception thrown** - object construction fails
6. Execution jumps to catch block
7. Error message printed: "grade too low"
8. Memory is cleaned up (destructor called on partial object)
9. Program continues without crash

---

## 💡 Key Takeaways

### Exception Safety
- **Never leave objects in invalid states**
- Validate in constructor (throw if invalid)
- Don't catch exceptions you can't handle properly

### RAII (Resource Acquisition Is Initialization)
- Objects should be fully initialized or not exist at all
- Constructor ensures valid state
- Destructor cleans up (printed message in this case)

### Const Correctness Benefits
- Compiler enforces immutability
- Self-documenting code
- Prevents bugs from accidental modifications

### Operator Overloading Best Practices
- Make code intuitive: `cout << object` feels natural
- Follow standard conventions
- Return references for chaining

---

## 🧪 Testing Strategy

### Test Invalid Grades
```cpp
try { Bureaucrat b("Test", 0); }    // Too high
try { Bureaucrat b("Test", 151); }  // Too low
try { Bureaucrat b("Test", -5); }   // Negative
```

### Test Valid Boundaries
```cpp
Bureaucrat b1("Best", 1);    // Highest
Bureaucrat b2("Worst", 150); // Lowest
```

### Test Grade Increment/Decrement
```cpp
Bureaucrat b("Test", 75);
b.incrementGrade();  // Now 74
b.decrementGrade();  // Back to 75
```

### Test Copy and Assignment
```cpp
Bureaucrat a("Alice", 50);
Bureaucrat b(a);           // Copy constructor
Bureaucrat c = a;          // Also copy constructor (not assignment!)
Bureaucrat d("Dave", 100);
d = a;                     // Assignment operator
```

---

## 🚫 Common Mistakes to Avoid

1. **Forgetting exception specifications on `what()`**
   ```cpp
   // Wrong:
   virtual const char *what();
   
   // Right:
   virtual const char *what() const throw();
   ```

2. **Not checking self-assignment**
   ```cpp
   Bureaucrat& operator=(const Bureaucrat &src) {
       if (this == &src) return *this;  // Essential!
       // ... rest of code
   }
   ```

3. **Confusing grade numbers**
   - Lower number = Higher rank
   - Increment grade = Decrease number
   - Decrement grade = Increase number

4. **Not initializing const members**
   ```cpp
   // Wrong:
   Bureaucrat::Bureaucrat(string _name, int _grade) {
       name = _name;  // ERROR: can't assign const member
   }
   
   // Right:
   Bureaucrat::Bureaucrat(string _name, int _grade) : name(_name) {
       // Initialize in list
   }
   ```

5. **Catching exceptions too broadly**
   ```cpp
   // Less specific:
   catch (std::exception &e)
   
   // More specific (when you need different handling):
   catch (Bureaucrat::GradeTooHighException &e)
   catch (Bureaucrat::GradeTooLowException &e)
   ```

---

## 🎓 Advanced Concepts

### Exception Hierarchy
```
std::exception (base)
    └── Bureaucrat::GradeTooHighException
    └── Bureaucrat::GradeTooLowException
```

**Catch order matters:**
```cpp
try {
    // code
}
catch (Bureaucrat::GradeTooHighException &e) {
    // Specific handling
}
catch (std::exception &e) {
    // General handling - must come after specific catches
}
```

### Why Return References?
```cpp
std::ostream& operator<<(std::ostream &out, const Bureaucrat &src);
Bureaucrat& operator=(const Bureaucrat &src);
```

**Benefits:**
- **Efficiency:** No copying large objects
- **Chaining:** `cout << a << b << c;`
- **Standard practice:** Matches standard library behavior

---

## 📖 Further Reading

- **C++ exceptions:** Learn about RAII, exception safety guarantees
- **Const correctness:** Deep dive into const methods and members  
- **Operator overloading:** Rules for different operators
- **Copy semantics:** Deep vs shallow copy, rule of three/five

---

## ✅ Checklist for Understanding

- [ ] I understand what exceptions are and when to use them
- [ ] I can explain the difference between throw and catch
- [ ] I know why const correctness matters
- [ ] I understand initialization lists and when they're required
- [ ] I can explain why operator<< is not a member function
- [ ] I know how to prevent self-assignment
- [ ] I understand the grade numbering system (1=best, 150=worst)
- [ ] I can explain RAII principles
- [ ] I know when to use references vs pointers vs values

---

**Remember:** This exercise builds the foundation for ex01 and beyond. Master these concepts before moving forward!
