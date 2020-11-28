from domain import *
from exceptii import *

class RepositoryProdus():
    def __init__(self):
        self._lista_produse=[]
        self._lista_produse_undo=[]
        
    def clearRepo(self):
        self._lista_produse.clear()
        
    def getLista(self):
        return self._lista_produse
    
    def getSize(self):
        return len(self._lista_produse)
        
    def adaugaProdus(self,produs):
        for prod in self._lista_produse:
            if produs==prod:
                raise ExceptiiRepository("produs deja existent!")
        self._lista_produse.append(produs)
        
    def stergeProdus(self,cifra):
        self._lista_produse_undo.append(self._lista_produse.copy())
        p=0
        for produs in self._lista_produse:
            if produs.getId().find(cifra)>=0:
                self._lista_produse.remove(produs)
                p+=1
                self._lista_produse_undo.append(self._lista_produse.copy())
        if p==0:
            raise ExceptiiRepository("produs inexistent!")
        else:
            return (self._lista_produse,self._lista_produse_undo)
            
    def undo(self):
        try:
            self._lista_produse_undo.pop()
        except:
            raise ExceptiiRepository("nu exista operatii anterioare!")
        self._lista_produse=self._lista_produse_undo[-1]
        return self._lista_produse

class FileRepositoryProdus():
    def __init__(self,filename,read,write):
        RepositoryProdus.__init__(self)
        self.__filename=filename
        self.__read=read
        self.__write=write
        
    def read_all_from_file(self):
        self._lista_produse=[]
        with open(self.__filename,"r") as file:
            lines=file.readlines()
            for line in lines:
                line=line.strip()
                if line!="":
                    obj=self.__read(line)
                    self._lista_produse.append(obj)
                    
    def write_all_to_file(self):
        with open(self.__filename,"w") as file:
            for produs in self._lista_produse:
                line=self.__write(produs)
                file.write(line+"\n")
        
    def adaugaProdus(self,produs):
        self.read_all_from_file()
        RepositoryProdus.adaugaProdus(self, produs)
        self.write_all_to_file()
        
    def stergeProdus(self,cifra):
        self.read_all_from_file()
        (self._lista_produse,self._lista_produse_undo)=RepositoryProdus.stergeProdus(self,cifra)
        self.write_all_to_file()
        
    def getLista(self):
        self.read_all_from_file()
        return RepositoryProdus.getLista(self)
    
    def undo(self):
        self.read_all_from_file()
        self._lista_produse=RepositoryProdus.undo(self)
        self.write_all_to_file()
            
    


