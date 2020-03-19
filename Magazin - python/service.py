from domain import *
from repository import *

class ServiceMagazin():
    def __init__(self,repo,valid):
        self.__repo=repo
        self.__valid=valid
        
    def adaugaProdus(self,id,denumire,pret):
        produs=Produs(id,denumire,pret)
        self.__valid.valid(produs)
        self.__repo.adaugaProdus(produs)
        
    def stergeProdus(self,cifra):
        self.__repo.stergeProdus(cifra)
        
    def getLista(self):
        return self.__repo.getLista()
    
    def undo(self):
        self.__repo.undo()
    
        
    

    

