# 📦 **EaseDeliver**

Welcome to **EaseDeliver**, a comprehensive logistics software solution designed to streamline and simplify your delivery processes. Whether you're handling a small fleet or a large-scale delivery operation, EaseDeliver provides the tools you need to manage routes, track shipments, and ensure efficient delivery.

## 🚀 **Features**

- **Route Optimization**: Calculate the shortest paths for your deliveries.
- **Real-Time Updates**: Keep track of trucks and shipments in real-time.
- **Flexible Routing**: Adjust routes dynamically based on current conditions.
- **User-Friendly Interface**: Easy-to-use interface designed for efficiency.

## 🛠️ **Installation**

To get started with EaseDeliver, follow these steps:

1. **Clone the repository**:
    ```bash
    git clone https://github.com/maksymsyr/EaseDeliver.git
    cd EaseDeliver
    ```

2. **Build the project**:
    Ensure you have a C compiler installed (like `gcc`), then run:
    ```bash
    gcc -o EaseDeliver main.c mapping.c trucksNboxes.c -lm
    ```

3. **Run the program**:
    ```bash
    ./EaseDeliver
    ```

## 📋 **Usage**

Upon running the program, you'll be greeted with the main menu of **Seneca College Deliveries**. Follow the prompts to manage your delivery routes by entering shipment details.

### **Input Format**

Enter shipment details in the following format:

**weight size destinationX destinationY**

- **weight**: The weight of the shipment.
- **size**: The size of the shipment.
- **destinationX**: The X-coordinate of the destination.
- **destinationY**: The Y-coordinate of the destination.

**Example:**

**5.5 2.3 12 B**

### **Stopping the Program**

To stop the program, simply enter:

**0 0 x**

## 📂 **Project Structure**

- **main.c**: The main program logic, handling user input and managing trucks and routes.
- **mapping.h/c**: Functions for map and route management.
- **trucksNboxes.h/c**: Functions for handling trucks and box loading.

## 🔧 **Debugging**

If you encounter any issues, you can enable debug mode by setting the `debug` variable to `1` in `main.c`. This will provide additional output useful for troubleshooting.

```c
// debug
int debug = 1;

```
## 🗺️ **Map Printing**

Control map printing with the `printOutMap` variable:

```c
// print map
int printOutMap = 1;  // Set to 0 to disable map printing
```

Enjoy using **EaseDeliver!** 🚚📦✨
