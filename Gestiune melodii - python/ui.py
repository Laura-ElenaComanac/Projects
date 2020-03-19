from service import *
from exceptii import *
from valid import *
from random import choice

"""
def criteriu(melodie):
    return melodie.getArtist()+melodie.getTitlu()
"""

class Console():
    def __init__(self,service):
        self.__service=service
        
    def addMelodie(self):
        while True:
            titlu=input("introduceti titlu: ")
            artist=input("introduceti artist: ")
            gen=input("introduceti gen: ")
            durata=int(input("introduceti durata: "))
            try:
                melodie=Melodie(titlu,artist,gen,durata)
                self.__service.addMelodie(melodie)
                print("")
                print("melodie adaugata cu succes!")
                print("")
                break
            except ExceptiiValidatorMelodie as ex:
                erori=ex.getErori()
                for eroare in erori:
                    print("")
                    print(eroare)
                    print("")
            except ExceptiiMelodie:
                print("")
                print("melodie deja existenta")
                print("")
                
    def modificaMelodie(self):
        while True:
            titlu=input("introduceti titlu: ")
            artist=input("introduceti artist: ")
            gen=input("introduceti noul gen: ")
            durata=int(input("introduceti noua durata: "))
            try:
                self.__service.modificaMelodie(artist,titlu,gen,durata)
                print("")
                print("melodie modificata cu succes!")
                print("")
                break
            except ExceptiiValidatorMelodie as ex:
                erori=ex.getErori()
                for eroare in erori:
                    print("")
                    print(eroare)
                    print("")
            except ExceptiiMelodie:
                print("")
                print("melodie deja existenta")
                print("") 
                
    def addMelodiiRandom(self):
        nr=int(input("introduceti numarul de melodii: "))
        self.__service.addMelodiiRandom(nr)
           
    def exportMelodie(self):
        nume_fisier=input("introduceti numele fisierului: ")
        with open(nume_fisier+".csv","w") as file:
            lista_melodii=self.__service.getListaMelodii()
            lista_melodii.sort(key=lambda melodie: melodie.getArtist() + melodie.getTitlu())
            #lista_melodii.sort(key=criteriu)
            for melodie in lista_melodii:
                file.write("{},{},{},{}\n".format(melodie.getArtist(),melodie.getTitlu(),melodie.getGen(),str(melodie.getDurata())))
            
    def run(self):
        while True:
            meniu="""
            1. Adauga melodie
            2. Modifica melodie
            3. Random melodii
            4. Exporta melodie
            """
            print(meniu)
            print("")
            comanda=input("introduceti comanda: ")
            self.__lista_comenzi={
                "1":self.addMelodie,
                "2":self.modificaMelodie,
                "3":self.addMelodiiRandom,
                "4":self.exportMelodie
                }
            if comanda in self.__lista_comenzi:
                self.__lista_comenzi[comanda]()
            else:
                print("comanda invalida")


