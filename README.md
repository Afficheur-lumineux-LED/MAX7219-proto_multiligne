# Proto_multiligne
Test d'affichage multi-ligne et multi-effet

Necessite les librairies :
* MD_Parola
* MD_MAX72xx.h

Premier prototype qui affiche un texte sur plusieurs lignes, avec des effet diférents.
* Ligne défilante sans arrêt.
* Ligne défilante avec arrêt au centre, puis disparition du texte vers le bas.
* Ligne centré qui apparait du bas, fait une pause, et disparait de nouveau en bas.
* Les deux lignes suivantes défilent de la gauche vers la droite, avec un arrêt de deux secondes au centre de l'afficheur.

La variable "temps_pause" (exprimée en milliseconde), défini le temps d'arrêt au centre de l'afficheur.
Pour déboguage, une sortie en console est prèvue afin de suivre le déroulement du programme.

Piloté par un Arduino UNO, le code utilise 21414 octets, soit 66% de l'espace de stockage de programmes, et 689 octets, soit 33% de mémoire dynamique.

# Vidéo démonstration
https://www.youtube.com/watch?v=78se71uhlqY
