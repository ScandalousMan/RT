https://travis-ci.org/ScandalousMan/RT.svg?branch=master
# RT
Ray Tracing group project for School 42

## Requirements
Install `pkg-config`, `glew`, `sdl2` and `sdl2_images`

## How-to

### Compile

```
$ make
```

### Recompile and run

```
$ make run
```

### Check norm

You need to be at 42
```
$ make norm
```

### Clean

```
$ make clean
```

# Others

Projet Github => cf ToDo Liste

Pour ajouter une nouvelle forme géométrique :
- ajouter sa structure dans `rt.h`
- créer son ficher `forme.c`, y ajouter les fonctions :
```c
int         rt_forme_parser(t_param *param, t_parse *config);
t_object    *add_forme(t_param *param, autres paramètres...);
double      distance_to_forme(t_object *tmp, double *from, double *to);
void        update_normal_forme(t_object *tmp, t_path *path);
```
- ajouter la forme avec son numéro dans l'aiguillage `rt_object_parser`

# GUI

## interface standard

Interface composée de 2 zones :
* valeurs générales la scène
* Onglet lights et onglet objects

### Valeurs générales de la scène

les valeurs param ci-dessous sont initialisées aux valeurs des MACROs (pas encore déclaré ou fait)

Bouton pour :
-> rafraichir la scène et revenir aux valeurs initiales du parser

Input select pour :
-> appliquer un filtre (none (par défaut) / cartoon / greyscale / sepia / blur)
-> sélectionner la scène initiale à parser (liste de fichiers contenus dans un répertoire spécifique)

### onglet lights

Input select pour sélectionner une lumière parmi toutes celles de la scène
Bouton + pour ajouter une lumière
Bouton _ pour supprimer une lumière

Au clic sur une option du select,
afficher les données de la lumière et permettre leur modification (cf structure t_light)

### onglet objects

Input select pour sélectionner un objet parmi tous ceux de la scène
Bouton + pour ajouter un objet
Bouton - pour supprimer un objet

Au clic sur une option du select (ou sur un pixel de l'image)
afficher les données de l'objet sélectionné et permettre leur modification (cf structure t_object)

### divers

Pour les boutons, commencer par générer un mprintf(1, "event") à l'event clic et ensuite on cablera