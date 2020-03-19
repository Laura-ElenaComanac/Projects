from repository import *
from exceptii import *

class TesteJucator():
    def __init__(self):
        pass
    
    def test_addJucator(self):
        self.__repo=RepositoryJucator()
        self.__repo.clearRepo()
        assert(self.__repo.getLista()==[])
        assert(self.__repo.getSize()==0)
        jucator=Jucator("Olaru","Laura",162,"Pivot")
        self.__repo.addJucator(jucator)
        assert(self.__repo.getLista()==[jucator])
        assert(self.__repo.getSize()==1)
        try:
            self.__repo.addJucator(jucator)
            assert False 
        except ExceptiiRepository:
            assert True
        
    def test_modificaJucator(self):
        self.__repo=RepositoryJucator()
        self.__repo.clearRepo()
        jucator=Jucator("Olaru","Laura",162,"Pivot")
        self.__repo.addJucator(jucator)
        assert(self.__repo.getLista()==[Jucator("Olaru","Laura",162,"Pivot")])
        self.__repo.modificaInaltime("Olaru","Laura",164)
        assert(self.__repo.getLista()==[Jucator("Olaru","Laura",164,"Pivot")])
    
    def ruleaza(self):
        self.test_addJucator()
        self.test_modificaJucator()
