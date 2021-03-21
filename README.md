# Mein erstes C Projekt
Dieses Projekt erstellte ich im Rahmen meines Studiums im ersten Semester. Es handelt sich um mein erstes größeres Programmierprojekt.

## Zum Testen
1. Dateien herunterladen
2. pure-c-chess.exe ausführen

## Belegaufgabe - Schach
Schreiben Sie ein Programm, mit dessen Hilfe der Nutzer Spielzustände aus
Textdateien laden, anzeigen, spielen und wieder in eine Datei schreiben
kann. Hierzu ist eine geeignete Benutzerführung zu entwerfen und zu
implementieren.  
"Spielen" bedeutet hier, dass gültige Züge eingegeben werden können, die
(auf Gültigkeit) geprüft und dann angezeigt werden. Welche Züge gültig
sind, ist auf https://de.wikipedia.org/wiki/Schach#Spielregeln beschrieben
und lässt sich leicht testen, wenn Sie eine entsprechende Datenstruktur
(z.B. char schachbrett[8][8]) mit dem aktuellen Spielstand anlegen. Die
Spielzüge "Rochade" und "en passant"-Schlagen müssen nicht implementiert
werden.  
Schreiben Sie ein Programm, mit dessen Hilfe der Nutzer Spielzustände aus
Textdateien laden, anzeigen, editieren und wieder in eine Datei schreiben
kann. Hierzu ist eine geeignete Benutzerführung (mit DAU-sicheren Menüs) zu
entwerfen und zu implementieren. Die Eingabe eines Spielzuges erfolgt über
die Tastatur mit 4 Zeichen. So bedeutet z.B. "c1a3" einen Zug der Figur auf
dem Feld c1 zum Feld a3.  
Die Darstellung/Ausgabe (Visualisierung) erfolgt sehr einfach auf der
Konsole, zum Beispiel:
![c3](https://user-images.githubusercontent.com/56033013/111895777-19661980-8a15-11eb-8b61-2d1762e3a278.PNG)

Zum Unterscheiden von schwarzen und weißen Figuren gibt es mehrere
Möglichkeiten:
- Anhängen eines Punktes an das Zeichen der schwarzen
Spielfiguren (siehe oben).
- Großbuchstaben für schwarz und Kleinbuchstaben für weiß.
- ...

## Screenshots
### Benutzerführung:
![c1](https://user-images.githubusercontent.com/56033013/111895782-208d2780-8a15-11eb-934b-8a15b7066a0a.PNG)  
### Spiel:
![c2](https://user-images.githubusercontent.com/56033013/111895785-22ef8180-8a15-11eb-869c-e6629614281f.PNG)
