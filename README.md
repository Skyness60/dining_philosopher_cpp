# Dining Philosophers (EN — default)

Small C++ implementation of the Dining Philosophers problem to practice multi-threading and the resource-hierarchy pattern (global ordering on forks). Français plus bas.

Language: English (default) | [Français](#philosophes-d%C3%AEneurs-fr)

## What’s inside
- `src/` sources (`Dining` app wrapper, `Philosopher` logic, `main.cc`)
- `include/` headers
- `Makefile` with `make`, `make run`

## Quick start
```bash
make        # build bin/philo
./bin/philo <philosophers> <think_ms> <eat_ms> <sleep_ms> [meals_per_philo]
```
- `meals_per_philo` is optional; when omitted the simulation runs indefinitely.
- Example: `./bin/philo 5 100 120 150 3`

## Threads and the problem
- A thread is a lightweight execution unit sharing memory with other threads; here each philosopher runs in its own thread started by the main program.
- Dining Philosophers: philosophers alternate thinking/eating and must pick up two shared forks; naive locking can deadlock if everyone grabs one fork.

## Pattern used: resource hierarchy
- Design pattern: a reusable solution template for a recurring problem.
- Resource hierarchy: impose a total order on resources and always lock in that order to avoid cycles.
- Here, forks are ordered by their index; each philosopher locks the lower-index fork first, then the higher one. This breaks circular wait and prevents deadlocks.

## Diagrams (fork ordering)
Layout (5 philosophers / 5 forks):
```
      F0          F1
   P0    \\      /    P1
    \\     \\    /     /
     \\     \\  /     /
      F4--- P4 ---F2
       /     /\\     \\
      /     /  \\     \\
    P3    /      \\    P2
      F3          F2
```
Lock order (example P3 with F3 and F4):
```
1) min(F3, F4) = F3 -> lock F3
2) max(F3, F4) = F4 -> lock F4
```
Each philosopher follows the same rule: always lock the lower-index fork first, then the higher one.

## Behavior knobs
- `philosophers`: number of philosophers/forks (>=1)
- `think_ms`, `eat_ms`, `sleep_ms`: durations in milliseconds (>=1)
- `meals_per_philo`: optional positive integer; when set, each philosopher stops after this many meals.

## Future ideas
- Add clean shutdown (signal/flag).
- Implement starvation mitigation (e.g., limit concurrent eaters).
- Add logging/metrics and tests around timing and mutual exclusion.

---

# Philosophes Dîneurs (FR)

Petite implémentation C++ du problème des philosophes dîneurs pour s’entraîner aux threads et au pattern de hiérarchie de ressources (ordre global sur les fourchettes). Section anglaise au-dessus.

Langue : Français | [English](#dining-philosophers-en--default)

## Contenu
- `src/` code source (`Dining`, `Philosopher`, `main.cc`)
- `include/` headers
- `Makefile` avec `make`, `make run`

## Démarrage rapide
```bash
make        # construit bin/philo
./bin/philo <philosophes> <penser_ms> <manger_ms> <dormir_ms> [repas_par_philo]
```
- `repas_par_philo` est optionnel ; s’il est omis, la simulation tourne sans limite.
- Exemple : `./bin/philo 5 100 120 150 3`

## Threads et problème
- Un thread est une unité d’exécution légère qui partage la mémoire du processus ; ici chaque philosophe s’exécute dans son propre thread lancé et rejoint depuis le programme principal.
- Philosophes dîneurs : les philosophes alternent pensée/repas et doivent prendre deux fourchettes partagées ; un verrouillage naïf peut mener au deadlock si chacun garde une fourchette.

## Pattern utilisé : hiérarchie de ressources
- Un design pattern est un schéma de solution réutilisable pour un problème récurrent.
- Hiérarchie de ressources : imposer un ordre total sur les ressources et toujours les verrouiller dans cet ordre pour casser les cycles.
- Ici, les fourchettes sont ordonnées par leur index ; chaque philosophe verrouille d’abord la fourchette au plus petit index, puis la seconde, supprimant ainsi l’attente circulaire et le deadlock.

## Diagrammes (ordre des fourchettes)
Disposition (5 philosophes / 5 fourchettes) :
```
      F0          F1
   P0    \\      /    P1
    \\     \\    /     /
     \\     \\  /     /
      F4--- P4 ---F2
       /     /\\     \\
      /     /  \\     \\
    P3    /      \\    P2
      F3          F2
```
Ordre de prise (exemple P3 avec F3 et F4) :
```
1) min(F3, F4) = F3 -> verrouiller F3
2) max(F3, F4) = F4 -> verrouiller F4
```
Chaque philosophe suit ce schéma : toujours verrouiller la fourchette à l’index le plus bas, puis la plus haute.

## Paramètres
- `philosophes` : nombre de philosophes/fourchettes (>=1)
- `penser_ms`, `manger_ms`, `dormir_ms` : durées en millisecondes (>=1)
- `repas_par_philo` : entier positif optionnel ; quand défini, chaque philosophe s’arrête après ce nombre de repas.

## Pistes futures
- Ajouter un arrêt propre (signal/flag).
- Réduire la famine éventuelle (par ex. limiter le nombre de mangeurs simultanés).
- Ajouter du logging/des métriques et des tests sur le timing et l’exclusion mutuelle.
