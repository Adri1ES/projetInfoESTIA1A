##### École Supérieure des Technologies Industrielles avancées

# IT Project

##### Subject : Calculation of aircraft wing parameters

### Valentine G. ; Adrien G.

### 25/06/2019

## Abstract
This is the computer project of first year in ESTIA
Rules about this project can be found here: http://www.guillaumeriviere.name/estia/GI/reglement.php


## Table des matières

I. Conception de l'interface ................................................................................................................ 1

1) Explication des fonctionnalités proposées et de la finalité du logiciel ....................................... 1
2) Croquis de l'interface .................................................................................................................. 2
3) Organisation de l'interface : hiérarchie et placement des composants ..................................... 2

II. Manuel utilisateur ........................................................................................................................... 4

III. Métriques .................................................................................................................................... 7

IV. Explication de parties de code choisies ...................................................................................... 7

V. Bilan ................................................................................................................................................ 8

## I. Conception de l'interface

#### 1) Explication des fonctionnalités proposées et de la finalité du logiciel

Lorsqu’un constructeur souhaite concevoir une nouvelle aile ou qu’un amateur souhaite
connaitre les caractéristiques de sa voilure, il est nécessaire de réaliser quelques calculs à la main.
Pour automatiser ce processus, nous avons créé ce logiciel qui permet de calculer des
caractéristiques de profils à partir de valeurs entrées. Le logiciel permet aussi de visualiser à quoi
ressemblent certains profils. Il est supposé dans le logiciel que l’air est incompressible, c’est-à-dire
avec une masse volumique constante. Cela implique de travailler pour des valeurs inférieures à
Mach 0,3, valeur qui permettra de déterminer si le modèle proposé est cohérent ou non.

L'utilisateur peut choisir le type d'avion qu'il souhaite étudier et le type de résultat qu'il souhaite
obtenir. Pour cela, il doit choisir parmi les 3 boutons radio proposés pour choisir l'avion : modélisme,
ULM, avion de tourisme

Selon le type d'avion choisi, les valeurs changent. Le logiciel va lire les valeurs de la vitesse,
corde, flèche, épaisseur et surface correspondant au type d'avion dans un fichier, et initialiser les
spinbuttons en fonction.

Il devra également choisir parmi trois autres boutons radio pour choisir le résultat : soit « obtenir
profil d'aile », soit « obtenir caractéristiques d'aile », soit obtenir « toutes les données ». À chaque
fois qu'il changera les données, un bouton « rafraichir » lui permet d’actualiser les calculs.

S'il choisit « obtenir profil », il va devoir entrer des données et le logiciel va lui retourner l'image
du profil correspondante ainsi que certaines caractéristiques liées à ce type de profil. Des cases à
cocher lui permettent d'augmenter le nombre de données s'il veut connaitre la portance, la trainée,
le poids et la finesse.

S'il choisit « obtenir caractéristiques », il sélectionnera un type de profil avec la boîte combinée.
Les valeurs caractéristiques de ces types de profils seront affichées ainsi que la photo
correspondante.


S'il choisit « toutes les données », il peut obtenir les mêmes résultats décrit précédemment avec
les images obtenues avec « obtenir profil » et celle obtenu avec « obtenir caractéristiques » qui sont
liés donc change en même temps lorsque l'utilisateur change les données.

L'utilisateur peut enregistrer les données qu'il vient de calculer dans un fichier CSV.

Ce logiciel permet donc à l'utilisateur d'obtenir soit un profil d'aile selon des données
spécifiques, soit connaitre les caractéristiques propres à chaque type de profil et d'enregistrer le
résultat et cela pour 3 différents types d'avion proposé.

#### 2) Croquis de l'interface

```
Figure 1 Croquis de l'interface
```
#### 3) Organisation de l'interface : hiérarchie et placement des composants

Une fenêtre window1 rassemble tous les composants du logiciel.

Une table permet de partager la fenêtre en 2 colonnes avec dans la première le type d'avion
et dans la deuxième un VBox qui partage en 4 parties pour utiliser le radio button pour "Toutes les
données", des frames contenant des radio buttons pour «Obtenir profil d'aile» et «obtenir
caractéristiques d'aile» ainsi que la partie enregistrement des données.


