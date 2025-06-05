# S2 | Programmation & Synthèse d'image : IMAC Digger
> Par Guillaume Boucher, Nina Goislot et Paul Marchiset ☕︎☕︎☕︎

Bienvenue sur notre readme de notre jeu vidéo Phantom !


## Instructions

- Lancez le jeu avec le compilateur GCC
- Lancer le jeu depuis "dossier parent > bin/debug" dans le terminal

## Contrôles 

Phantom peut se joueur soit avec les flèches directionnelles <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> : pas de déplacement en diagonal possible. Utilisez <kbd>Z</kbd><kbd>Q</kbd><kbd>S</kbd><kbd>D</kbd> pour explorer le jeu plus rapidement, comme un mode debug (attention le méchant ne poursuit pas le joueur avec ce type de déplacement)


Pour miner les blocs, la touche est <kbd>A</kbd>.

Pour récupérer un item, c'est la touche <kbd>E</kbd>.

## Coup d'oeil sur le lore

Phantom est un jeu où nous incarnons une petite flamme partant dans une quête risquée. Un vieux sage à la tête triangle lui annonce qu’il a perdu sa vieille canne magique dans la cave du méchant vivant dans le grand manoir de la colline. Celle ci s'st cassée en plusieurs morceaux la dernière fois qu'il s'y ai aventuré et il aimerait la récupérer.

Le joueur se lance donc la recherche des morceaux perdus pour reconstruire la canne de M. PépéNG tout en se faisant pourchasser par l'hôte du manoir et plusieurs fantômes semblant hanter les lieux.

A la fin de son épopée la flamme toute contente part restituer les bouts de canne au vieux sage qui se révèle être un démon qui avait besoin de collecter les 5 morceaux de bâton magique pour conquérir le monde. Ne jamais se fier aux apparences. 


## Fonctionnalités

### Gestion des collisions

Notre joueur ne peut naturellement pas passer au travers des murs. Nous prenons les coordonnées du joueur et nous ne permettons le déplacement que si le futur bloc est une tuile de sol. Même si les detections de collisions sont censés fonctionner, nous avons implémenté une fonction de softlock qui redirige le joueur vers le haut si il se retrouvait coincé. 

### Minage

Notre joueur ne peut creuser que si les cases en face de lui sont des murs. Il peut le faire à l'aide de la touche <kbd>A</kbd>. 

### Items

Pour pouvoir gagner le jeu il est nécessaire de récupérer 5 items, qui sont des morceaux de cannes. Ces items sont placés de manière aléatoire sur les cases libres de la carte. Au bout du cinquième morceau de canne, le joueur "gagne" et est conduit à la scène de victoire. 

## Architecture 
### Organisation des fichiers

Le projet est décomposé en 5 parties de code : 

**1 - Les managers**

    Regroupent les fichiers en charge de toute une partie du code. Un gestionnaire de scene, du jeu, des textures, ect. 

**2 - Characters / Entities**

    Les entités du jeu, aussi bien le player que les ennemis. 

**3 - Controls**

    Les gestionnaires des touches. 

**4 - Map**

    Les fichiers en lien avec le chargement de la map. 

**5 - Scenes**

    Les différentes scenes appelées au cours du jeu.

### Structure POO

Le projet est conçu en programmation orienté objet principalement. Dans le cas des scènes et des ennemies, entités multiples, il existe une classe mère qui permet aux fichiers enfants d'hériter des charactéristiques communes et de les gérer plus facilement dans les managers.
## Génération de carte 

### Cases incassables

<<<<<<< HEAD
Les cases incassables sont générés aléatoirement et sont placées sur la carte sur les cases libres. Représentés par des rochers, ils suivent le même système de collision que pour les murs, cependant ils ne peuvent être creusés.
=======
Les cases incassables sont générées aléatoirement et sont placés sur la carte sur les cases libres. Les rochers suivent les même système de collision que pour les murs, cependant ils ne peuvent être creusés.
>>>>>>> 35c415a48313ccd4f53e8f1505db5ee132bc7f4c

### Pièges

Comme les roches et les items, les pièges sont placés de manière aléatoire sur les cases libres. Si le joueur entre en collision avec ceux-ci, il perd de la vie.

## Flow Field 

## Texturing 

Pour gérer le texturing de tous nos éléments nous avons créé un tileset qui regroupe tous les éléments de la carte. Nous avons également d'autres stylesheet pour le joueur et les ennemis.

| Texture atlas de la carte  |
| :---------------: |
| ![L'image de base'](./assets/images/Map.png) | 

## IHM 

Notre jeu vidéo possède un écran d'accueil ainsi qu'un écran de victoire ou de perte du jeu. Durant la phase de jeu, le joueur peut consulter le nombre de vies qu'il possède encore ainsi que le nombre d'objets qu'il doit encore obtenir.

## Améliorations 

### Vies

Notre joueur possède plusieurs vies, au nombre de 3, si le joueur tombe dans un piège il perd une vie, s'il perd toutes ses vies, le joueur a perdu et est conduit à la scène de fin du jeu. Après une perte d'une vie, le joueur possède un temps d'invincibilité avant le prochain coup de dégât.

