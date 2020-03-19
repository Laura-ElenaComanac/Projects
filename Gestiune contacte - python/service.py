from repository import RepositoryContact
from validare import ValidareContact

class ServiceContact():
    def __init__(self,valid,repo):
        self.__valid=valid
        self.__repo=repo
        
    def addContact(self,contact):
        self.__valid.valid(contact)
        self.__repo.addContact(contact)
        
    def cautareContact(self,contact):
        return self.__repo.cautareContact(contact)
    
    def cautareContacteGrup(self,grup):
        return self.__repo.cautareContacteGrup(grup)


