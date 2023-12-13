# PEA zadanie projektowe 1

W folderze src znajduja sie pliki zrodlowe programu

W folderze outputFiles dostepne beda wyniki pomiarow uruchomionych z programu

W folderze sourceFiles znajduja sie pliki potrzebne do testow jednostkowych oraz plik test.txt ktory jest generowany losowo przy pomiarach, ktory mozemy rowniez stosowac jako plik wejsciowy programu

W folderze tests znajduja sie testy jednostkowe napisane przy uzyciu Gtest

W folderze cmake_build_release znajduja sie podfoldery z bibliotekami oraz programami 
Odpowiednio w podfolderach:

- podfolder src: program Main.exe sluzacy do wczytywania pliku i wykonywania na nim algorytmu 
WAZNE: plik do wczytania musi znajdowac sie w najbardziej zewnetrznej warstwie folderow projektu, w folderze o nazwie sourceFiles,
sluzacy rowniez do uruchomienia pomairow

- podfolder tests: program do uruchomienia wylacznie w IDE, sluzacy do testow jednostkowych