```
Figure 2 Hiérarchie des composants
```
Dans le frame_avion, un Vbox partage l'espace en 3 catégories pour 3 radiobouton dédiée
aux types d'avion que l'utilisateur va choisir.

Dans le frame_profil, le radiobutton_profil permet d'activer ce frame qui est partagé en deux
autres frames pour une partie ou l'utilisateur va rentrer des données (frame_donnee), et une autre
partie ou l'utilisateur va observer le résultat (frame_resultat). Une 3ème partie est dédiée à
l'affichage du message d'erreur lorsque le modèle du profil proposé n'est pas cohérent
(frame_message)

Dans le frame_caracteristiques, le radiobutton_caracteristiques permet d'activer ce frame
qui est partagé en deux autres cadres une partie où l'utilisateur va rentrer le profil avec un
combobox (frame_type), et une autre partie ou l'utilisateur va observer le résultat (frame_carac).

Dans le frame_enregistrement, un bouton export_csv et un composant pour choisir un fichier
permet d'enregistrer les données.

```
Figure 3 Hiérarchie détaillés des composants
```
Dans le frame_donnee, un table permet de partager l'espace avec des labels, spinbuttons et
checkbuttons.


Dans le frame_resultat, deux autres frames sont nécessaires : l'un pour afficher le résultat
calculé (avec des labels) et un autre pour afficher l'image (resultat_image)

Des composant alignement ont également été utilisés pour optimiser la compréhension du logiciel.

Dans le frame_type, un combobox_profil (+ listestore1 avec le choix de 4 profils) et
image_profil ont été utilisés.

```
Dans le frame carac, seul des labels ont été utilisé.
```
## II. Manuel utilisateur

La première action que doit effectuer l'utilisateur est de choisir le type d'avion qu'il souhaite
étudier ainsi que le type de résultat qu'il souhaite obtenir donc choisir parmi les trois boutons radio
proposés pour ces deux parties. Les résultats sont affichés lorsque l'utilisateur appuie sur le bouton
Rafraichir.

```
Figure 4 Fenêtre d'accueil
```
Selon le type d'avion sélectionné, le logiciel va lire les valeurs dans un fichier "instructions"
et initialiser les spinbutton en fonction, ce qui permettra d'indiquer à l'utilisateur l'ordre de
grandeur de ces données.

Si l’option "Obtenir profil", il faudra entrer les valeurs de la vitesse, la longueur de corde, la
flèche, l’épaisseur et la surface alaire (pour une seule aile). Il faut ensuite appuyer sur le bouton
"Rafraichir" pour que le logiciel donne les valeurs de l'épaisseur relative, le nombre de Reynolds et la
cambrure ainsi que l'image du profil correspondant. Un message affichera si le modèle est correct
avec un message affiché « modèle cohérent » ou si les valeurs données en entrée sont aberrantes, le
message affiché sera « modèle incorrect, vitesse trop importante ».


Si l'utilisateur connaît les valeurs de la masse, du coefficient de portance Cz ou du coefficient
de trainée 1cx, il peut cocher les casses correspondantes, rentrer les valeurs dans la case et appuyer
sur rafraichir pour obtenir les valeurs de la portance, trainée, de la finesse et du poids.


S'il ne connaît pas les valeurs et ne coche pas les cases, un message sera affiché pour
prévenir que le Poids, trainée, portance ou finesse n'est pas calculé.

```
Figure 5 Masse, Cz et Cx non saisis
```
Si jamais l'utilisateur dépasse 0,3 Mach, le modèle de calcul du logiciel ne sera plus valide et renverra
un message d'erreur en rouge.

```
Figure 6 Message d'erreur possible si la vitesse est trop importante
```
Si l'utilisateur choisit « obtenir caractéristiques de l'aile », il faudra sélectionner un type de
profil avec la boite combinée (convexe, biconvexe, creux ou supercritique) et les intervalles de
valeurs caractéristiques de ces types de profils seront affichés ainsi que la photo correspondante.


