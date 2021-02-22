from domain import *
from validare import *
from repository import *

class ServiceJucator():
    def __init__(self,valid,repo):
        self.__valid=valid
        self.__repo=repo
        
    def addJucator(self,nume,prenume,inaltime,post):
        """
        Se creeaza obiectul de tip Jucator
        Se valideaza obiectul de tip Jucator
        Se adauga obiectul de tip Jucator
        Input: nume - nume al unui obiect de tip Jucator
        prenume - prenume al unui obiect de tip Jucator
        inaltime - inaltime al unui obiect de tip Jucator
        post - post al unui obiect de tip Jucator
        Output: Se adauga la lista de jucatori self._lista_jucatori jucatorul jucator
        Exceptii: raise ExceptiiRepository("Jucator deja existent!")
        """
        jucator=Jucator(nume,prenume,inaltime,post)
        self.__valid.validare(jucator)
        self.__repo.addJucator(jucator)

    def modificaInaltime(self,nume,prenume,inaltime_noua):
        """
        Se modifica obiectul de tip Jucator
        Input: nume - nume al unui obiect de tip Jucator
        prenume - prenume al unui obiect de tip Jucator
        inaltime_noua - noua inaltime a unui obiect de tip Jucator
        Output: Se modifica lista de jucatori self._lista_jucatori
        Exceptii: raise ExceptiiRepository("Jucator inexistent!")
        """
        self.__repo.modificaInaltime(nume,prenume,inaltime_noua)

    def echipa(self):
        """
        Se formeaza echipa construita din jucatorii disponibili cu media de inaltime cea mai mare fomrata din 2 fundasi, 2 extreme si  un pivot
        Input: no input
        Output: Lista echipa - lista de jucatori
        Exceptii: no exceptions
        """
        return self.__repo.echipa()
    
    def genereaza(self,nume_fisier):
        """
        Se iau fiecare nume si prenume din fisierul dat si se genereaza aleator inaltimea si postul si salveaza jucatorul astfel creat
        Input: nume_fisier - de tip string
        Output: Returneaza un tuplu format din self._lista_jucatori modificata si nr - numarul de jucatori importati
        Exceptii: no exceptions
        """
        return self.__repo.genereaza(nume_fisier)
    
    