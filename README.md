# Online Supermarket Shopping Simulator

## Description

The **Online Supermarket Shopping Simulator** is a C++ console-based application that simulates the experience of shopping in an online supermarket. It offers a basic but functional simulation of browsing categories, selecting products, adding items to a cart, and checking out—all within a terminal environment.

The application includes support for customer login, file-based data persistence for users and products, category-specific browsing, and a simplified cart management system. It uses Windows console functions to enhance the user interface with colors and structured formatting.

## Key Features

- Console-based UI with color formatting for better readability
- Customer login and session handling
- Product browsing by categories (e.g., Fruits, Vegetables, Household items, etc.)
- Shopping cart with support for adding/removing items
- File I/O for loading and saving product and customer data
- Order receipt generation and basic invoice display

## Technologies Used

- C++ (Object-oriented design)
- File I/O (`data.txt`, `Customer.txt`, etc.)
- Windows Console API for colored output
- Text-based menus and input handling

## Disclaimer

This was my **first project**, created as a learning exercise in C++ and basic system design. As such, it has some limitations and missing features, including but not limited to:

### Known Limitations and Missing Features

- **No Admin Panel:** There is no interface for managing products or customers from within the app.
- **No Input Validation:** Some user inputs may cause unexpected behavior due to lack of rigorous validation.
- **Limited Error Handling:** File errors, invalid states, or incorrect data formats are not fully handled.
- **No Persistence Across Sessions for Cart or Orders:** Orders are not saved beyond the session.
- **No Sorting or Searching:** Products are not sorted, and there is no search functionality.
- **No Pricing Calculations with Discounts/Taxes:** Prices are basic and static, with no promotion or tax logic.
- **Console-only UI:** The user interface is entirely text-based, which limits usability and interactivity.

Despite these limitations, this project demonstrates the fundamentals of structured programming, file management, and basic UI design in a C++ environment.

---


