# Jeu de Tétris
<img width="1353" height="679" alt="image" src="https://github.com/user-attachments/assets/b3f47e31-7a2c-41fd-a092-af343eb3aad6" />


Ce projet est une implémentation en langage C d'un jeu de Tétris utilisant un Makefile pour la gestion de la compilation.

---

## *FR* Documentation du Projet (English below)

### À Propos du Projet

Ce projet est une implémentation en langage **C** d'un jeu de Tétris gérée par un **Makefile**. Son objectif principal est de lancer depuis le terminal un jeu de Tétris revisité.

### Prérequis

Pour compiler et exécuter ce projet, vous devez disposer des outils suivants :

* **GNU Compiler Collection (GCC)** : Le compilateur C.
* **GNU Make** : Pour l'automatisation de la compilation.
* **Toute bibliothèque spécifique** (si nécessaire, ex: ncurses, math.h, etc.)

###  Compilation et Exécution

Toutes les commandes s'exécutent depuis le répertoire racine du projet.

1.  **Compiler le projet :**
    La commande `make` utilise le `Makefile` pour compiler l'exécutable principal.

    ```bash
    make
    ```
    *Ceci génère l'exécutable principal dans le dossier `bin/` (`bin/tetris`).*

2.  **Exécuter le programme :**
    Lancez l'exécutable principal :

    ```bash
    ./bin/tetris
    ```

3.  **Nettoyage des fichiers objets :**
    Pour supprimer tous les fichiers intermédiaires (`.o`) et l'exécutable, utilisez la cible `clean` :

    ```bash
    make clean
    ```

### Structure du Répertoire

| Dossier | Contenu |
| :--- | :--- |
| `src/` | Fichiers sources en C (`.c`). |
| `include/` | Fichiers d'en-tête (`.h`) pour les déclarations de fonctions. |
| `obj/` | Fichiers objets intermédiaires (`.o`) générés par la compilation. |
| `bin/` | Exécutable final. |
| `test/` | Fichiers sources des tests. |
| `makefile` | Fichier d'automatisation de la compilation. |

---

## *ENG* Project Documentation 

### About the Project

This project is a **C language** implementation managed by a **Makefile**. Its main objective is to play from the terminal to a revisited Tetris game.

### Prerequisites

To compile and run this project, you need the following tools:

* **GNU Compiler Collection (GCC)**: The C compiler.
* **GNU Make**: For build automation.
* **Any specific libraries** (if needed, e.g., ncurses, math.h, etc.)

###  Compilation and Execution

All commands are executed from the project's root directory.

1.  **Compile the project:**
    The `make` command uses the `Makefile` to compile the main executable.

    ```bash
    make
    ```
    *This generates the main executable in the `bin/` folder (Example: `bin/tetris`).*

2.  **Run the program:**
    Execute the main program:

    ```bash
    ./bin/tetris
    ```

3.  **Clean up object files:**
    To remove all intermediate (`.o`) files and the executable, use the `clean` target:

    ```bash
    make clean
    ```