### Autotiling

Pour obtenir un autotiling autour des murs de la map, nous avons utilisé une fonction de bitmasking qui permet de stocker si les voisins de la tuile en question sont en vie ou non, respectivement si le north, west,east et south sont vivants ou non. Avec ceci nous appliquons un changement d'uv pour chaque cas sur la même texture pour détourer les murs. En ce qui concerne les améliorations possibles, nous avons remarqué que l'autotiling pouvait provoquer une chute des performances, il serait bon de passer plus de temps là dessus pour optimiser l'ensemble. Une autre amélioration pourrait être le fait d'ajouter de l'aléatoire pour que l'on reconnaisse moins de motif au sol notamment. 

### Animation

Notre joueur possède également une petite animation à l'aide d'un spritesheet avec une animation pour chaque direction. Pour réaliser cela, nous avons implémenté une petite fonction qui permet de mettre à jour les UVs d'une texture pour passer d'une frame à une autre. Une petite amélioration serait de garder la direction précédente du joueur en mémoire pour que s'il s'arrête d'avancer, la première frame du cycle soit sélectionnée. Nous pourrions également ajouter une animation d'idle.

| SpriteSheet du player  |
| :---------------: |
| ![SpriteSheet du player](./assets/images/Player.png) | 

| SpriteSheet du villain  |
| :---------------: |
| ![SpriteSheet du villain](./assets/images/villain.png) |

## Améliorations abandonnées 

### Tuiles aléatoires

Une autre amélioration envisagée a été celle de la génération aléatoire de tuiles de sol. Cependant comme nous avions prévu de stocker un id aléatoire pour chaque tuile de la carte que nous utilisons pour définir la tuile de sol à affecter. Le problème étant que dans ce cas nous vérifions l'id de chaque tuile dans une carte de 100x100 et donc de 10000 vérifications au minimum. L'execution du programme était donc très ralenti. Nous avons pas trouvé de solutions dans les temps donnés, nous avons donc préféré enlever cette fonctionnalité.Si vous voulez y jeter un oeil, elle est toujours présente (dans drawGame.cpp, ligne 88) mais mis en commentaire pour profiter des meilleures performances du jeu.

| Tuile aléatoire  |
| :---------------: |
| ![L'image de base'](./assets/images/screenshots/screen1.png) |

### Éléments sonores

Nous avions commencé à regarder l'implémentation de son au sein du code (visible au dans la branche "sounds"). Faute de temps, cette implémentation à été mise de coté et n'a pas été reprise.  

### Ennemis multiples

Nous avions prévus 5 types d'ennemis au total. Chacun étant des fantomes (famille défunte du méchant qui protège les lieux) avait un nom commencant par un 'P'. Chaque méchant avait un comportement différent (l'un se repère aux sons, l'autre à la vue, l'un ne peut pas passer les murs, ect). Nous avions même commencés les sprites. Avec une journée supplémentaire, ces petits fantômes auraient pu voir le jour. 

### Tuto

En lien avec notre lore, nous voulions mettre au point une petite scene de tutoriel qui se déroulerait au sein même du manoir du faux méchant, le jeu principal se déroulant dans sa cave. Ce tuto introduisait le comportement des différents fantômes. c'est dans ce petit tuto qu'on recevait la quête de PépéNG. 

## Difficultés 

En ce qui concerne les difficultés il y en a eu un certain nombre en effet . Les principales se sont concentrées autour de l'architecture du code, de la gestion des textures et de la fiabilité du programme.

### Architecture de code

Nous voulions un code le plus clean possible, avec une architecture qui se rapproche des véritables jeux standards. Cela à pris un peu de temps au début, mais nous avons évitons un grand nombre de conflits au sein de nos avancées respectives grâce à ça !

Il a été notamment très difficile de faire apparaître des textures sur les différents meshes au départ et une bonne partie du déboguage a été porté là dessus. Particulièrement en ce qui concerne les UVs et le découpage des tilesets. L'aide du renderDoc ainsi que de nos professeurs a été particulièrement utile.

### Problème de compilateur

Un problème assez étrange qui s'est produit également est le fait que pendant un certain temps il a été impossible de charger une texture avec stbi_load, en effet avec le compilateur Clang cette fonction nécessaire pour afficher des textures faisait planter l'application. Après un certain temps de déboguage nous avons réalisé qu'en changeant de compilateur pour GCC par exemple tout fonctionnait comme prévu.

### Problème OpenGl

Nous avions difficilement la main mise sur la structure derrière l'implémentation d'openGL. En conséquence, nous nous sommes retrouvés avec de nooooombreux conflits sur la faisabilité de certaines actions ou sur le manque de compatibilité entre la template et les objectifs du code. Encore maintenant, il faut parfois relancer plusieurs fois le jeu au début car une exeption inconnue (et non visible) provoque un crash. 

## Notes de fin  

> Tous les éléments graphiques utilisés dans ce projet ont été soit réalisés par nos soins ou sont libres de droit. Notez la qualité de nos sprites fait main :)