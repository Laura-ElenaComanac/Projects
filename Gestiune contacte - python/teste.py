from domain import *
from repository import *

class TesteContact():
    def __init__(self):
        pass
    
    def addContact(self):
        self.__repo=RepositoryContact()
        self.__repo.clearRepo()
        contact=Contact("100","laura","09083232","Prieteni")
        self.__repo.addContact(contact)
        assert(self.__repo.getLista()==[contact])
        assert(self.__repo.getSize()==1)
        
    def cautareContact(self):
        self.__repo=RepositoryContact()
        contact=Contact("22", "lala", "1234567", "Prieteni")
        contact_cautat=self.__repo.cautareContact("lala")
        assert(str(contact_cautat)==str(contact))
        
    def ruleaza(self):
        self.cautareContact()
        self.addContact()
        




