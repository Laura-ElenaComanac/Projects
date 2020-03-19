from domain import *
from exceptii import *
from service import *

class Console():
    def __init__(self,srv):
        self.__srv=srv
    
    def addContact(self):
        while True:
            id=input("introduceti id: ")
            nume=input("introduceti nume: ")
            nr=input("introduceti nr telefon: ")
            grup=input("introduceti grup: ")
            try:
                contact=Contact(id,nume,nr,grup)
                self.__srv.addContact(contact)
                print("")
                print("Contactul a fost adaugat!")
                print("")
                break
            except ExceptiiContact:
                print("nume deja existent!")
            except ExceptiiValidare as ex:
                erori=ex.getErori()
                for eroare in erori:
                    print("")
                    print(eroare)
                    print("")
                    
    def cautareContact(self):
        while True:
            nume=input("introduceti nume: ")
            try:
                contact=self.__srv.cautareContact(nume)
                print("")
                print("Contactul este: ")
                print(contact)
                print("")
                break
            except ExceptiiContact:
                print("nu exista nume!")
                
    def cautareContacteGrup(self):
        while True:
            grup=input("introduceti grup: ")
            try:
                contacte=self.__srv.cautareContacteGrup(grup)
                print("Contactele sunt: ")
                print("")
                for contact in  contacte:
                    print(contact)
                print("")
                break
            except ExceptiiContact:
                print("nu exista contacte!")
                
    def exporta(self):
        while True:
            grup=input("introduceti grup: ")
            fisier=input("introduceti nume fisier: ")
            with open(fisier+".csv","w") as file:
                contacte=self.__srv.cautareContacteGrup(grup)
                for contact in contacte:
                    file.write(str(contact.getNume())+", "+str(contact.getNrTelefon())+'\n')
            print("Grupurile au fost exportate su succes!")
            break
                
    def run(self):
        while True:
            meniu="""
            1. Adauga
            2. Cauta
            3. Tipareste
            4. Exporta
            """
            print(meniu)
            comanda=input("Introduceti comanda: ")
            self.__lista_comenzi={
                "1":self.addContact,
                "2":self.cautareContact,
                "3":self.cautareContacteGrup,
                "4":self.exporta
                }
            if comanda in self.__lista_comenzi:
                self.__lista_comenzi[comanda]()
            else:
                print("comanda invalida!")
            
            
            
