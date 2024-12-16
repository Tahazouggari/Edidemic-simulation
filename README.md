# Epidemic Simulation Project

## Team Members
- **Mohamed Taha Brida**
- **Johann Ly**
- **Taha Zouggari**
- **Mohamed Toujani**

## Project Description
This project simulates the spread of an epidemic within a city, using various mechanisms such as inter-process communication, shared memory, and threading. The goal is to model citizen roles and their interactions to manage and mitigate the contamination.

## Setup and Execution
### Prerequisites
- A Linux environment (for ncurses or graphical libraries).
- C compiler (e.g., `gcc`).

### Build Instructions
1. Clone the repository:
   ```bash
   git clone https://gitlab.ecole.ensicaen.fr/toujani/epidemy-os.git
   cd epidemy-os
   ```
2. Build the project using the provided Makefile:
   ```bash
   make
   ```
3. Run the simulation:
   ```bash
   ./epidemic_sim
   ```

## File Structure
- **`src/`**: Contains the source code files.
- **`include/`**: Contains the header files.
- **`doc/`**: Includes the project report.
- **`Makefile`**: Automates the build process.

## Additional Information
Refer to the report in the `doc/` folder for a detailed explanation of the project design, challenges encountered, and solutions implemented.