```
Figure 7 Exemple de retour pour un profil caractéristique
```
Si l'utilisateur choisit « toutes les données », il obtiendra les mêmes résultats décrit
précédemment avec les images de « obtenir profil » et celle obtenu avec « obtenir caractéristiques »
qui sont liées. Donc elles changent en même temps lorsque les données en entrée seront changés
avec le bouton rafraichir ou avec la boite combinée.

```
Figure 8 Exemple de retour lorsque l'option tout les données est sélectionnée
```
Il est possible d'enregistrer les valeurs en choisissant en premier le dossier puis le nom de
fichier.csv puis appuyer sur le bouton "Exporter".

Si l'utilisateur choisit uniquement la partie « obtenir profil », le logiciel peut enregistrer les données
rentrée, les valeurs des différents calculs de 'Résultats' et le nom du profil (ex : supercritique)

Si l'utilisateur choisit uniquement la partie "obtenir caractéristiques", le logiciel peut enregistrer les
noms du profil choisi avec la boite combinée, puis les intervalles de valeurs caractéristiques.


## III. Métriques

|   | SLOC | %CLOC | %BLOC | Nombre de fonctions | Nombre de types structurés |
| --- | --- | --- | --- | --- | --- |
| callbacks.c | 614 | 6.3% | 18% | 18 | 0 |
| main.c | 22 | 19% | 28.6% | 2 | 0 |
| callbacks.h   | 11 | 0% | 33.3% | 0 | 0 |
| Tout les fichiers | 647 | 6.7% | 18.8% | 20 | 0 |

## IV. Explication de parties de code choisies

Nous avons eu des problèmes pour lire un fichier et initialiser les valeurs des spins buttons selon
les valeurs du fichier et selon le radiobutton choisi par l'utilisateur. Nous avons décidé d'écrire les
valeurs des différents types d'avion dans un seul fichier texte et de faire un fscanf pour lire les
données.

Nous avons également rencontré des difficultés pour activer les checkbutton et enregistrer les
données lorsque ces boutons etaient activés. Nous avons fait le choix d'écrire un message d'une
autre couleur lorsque les boutons n'étaient pas actifs.

Exemple de code :
```c
if ( gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (checkbutton_Cz)))
{

  valeur_portance = 0.5 *Surface*MasseVolAir*Vitesse*Vitesse*CoefP;
  sprintf ( valPort, "%.1f " , valeur_portance) ;

  gtk_label_set_text (portance, valPort) ;

  gtk_label_set_text (labelPortance,"Portance(N)") ;

}

else
{

  sprintf (valPort, " ") ;
  sprintf (couleurP, "<span foreground=\"#7378AD\"> Portance non calculee</span>");
  gtk_label_set_markup (GTK_LABEL(labelPortance), couleurP) ;

}
```
Nous avons également rencontré des difficultés pour changer des images et les faire coïncider
lorsque le radio bouton « toutes les données » est activé. Nous avons finalement retenu cette
solution. Nous avons mis un if pour tester si la valeur était la bonne pour afficher l’image.

Exemple:
```c
if (i==1)
{

  gtk_image_set_from_file (GTK_IMAGE(image_profil), "images/biconvexe.png");

  if ( gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (radiobutton_lesDeux)))
  {

  gtk_image_set_from_file (GTK_IMAGE(resultat_image), "images/biconvexe.png");
  }
}
````
## V. Bilan

Nous avons appris comment coder certains composants que nous n'avions jamais utilisé en
TP comme les checkbuttons par exemple, ou à remplacer une image à partir de certaines valeurs.

Nous avons dû gérer nos erreurs une à une pour s'assurer du bon fonctionnement du
logiciel. Nous avons appris qu'une simple virgule à la place d'un point pouvait fausser les résultats
retournés.

Nous nous sommes rendu compte qu'il est très important de bien commenter nos codes
pour être sûr que le partenaire de binôme le comprendra et de bien écrire les noms des fonctions
pour retrouver facilement et comprendre à quoi ils correspondent pour ne pas perdre de temps.

Nous avons eu des difficultés à comprendre quelles valeurs scientifiques nous devions
choisir pour faire afficher les images ou les messages d’erreur.

Le fichier Glade a évolué tout au long du projet puisque nous rajoutions des fonctionnalités
au fur et à mesure que nous validions les fonctions ajoutées.
