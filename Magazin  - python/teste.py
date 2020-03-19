from domain import *
from repository import *
from exceptii import *

class TesteMagazin():
    def __init__(self):
        pass
    
    def adaugaProdus(self):
        self.__repo=RepositoryProdus()
        self.__repo.clearRepo()
        produs=Produs("12","ss","133")
        self.__repo.adaugaProdus(produs)
        assert(self.__repo.getLista()==[produs])
        assert(self.__repo.getSize()==1)
        
    def ruleaza(self):
        self.adaugaProdus()
        


