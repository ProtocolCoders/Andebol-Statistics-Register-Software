# Handball Statistics Register Software

This project is a console-based application developed in C for managing and registering statistical data of handball teams and players. It was created as the final project for the "Introduction to Programming" course at the School of Technology and Management of Viseu (ESTGV), Polytechnic Institute of Viseu.

The software provides a comprehensive set of tools for handling championship data, including dynamic registration of teams and athletes, calculation of performance metrics, and persistent storage.

## Features

The application implements a wide range of functionalities, including:

- **Team and Player Management**:
  - Register new teams and add up to 15 players per team.
  - Update player information individually.
  - Remove specific players or entire teams.
- **Statistical Calculations**:
  - Automatically calculates a player's "value" (`valia`) based on their position and performance statistics (points, assists, etc.). Goalkeepers have a default value of zero.
  - Aggregates player values to determine the total value of a team.
- **Data Querying and Sorting**:
  - List all players in a team, sorted alphabetically by name or by their calculated value (ascending/descending).
  - Search for players based on specific criteria, such as value (greater/less than a specified amount) or birth year (exact, before, or after a specified year).
- **Advanced Insights**:
  - Identify the most and least valuable teams in the championship.
  - Find the most valuable player for each position (winger, lateral, center, pivot, goalkeeper), considering only players with more than 100 minutes played.
- **Data Persistence**:
  - Automatically loads championship data from `data/equipas.txt` on startup.
  - Automatically saves any changes (additions, updates, deletions) back to the file, ensuring no data is lost between sessions.
- **Dynamic Memory Management**:
  - Uses dynamic memory allocation (`malloc`, `realloc`, `free`) to efficiently manage data without predefined limits on the number of teams.

## Project Structure

The project is organized in a modular structure to ensure clarity, maintainability, and code reuse:

- **`/include`**: Contains the main header file `andebol.h`, which defines the core data structures (`Atleta`, `Equipa`, `Campeonato`), constants, and function prototypes.
- **`/src`**: Contains the source code, divided into functional modules:
  - `main.c`: The entry point of the application. Initializes the system and starts the main menu.
  - `core.c`: Implements the central data management logic, including adding, removing, and updating teams and players, as well as memory management.
  - `io.c`: Handles all input/output operations, including the user menu interface and reading from/writing to the data file.
  - `stats.c`: Contains all functions related to statistical calculations, sorting, and advanced data searching.
- **`/data`**: Stores the application's data.
  - `equipas.txt`: The database file where all championship, team, and player information is persisted.
  - `Estrutura-dados-equipa.txt`: A file describing the format of the `equipas.txt` data file.
- **`/docs`**: Contains project documentation, including the official report (in Portuguese).
- **`Makefile`**: A cross-platform Makefile for compiling and running the project on Windows, Linux, and macOS.

## Getting Started

Follow these instructions to compile and run the project on your local machine.

### Prerequisites

- **GCC Compiler**: You must have `gcc` installed. On Windows, you can use [MinGW](https://www.mingw-w64.org/).
- **Make**: You must have `make` installed. It is typically included with build tools on Linux/macOS and comes with MinGW on Windows.

### Compilation

1.  Clone the repository to your local machine.
2.  Open a terminal or command prompt in the root directory of the project.
3.  Run the following command to compile the source code:

    ```sh
    make
    ```

    This will create an `obj/` directory for intermediate object files and a `bin/` directory containing the final executable (`andebol.exe` on Windows, `andebol` on Linux/macOS).

### Running the Application

To run the program, use the following command from the root directory:

```sh
make run
```

This will launch the application in a new terminal window. The program will automatically load data from `data/equipas.txt`.

Alternatively, you can run the executable directly from the `bin/` directory.

### Cleaning Up

To remove all compiled files and generated directories (`bin/` and `obj/`), run:

```sh
make clean
```

## Data File Format

All data is stored in `data/equipas.txt` using a pipe-delimited (`|`) format.

- **Championship**: `CAMPEONATO|<name>|<year>|<num_teams>|<team_capacity>`
- **Team**: `EQUIPA|<name>|<num_players>`
- **Player**: `ATLETA|<id>|<name>|<birth_year>|<position>|<avg_points>|<avg_shots>|<avg_turnovers>|<avg_assists>|<avg_feints>|<minutes_played>|<value>`

Player positions are abbreviated as follows:
- `pon`: Winger (Ponta)
- `lat`: Lateral (Lateral)
- `cen`: Center (Central)
- `piv`: Pivot (Pivô)
- `gua`: Goalkeeper (Guarda-redes)

## Authors

- **Marcos Marcelo Assis Nunes**
- **Pedro Miguel Gomes**
- **Raquel Vaz Guerreiro**
- **Bernardo Miguel Vieira**

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.