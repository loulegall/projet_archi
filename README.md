Fait par : Lou Le Gall
Classe : IMR1

 CONTENU DU FICHIER
 ------------------

    * Introduction
    * Élément nécessaires
    * Utilisation
    * Description des modules
    * Information
    * Bug référencé

 INTRODUCTION
 ------------
    Le programme associé permet de controler des elements tel que des leds ou encore un ecran LCD sur un microcontrôleur Open1768.

 ELEMENTS NECESSAIRES
 --------------------

    Pour réaliser le projet il faut ce munir d'un carte un microcontrôleur Open1768. Sur cette carte nous allons utiliser:
    * Des leds
    * Un écran LCD
    * Une mémoire i2c

    Les autres elements nesessaires au bon fonctionnement de ce projet:
    * Un cable d'allimentation pour la carte Open1768
    * Un cable permettant de faire la liaison entre l'ordinateur (le code) et la carte
    * Le logiciel Micro Vision (version 5.36.0)


UTILISATION
------------

    Lancer un projet:
    1- Ouvrir le dossier contenant le projet uVision
    2- Arrivé sur le logiciel on retrouve:
        * Un exploreur (a gauche) avec tous les fichiers du projet
        * Une page principal ou on peut ouvir les dossier et les éditer
    3- Quand le code est écrit il faut "build" le projet
    4- Lancer le debuger 
    5- Run le projet pour qu'il puissent l'executer sur la carte ou en mode simulation sans carte

    Changer de mode de simulation:
        Avant de passer en mode debugage il faut 
        1- Appuyer sur la "baguette magique"
        2- Onglet "Debug"
            * Pour simuler sur le logiciel cocher "Use Similator"
            * Pour lancer sur la carte cocher "Use"

    Quand l'application est lancer il est possible d'utiliser l'écran LCD:
        Le principe est simple. Quand l'ecran est touche, un compteur va commencer et compter le nombre de touches qui on été realise.
        Il est possible de toucher sur l'intégralité de l'écran pour que le compteur s'incrémente. 
        L'ecran permet aussi d'afficher. Des carrees de couleurs qui changent en fonction du touche de l'ecran. Et affiche aussi les chaines de caracteres et le nombre de touches realise. 

    Le module mémoire I2C permet de stocker le nombre de  touches fait sur l'ecran, tous les 10 touches.
    Ainsi on peut afficher ce qui est stocke dans la memoire sur l'ecran. 

    Pour réinisialiser il est possible d'appuyer sur le bouton "RESET"

 DESCRIPTION DES MODULES
 -----------------------
module = fichier.c + fichier.h

    * Main: Le main est le module principal du projet. 

    * Timer: Le module timer permet:
        * Initialiser le Timer 0
        * Initialiser le Handler qui va faires des actions à chaque intéruption

    * LCD : Ce module permet l'affichages d'élement différents si on touche l'ecran ou non
        * Affiche deux carres 
        * Affiche une chaine de caractere entre les deux carres

    * Mémoire I2C : Ce module permet de lire et d'ecrire dans la memoire I2C, dialogue avec la memoire. 

    * globaldec: est appele que dans le main et stocke toutes les variables globales

    * global : stocke toutes les variables globales qui peuvent être appele dans les autres fichiers du projet. 


 INFORMATIONS
-------------
    * Le LPC1768 possède 3 périphériques I2C. Nous utiliserons le I2C0
    * Un timer sert de base de temps pour générer une interruption toutes les 10 ms avec une
précision de 500 us

 BUG REFERENCE
 -------------

 Le probleme que l'on peut relever est du à la carte car il y avait une led sur ma carte qui ne marchais pas. 



