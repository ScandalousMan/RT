# RT
Ray Tracing group project for School 42

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
- 