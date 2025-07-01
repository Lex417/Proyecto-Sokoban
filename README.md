# 📦 Sokoban: A C++ Puzzle Game

## Project Overview

This project is an implementation of the classic puzzle game "Sokoban," developed as part of the **Data Structures (EIF207)** course at **Universidad Nacional, Costa Rica**, in **October 2017**. It was a collaborative effort by **Leonardo Hidalgo Fonseca** and **Enzo Darío Quesada Rojas**, aimed at applying fundamental data structures and algorithms in a practical, graphical context.

The goal of Sokoban is simple yet challenging: guide a character to push boxes onto designated target points within a confined maze. This particular implementation features multiple levels, intuitive controls, and a custom graphical interface

<img src="https://github.com/user-attachments/assets/cad54982-73ae-4ef8-888a-94f7ded4b491" width="500" alt="game">


## 🎮 Gameplay & Features

Our Sokoban game provides a complete experience with several key features:

* **Multi-Level Challenge:** Navigate through **5 distinct levels**, each with increasing complexity. Levels can be loaded individually or played in sequential order, progressing automatically upon successful completion.

* **Flexible Controls:** Players can move the character using both the **arrow keys** and the **WASD** key set, offering ergonomic choices for gameplay.

* **In-Game Management:** A convenient in-game menu allows for quick actions:

  * **Restart Level:** Pressing `LShift` instantly resets the character and all boxes to their starting positions, perfect for when you find yourself in an unsolvable state.

  * **Return to Main Menu:** The `Backspace` key provides a quick exit back to the main menu.

  * **Exit Game:** Pressing `Escape` will immediately close the application.

## ⚙️ Technical Architecture & Implementation

The game's foundation is built on robust C++ programming and a thoughtful application of data structures and object-oriented principles to manage game state and graphical rendering.

### Data Structures: The Map's Backbone

The game maps are dynamically represented using a system of **linked lists**. Specifically, each level is composed of **8 linked lists, each containing 9 nodes**. These lists are intelligently concatenated to form the complete 2D game board. Each node within these lists stores a specific integer value (ID) that dictates the type of element present at that location:

* `0 = Empty Space`

* `1 = Player Character`

* `2 = Box`


* `3 = Wall`

![front](https://github.com/user-attachments/assets/c188ef6d-cdc9-47a5-9a2c-20b48eb4b1dc)
![back](https://github.com/user-attachments/assets/7d023973-52a1-4f99-a11d-439f5c32d4c6)
![right](https://github.com/user-attachments/assets/65e30431-f37f-40ff-9756-f340621d2134)
![left](https://github.com/user-attachments/assets/526640ef-2d80-401b-a7e5-cbad3b436ea7)
![wall](https://github.com/user-attachments/assets/fd14976a-f933-4e27-9650-0581b4f2f855)
![floor](https://github.com/user-attachments/assets/839de91e-54ca-4bfa-9687-12b5864c88e3)
![box](https://github.com/user-attachments/assets/1580f704-515e-4eeb-8227-268950ba1ac8)
![point](https://github.com/user-attachments/assets/252dda5b-ef82-4643-9b84-bfad95296442)


* `4 = Goal Point`

This node-based representation allows for efficient manipulation of the game state as the character moves and pushes boxes.

### Object-Oriented Design

The project's architecture is structured around several key classes:

* **`Objects` Class:** This foundational class holds the integer IDs for all game elements (e.g., `emptySpace`, `player`, `box`, `wall`, `finish`).

* **`List` Class:** Inheriting from `Objects`, the `List` class manages the linked list structures that compose the game board. It is responsible for interpreting the node values and providing them to the graphical interface for rendering.

* **`Interface` Class:** This class serves as the primary bridge between the game's logic and its graphical representation. It invokes all graphical rendering operations, manages keyboard event detection (for player movement and menu interactions), and orchestrates the main game loop. It also contains specific lists for handling keyboard events and other program functions.

### Graphics & API Development

The graphical mode, event handling, and the overall API for the game were entirely developed using the **SFML 2.0 (Simple and Fast Multimedia Library)**. SFML was chosen for its simplicity, speed, and powerful capabilities in:

* **Sprite Management:** Handling the rendering and animation of character, box, and wall sprites.

* **Movement:** Facilitating smooth character and object movement on the screen.

* **Keyboard Recognition:** Processing player input from the keyboard for game controls and menu navigation.

* **Window Management:** Creating and managing the game window.

The entire development process was conducted within the **Visual Studio Community 2017** IDE.

## 🚀 Getting Started (How to Run)

To set up and run this Sokoban game:

1. **Clone the repository:**

git clone https://github.com/your-username/sokoban-game.git
cd sokoban-game

2. **Configure SFML 2.0:** Ensure that SFML 2.0 is correctly set up and linked with your C++ development environment (e.g., Visual Studio). You can find detailed setup guides in the official SFML documentation.

3. **Build and Run:** Open the project in Visual Studio Community 2017, build the solution, and then run the executable.

## ⚠️ Limitations & Key Learnings

During the development of this project, we encountered a couple of notable limitations that provided valuable learning experiences:

* **Replay Feature Implementation:** The game is designed to track player movements for a replay. However, implementing a visual replay directly within the graphical game window proved challenging. This was primarily due to specific exceptions encountered in `if` statements related to linked list node manipulation (e.g., `temp->next->next = nullptr`), which behaved differently compared to real-time character movement. As a workaround, the replay functionality currently prints the sequence of movements to the console. If a level is restarted or the player returns to the main menu, the replay sequence is reset.

* **Saved Game Loading:** The functionality to load a previously saved game currently resets the map to its initial state (level 0). This limitation arose from debugger errors and complexities in accurately saving and restoring the precise state of all linked list nodes and their interconnections. Consequently, maps are always loaded from their initial configuration.

These challenges underscored the complexities of debugging intricate data structures in a graphical application and provided deep insights into managing game state persistence and dynamic object manipulation.

## 📚 References

This project was developed with the aid of various online resources and academic materials:

* **SFML Documentation:** The official SFML 2.0 documentation was a primary source for library usage.

* **YouTube Tutorials:** Channels like "Sonar Systems" (<https://www.youtube.com/user/sonarsystemslimited>) and "Hilze Vonck" (<https://www.youtube.com/channel/UC8C7ncaMYnXyu-pRU0S9FLg>) were invaluable for learning about sprites, movement, and keyboard input.

* **Academic Text:** "Programación en C, Metodología, Algoritmos y estructura de datos" by Joyanes L. (2015).

* **Online Forums:** StackOverflow (<https://stackoverflow.com/>) was a key resource for resolving specific programming challenges related to linked lists.

Feel free to explore the code, provide feedback, or even contribute to this classic puzzle game!
