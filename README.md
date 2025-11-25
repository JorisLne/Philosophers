<p align="center">
  <img 
    src="https://github.com/JorisLne/42-project-badges/blob/main/covers/cover-philosophers-bonus.png?raw=true" 
    alt="Bannière philo" 
    width="80%">
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Score-125%2F100-brightgreen?style=flat-square" alt="Score du projet 125/100" />
  <img src="https://img.shields.io/badge/Langage-C-blue.svg?style=flat-square&logo=c" alt="Langage C" />
</p>

<p align="center">
  <img src="https://github.com/JorisLne/42-project-badges/blob/main/badges/philosophersm.png?raw=true" alt="Badge philo">
</p>


# 🧠 Philosophers

Ce projet illustre le **problème des philosophes**, à travers la gestion de la concurrence et des ressources partagées entre threads en C.

---

## 📚 Table des matières

- [Introduction](#introduction)
- [Schéma du problème](#schéma-du-problème)
- [Démonstration animée (GIF)](#démonstration-animée-gif)
- [Fonctionnalités](#fonctionnalités)
- [Installation](#installation)
- [Utilisation](#utilisation)
- [Exemples de commande](#exemples-de-commande)
- [Dépendances](#dépendances)
- [Structure du projet](#structure-du-projet)
- [Bonus](#bonus)
- [Améliorations possibles](#améliorations-possibles)
- [Licence](#licence)

---

## 🧩 Introduction

Ce problème modélise plusieurs philosophes autour d'une table, alternant entre **penser**, **manger** et **dormir**. Chacun a besoin de deux fourchettes pour manger, mais les fourchettes sont partagées. Cela soulève des problématiques de **concurrence**, **d'accès synchronisé aux ressources** et **de prévention de famine et d'interblocages (deadlocks)**.

Le but est de créer une simulation fiable et performante qui respecte ces contraintes.

Chaque philosophe :
1. Prend deux fourchettes
2. Mange pendant un certain temps
3. Repose les fourchettes
4. Dort
5. Pense
6. Recommence
---

## ✨ Features

- Création de threads pour chaque philosophe
- Synchronisation avec **mutex** (version classique)
- Utilisation de **sémaphores** (version bonus)
- Contrôle de la durée de vie des philosophes
- Détection de la mort d’un philosophe
- Gestion de la fin de simulation

---

## 💾 Installation

### Pré-requis
- GCC ou Clang
- `make`

### Compilation

Version classique :
```bash
cd philosophers/philo
make
```

Version bonus :
```bash
cd philosophers/philo_bonus
make
```

---

## 🚀 Utilisation

Chaque version se lance avec les arguments suivants :

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers` : nombre de philosophes
- `time_to_die` : temps en ms avant qu’un philosophe meure s’il ne mange pas
- `time_to_eat` : durée du repas
- `time_to_sleep` : durée de sommeil
- `number_of_times_each_philosopher_must_eat` *(optionnel)* : termine la simulation après que chaque philosophe a mangé ce nombre de fois

---

## 🧪 Exemples de commande

```bash
# 5 philosophes, meurent après 800ms sans manger
./philo 5 800 200 200

# 4 philosophes, arrêt après que chacun ait mangé 3 fois
./philo 4 410 200 200 3
```

---

## 📦 Dépendances

Aucune dépendance externe. Le projet repose uniquement sur les bibliothèques standards C :

- `<pthread.h>`
- `<unistd.h>`
- `<stdlib.h>`
- `<stdio.h>`
- `<sys/time.h>`

---

## 🗂️ Structure du projet

```bash
philosophers/
├── philo/             # Version classique (mutex)
│   ├── Makefile
│   ├── includes/
│   └── sources/
├── philo_bonus/       # Version bonus (sémaphores)
│   ├── Makefile
│   ├── includes/
│   └── sources/
```

---

## 🧨 Bonus

La version bonus (`philo_bonus/`) remplace les mutex par des **sémaphores** :

- `sem_open`, `sem_wait`, `sem_post`
- Meilleure gestion inter-processus
- Simulation plus réaliste dans un environnement multi-processus

---

## 💡 Améliorations possibles

- Interface graphique ou en terminal (avec `ncurses`)
- Visualisation en temps réel des actions
- Génération de logs ou animations GIF
- Ajout d’un mode **slow motion** pour observer la concurrence
