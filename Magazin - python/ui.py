from domain import *
from service import *

class Console():
    def __init__(self,srv):
        self.__srv=srv
        
    def adaugaProdus(self):
        while True:
            id=input("introduceti id produs: ")
            denumire=input("introduceti denumire produs: ")
            pret=input("introduceti pret produs: ")
            try:
                self.__srv.adaugaProdus(id,denumire,pret)
                print("")
                print("Produsul a fost adaugat cu succes!")
                print("")
                break
            except ExceptiiRepository:
                print("produs deja existent!")
            except ExceptiiValidare as ex:
                erori=ex.getErori()
                for eroare in erori:
                    eroare=eroare.strip()
                    print("")
                    print(eroare)
                    print("")
    
    def stergeProdus(self):
         while True:
            cifra=input("introduceti cifra id produs: ")
            try:
                self.__srv.stergeProdus(cifra)
                print("")
                print("Produsul a fost sters cu succes!")
                print("")
                break
            except ExceptiiRepository:
                print("produs inexistent!")
                
    def filtrare(self):
        while True:
            text=input("introduceti text filtru: ")
            numar=input("introduceti numar filtru: ")
            with open("filtre.txt","w") as file:
                line=str(text)+", "+str(numar)
                file.write(line)
            break
        
    def undo(self):
        while True:
            try:
                self.__srv.undo()
                print("operatie efectuata cu succes!")
            except ExceptiiRepository:
                print("nu exista operatii anterioare!")  
            break
    
    def run(self):
        while True:
            meniu="""
            1. Adauga produs
            2. Sterge produs
            3. Filtreaza produs
            4. Undo ultima operatie
            """
            print(meniu)
            comanda=input("introduceti comanda: ")
            self.__lista_comenzi={
                "1":self.adaugaProdus,
                "2":self.stergeProdus,
                "3":self.filtrare,
                "4":self.undo
                }
            if comanda in self.__lista_comenzi:
                self.__lista_comenzi[comanda]()
            else:
                print("comanda invalida!")
            with open("filtre.txt","r") as file:
                line=file.readline()
                parts=line.split(", ")
                print("")
                print("filtrele sunt: {} si {}".format(parts[0].strip(),parts[1].strip()))
                print("")
                print("Lista produselor filtrate este: ")
                if parts[0]!="":
                    #print("%")
                    if parts[1]!="-1":
                        for produs in self.__srv.getLista():
                            if produs.getDenumire()==parts[0] and produs.getPret()==parts[1]:
                                print("")
                                print(produs)
                                print("")
                    else:
                        #print("#")
                        for produs in self.__srv.getLista():
                            if produs.getDenumire()==parts[0]:
                                print("")
                                print(produs)
                                print("")
                else:
                    print("nu exista produse!")
                        

