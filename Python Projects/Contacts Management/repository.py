from domain import *
from exceptii import *

class RepositoryContact():
    def __init__(self):
        self._lista_contacte=[]
        
    def getLista(self):
        return self._lista_contacte
    
    def getSize(self):
        return len(self._lista_contacte)
    
    def clearRepo(self):
        self._lista_contacte.clear()
        
    def addContact(self,contact):
        for cont in self._lista_contacte:
            if cont.getNume()==contact.getNume():
                raise ExceptiiContact("nume deja existent!")
        self._lista_contacte.append(contact)
        
    def cautareContact(self,nume):
        nr=0
        for contact in self._lista_contacte:
            if contact.getNume()==nume:
                nr+=1
                return contact
        if nr==0:
            raise ExceptiiContact("nu exista nume!")
            
    def cautareContacteGrup(self,grup):
        lista_contacte=[]
        for contact in self._lista_contacte:
            if contact.getGrup()==grup:
                lista_contacte.append(contact)
        if len(lista_contacte)==0:
            raise ExceptiiContact("nu exista contacte!")
        else:
            lista_contacte.sort(key = lambda contact: contact.getNume())
            return lista_contacte
        
    
    
class FileRepositoryContact():
    def __init__(self,filename,read,write):
        RepositoryContact.__init__(self)
        self.__filename=filename
        self.__read=read
        self.__write=write
        
    def read_all_from_file(self):
        self._lista_contacte=[]
        with open(self.__filename,"r") as file:
            lines=file.readlines()
            for line in lines:
                line=line.strip()
                if line!="":
                    obj=self.__read(line)
                    self._lista_contacte.append(obj)
                    
    def write_all_to_file(self):
        with open(self.__filename,"w") as file:
            for obj in self._lista_contacte:
                line=self.__write(obj)
                file.write(line+'\n')
                
    def addContact(self,contact):
        self.read_all_from_file()
        RepositoryContact.addContact(self,contact)
        self.write_all_to_file()
        
    def cautareContact(self,contact):
        self.read_all_from_file()
        return RepositoryContact.cautareContact(self,contact)
        self.write_all_to_file()
        
    def cautareContacteGrup(self,grup):
        self.read_all_from_file()
        return RepositoryContact.cautareContacteGrup(self,grup)
        self.write_all_to_file()

