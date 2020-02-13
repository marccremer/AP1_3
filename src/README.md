# Praktikum 3
**Marc Cremer 2019**

## prakt3_1.c
Nimmt einen String und fragt dann ob man nach einem Char in dem String suchen möchte.
Gibt bei 'j' die Häufigkeit des Char's aus.

## prakt3_2.c
Das Programm prakt3_1.c aufgesplittet in Haupt- und Nebendatein mit header Dateien.
Die funktion ist identisch nur wird mit der makefile *mymake.mak* compiliert

## prakt3_3.c
Ein Lagerverwaltungsprogramm ,dass Artikel mit ID,NAMEN und ANZAHL speichert.
Man kann:
* Das Lager als Tabelle ausgeben
* Artikel hinzufügen
* Artikel um ANZAHL veringern
* Artikel suchen nach NAMEN oder ID

Das Lager wird byte-weise in *lager.bin* gespeichert und die Anzahl an verschieden Artikeln in *lagereigenschaften.txt*
Wenn man die zahl in *lagereigenschaften.txt* auf 0 setzt löscht man damit effictive das Lager