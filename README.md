# Supermarket Checkout System

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Design Choices](#design-choices)
- [Architecture](#architecture)
- [Installation](#installation)
  - [Prerequisites](#prerequisites)
  - [Building from Source](#building-from-source)
- [Running the Application](#running-the-application)
- [Usage](#usage)
  - [Scanning Items](#scanning-items)
  - [Applying Deals](#applying-deals)
  - [Generating Receipts](#generating-receipts)
- [Testing](#testing)
- [Examples](#examples)
- [Future Improvements](#future-improvements)
- [Contact](#contact)

## Introduction
The **Supermarket Checkout System** is a C++ application designed to simulate a supermarket's checkout process. It allows scanning of items, applies various promotional deals, and generates detailed receipts for customers. The system is built with modularity and extensibility in mind, enabling easy integration of new features and deals.

## Features
- **Item Management**: Load and manage a catalog of items with unique IDs, names, and prices.
- **Deal Application**: Supports multiple deal types, such as:
  - **Deal Type 1**: Buy X get one free (e.g., Buy 2 get 1 free).
  - **Deal Type 2**: Buy a combination of items, get the cheapest free.
- **Receipt Generation**: Produces detailed receipts outlining purchased items, applied deals, and total costs.
- **Unit Testing**: Comprehensive test suite using Catch2 to ensure reliability.
- **Cross-Platform Compatibility**: Easily buildable and distributable on both Windows and macOS platforms.

## Design Choices
### Modular Architecture
The system is divided into distinct modules for better maintainability and scalability:

- **Item Management (`Item` Class)**: Represents individual items with properties like ID, name, and price.
- **Purchased Items (`PurchasedItem` Class)**: Extends `Item` to include purchase-specific information such as deal application status.
- **Deal Handling (`Deal` Classes)**: Abstract base class with derived classes for specific deal types, promoting extensibility.
- **Checkout Process (`Checkout` Class)**: Manages the overall checkout flow, including scanning items, applying deals, and generating receipts.

### Use of nlohmann/json
Chosen for its ease of use and seamless integration with C++, `nlohmann/json` handles JSON parsing, allowing dynamic loading of items and deals from external files.

### Testing with Catch2
Catch2 provides a simple and powerful framework for writing unit tests, ensuring that each component behaves as expected.

## Architecture
### Main Program (`main.cpp`)
- Initializes the checkout process.
- Loads items and deals from a JSON file.
- Handles user interactions for scanning items.
- Applies relevant deals.
- Generates and displays the receipt.

### Classes
- **Item**: Represents store items.
- **PurchasedItem**: Represents items in the cart with deal information.
- **Deal**: Abstract base class for different deal types.
- **DealType1 & DealType2**: Concrete implementations of specific deals.
- **Checkout**: Orchestrates the scanning, deal application, and receipt generation.

### Testing
- Located in the `tests/` directory.
- Utilizes Catch2 for writing and executing tests.
- Include an actual architecture diagram image (`architecture.png`) in your project repository for better visualization.

## Installation

### Prerequisites
- **C++ Compiler**: Supports C++17 (e.g., GCC 7+, Clang 5+, Visual Studio 2017+)
- **CMake**: Version 3.10 or higher
- **Git**: For cloning the repository

**Dependencies**:
- `nlohmann/json` for JSON parsing
- `Catch2` for unit testing

### Building from Source

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/jrwecler/Supermarket-Check-Out.git
    cd SupermarketCheckoutSystem
    ```
    _Or extract the provided .zip file_

2. **Create a Build Directory**:
    ```bash
    mkdir build
    cd build
    ```

3. **Configure the Project with CMake**:

    - **On macOS/Linux**:
        ```bash
        cmake ..
        ```

    - **On Windows (Using Visual Studio)**:
        ```bash
        cmake .. -G "Visual Studio 16 2019"
        ```

4. **Build the Project**:

    - **On macOS/Linux**:
        ```bash
        make
        ```

    - **On Windows**:
        Open the generated `.sln` file in Visual Studio and build the solution.

5. **Generate Packages (Optional)**:
    To create distributable packages:
    ```bash
    cpack
    ```
    This will generate packages like `.zip`, `.tar.gz`, and platform-specific installers.

## Running the Application
After building, the executable can be found in the `bin` directory of the package or build.

1. **Navigate to the `bin` Directory**:
    ```bash
    cd bin
    ```

2. **Run the Application**:

    - **On macOS/Linux**:
        ```bash
        ./SupermarketCheckout
        ```

    - **On Windows**:
        ```bash
        SupermarketCheckout.exe
        ```

**Important**:
Ensure that the `data` directory is located at the same hierarchical level as the `bin` directory.

The directory structure should look like this:
```plaintext
SupermarketCheckout/
├── bin/
│   └── SupermarketCheckoutSystem
└── data/
    └── data.json
```

## Usage
Once the application is running, follow these steps to use the Supermarket Checkout System.

### Scanning Items
Input the item ID along with the quantity you wish to purchase.

**Format:**

```php
<item_id> <quantity>
```

**Example:**
```php
A1 3
B2 1
C3 2
```
Type `help` to display available commands.

### Applying Deals
After scanning all desired items, the system automatically applies relevant deals based on the loaded deal configurations.

### Generating Receipts
Upon completion, the system generates a detailed receipt displaying:
- List of purchased items with quantities and individual prices.
- Applied deals and their impact on pricing.
- Total cost after applying deals.

**Example Receipt:**
```markdown
--- Customer Receipt ---
Apple x4                       $      4.00
  Discount (Type 1)           -$      1.00
Banana x1                      $      0.50
  Discount (Type 2)           -$      0.50
Cherry x1                      $      2.00

--- Discounts Applied ---
Deal Type 1 applied to 3 x Apple (-$1.00)
Deal Type 2 applied to Apple, Banana, Cherry (-$0.50)

Total before discounts         $      6.50
Total savings                 -$      1.50
Total after discounts          $      5.00
Thank you for shopping with us!
```

## Testing
To ensure everything is working correctly, execute the test suite.

```bash
# From the build directory
ctest
```

**Expected Output:**
```markdown
Test project /path/to/build
    Start 1: AllTests
1/1 Test #1: AllTests .........................   Passed    0.26 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.26 sec
```

_Note_: Ensure all tests pass before proceeding with packaging.

## Examples
### Example 1: Simple Purchase
**Scenario:** A customer buys 3 Apples and 1 Banana.

**Input:**
```markdown
A1 3
B2 1
```

**Output Receipt:**
```markdown
--- Customer Receipt ---
Apple x3                       $      3.00
  Discount (Type 1)           -$      1.00
Banana x1                      $      0.50

--- Discounts Applied ---
Deal Type 1 applied to 3 x Apple (-$1.00)

Total before discounts         $      3.50
Total savings                 -$      1.00
Total after discounts          $      2.50
Thank you for shopping with us!
```

**Explanation:**

- **Deal Type 1:** Buy 2 Apples, get 1 free.
- Customer pays for 2 Apples ($2.00) and gets 1 free Apple (-$1.00), plus 1 Banana ($0.50).
- **Total:** $2.00 + $0.50 = $2.50

### Example 2: Multiple Deals
**Scenario:** A customer buys 4 Apples, 1 Banana, and 1 Cherry.

**Input:**
```markdown
A1 4
B2 1
C3 1
```

**Output Receipt:**
```markdown
--- Customer Receipt ---
Apple x4                       $      4.00
  Discount (Type 1)           -$      1.00
Banana x1                      $      0.50
  Discount (Type 2)           -$      0.50
Cherry x1                      $      2.00

--- Discounts Applied ---
Deal Type 1 applied to 3 x Apple (-$1.00)
Deal Type 2 applied to Apple, Banana, Cherry (-$0.50)

Total before discounts         $      6.50
Total savings                 -$      1.50
Total after discounts          $      5.00
Thank you for shopping with us!
```
**Explanation:**

- **Deal Type 1:** Buy 2 Apples, get 1 free.
- **Deal Type 2:** Buy a combination of Apple, Banana, and Cherry to get the cheapest item free (Banana).
- Customer pays for 3 Apples ($3.00), gets 1 free Apple, pays for Cherry ($2.00), and gets Banana free.
- **Total:** $3.00 + $2.00 = $5.00

## Future Improvements
While the Supermarket Checkout System currently fulfills its core functionalities, there are several areas for potential enhancement:

1. **Expanded Test Cases:**

  - Develop more comprehensive unit tests covering edge cases, such as invalid inputs, large quantities, and simultaneous deal applications.

2. **Implementing New C++ Features:**

  - Utilize modern C++ features like smart pointers, lambda expressions, and concurrency to improve code efficiency and safety.

3. **Graphical User Interface (GUI):**

  - Create a simple GUI using frameworks like Qt or wxWidgets to provide a more user-friendly interaction compared to the command-line interface.

4. **Receipt Exporting:**

  - Implement functionality to export receipts to external files (e.g., .txt, .pdf) for record-keeping and customer convenience.

5. **Database Integration:**

  - Integrate a database (e.g., SQLite) to manage items and deals more efficiently, enabling dynamic updates without modifying JSON files.

6. **Support for Multiple Deal Types:**

  - Introduce additional deal types, such as bulk discounts, tiered pricing, or time-based promotions.

7. **Logging and Monitoring:**

  - Implement logging mechanisms to track transactions, errors, and system performance for maintenance and auditing purposes.


## Contact
For any inquiries or support, please contact:

- **Email**: jwecler@gmail.com
- **GitHub**: jrwecler

