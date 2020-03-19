from domain import *
from service import *
from exceptii import *

class Console():
    def __init__(self,srv):
        self.__srv=srv
        
    def addJucator(self):
        while True:
            nume=input("Introduceti nume jucator: ")
            prenume=input("Introduceti prenume jucator: ")
            inaltime=int(input("Introduceti inaltime jucator: "))
            post=input("Introduceti post jucator: ")
            try:
                self.__srv.addJucator(nume,prenume,inaltime,post)
                print("")
                print("Jucator adaugat cu succes!")
                print("")
                break
            except ExceptiiValidare as ex:
                erori=ex.getErori()
                for eroare in erori:
                    print("")
                    print(eroare)
                    print("")
            except ExceptiiRepository:
                print("")
                print("Jucator deja existent!")
                print("")
        
    def modificaInaltime(self):
        while True:
            nume=input("Introduceti nume jucator: ")
            prenume=input("Introduceti prenume jucator: ")
            inaltime=int(input("Introduceti inaltime noua jucator: "))
            try:
                self.__srv.modificaInaltime(nume,prenume,inaltime)
                print("")
                print("Jucator modificat cu succes!")
                print("")
                break
            except ExceptiiRepository:
                print("")
                print("Jucator inexistent!")
                print("")
            
    def echipa(self):
        while True:
            echipa=self.__srv.echipa()
            print("Jucatorii din echipa sunt: ")
            print("")
            for jucator in echipa:
                print(jucator)
            break
        
    def importa(self):
        nume_fisier=input("Introduceti numele fisierului: ")
        nr=self.__srv.genereaza(nume_fisier)
        print("")
        print("Jucatori importati cu succes!")
        print("")
        print("Au fost importati {} jucatori!".format(nr))
        print("")
            
    def run(self):
        while True:
            meniu="""
            1. Adauga jucator
            2. Modifica inaltime
            3. Tipareste echipa
            4. Importa jucatori
            """
            print(meniu)
            comanda=input("Introduceti comanda: ")
            self.__lista_comenzi={
                "1":self.addJucator,
                "2":self.modificaInaltime,
                "3":self.echipa,
                "4":self.importa
                }
            if comanda in self.__lista_comenzi:
                self.__lista_comenzi[comanda]()
            else:
                print("Comanda invalida!")
            
        
        
        