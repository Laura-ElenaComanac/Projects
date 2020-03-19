from domain import *
from exceptii import *
from random import choice

class RepositoryJucator():
    def __init__(self):
        self._lista_jucatori=[]
        
    def getLista(self):
        """
        Returneaza lista self._lista_jucatori
        """
        return self._lista_jucatori
    
    def getSize(self):
        """
        Returneaza lungimea listei self._lista_jucatori
        """
        return len(self._lista_jucatori)
    
    def clearRepo(self):
        """
        Curata continutul listei self._lista_jucatori
        """
        self._lista_jucatori.clear()
        
    def addJucator(self,jucator):
        """
        Input: jucator - obiect de tip Jucator
        Output: Se adauga la lista de jucatori self._lista_jucatori jucatorul jucator
        Exceptii: raise ExceptiiRepository("Jucator deja existent!")
        """
        for juc in self._lista_jucatori:
            if jucator==juc:
                raise ExceptiiRepository("Jucator deja existent!")
        self._lista_jucatori.append(jucator)
        
    def modificaInaltime(self,nume,prenume,inaltime_noua):
        """
        Input: nume - numele unui jucator - de tip string
        prenume - prenumele unui jucator - de tip string
        inaltime_noua - noua inaltime a unui jucator - de tip int
        Output: Se modifica lista de jucatori self._lista_jucatori: se actualizeaza inaltimea jucatorului cu nume si prenume date
        Exceptii: raise ExceptiiRepository("Jucator inexistent!")
        """
        nr=0
        for jucator in self._lista_jucatori:
            if jucator.getNume()==nume and jucator.getPrenume()==prenume:
                jucator.setInaltime(inaltime_noua)
                nr+=1
        if nr==0:
            raise ExceptiiRepository("Jucator inexistent!")
        
    def echipa(self):
        """
        Se formeaza echipa construita din jucatorii disponibili cu media de inaltime cea mai mare fomrata din 2 fundasi, 2 extreme si  un pivot
        Input: no input
        Output: Lista echipa - lista de jucatori
        Exceptii: no exceptions
        """
        echipa=[]
        self._lista_jucatori.sort(key = lambda jucator: jucator.getInaltime(), reverse = True)
        fundasi=0
        extreme=0
        pivot=0
        for jucator in self._lista_jucatori:
            if fundasi<2 and jucator.getPost()=="Fundas":
                fundasi+=1
                echipa.append(jucator)
            if extreme<2 and jucator.getPost()=="Extrema":
                extreme+=1
                echipa.append(jucator)
            if pivot<1 and jucator.getPost()=="Pivot":
                pivot+=1
                echipa.append(jucator)
        return echipa 
    
    def genereaza(self,nume_fisier):
        """
        Se iau fiecare nume si prenume din fisierul dat si se genereaza aleator inaltimea si postul si salveaza jucatorul astfel creat
        Input: nume_fisier - de tip string
        Output: Returneaza un tuplu format din self._lista_jucatori modificata si nr - numarul de jucatori importati
        Exceptii: no exceptions
        """
        nr=0
        inaltimi=list(range(100,220))
        posturi=["Fundas","Pivot","Extrema"]
        with open(nume_fisier+".txt","r") as file:
            lines=file.readlines()
            for line in lines:
                line=line.strip()
                if line!="":
                    parts=line.split(", ")
                    nume=parts[0].strip()
                    prenume=parts[1].strip()
                    test=1
                    for jucator in self._lista_jucatori:
                        if jucator.getNume()==nume or jucator.getPrenume()==prenume:
                            test=0
                    if test==1:
                        nr+=1
                        jucator=Jucator(nume,prenume,choice(inaltimi),choice(posturi))
                        self._lista_jucatori.append(jucator)
        return (self._lista_jucatori,nr)
         
class FileRepositoryJucator():
    def __init__(self,filename,read,write):
        RepositoryJucator.__init__(self)
        self.__filename=filename
        self.__read=read
        self.__write=write
        
    def read_all_from_file(self):
        """
        Citeste valorile din fisier si le adauga la lista  self._lista_jucatori
        """
        self._lista_jucatori=[]
        with open(self.__filename,"r") as file:
            lines=file.readlines()
            for line in lines:
                line=line.strip()
                if line!="":
                    obj=self.__read(line)
                    self._lista_jucatori.append(obj)
                    
    def write_all_to_file(self): 
        """
        Scrie valorile din lista self._lista_jucatori in fisier
        """  
        with open(self.__filename,"w") as file:
            for jucator in self._lista_jucatori:
                line=self.__write(jucator)
                file.write(line+"\n")
                
    def addJucator(self,jucator):
        """
        Se citesc valorile din fisier, se apeleaza functia din RepositoryJucator si apoi se scriu valorile in fisier
        Input: jucator - obiect de tip Jucator
        Output: Se adauga la lista de jucatori self._lista_jucatori jucatorul jucator
        Exceptii: raise ExceptiiRepository("Jucator inexistent!")
        """
        self.read_all_from_file()
        RepositoryJucator.addJucator(self, jucator)
        self.write_all_to_file()
        
    def modificaInaltime(self,nume,prenume,inaltime_noua):
        """
        Se citesc valorile din fisier, se apeleaza functia din RepositoryJucator si apoi se scriu valorile in fisier
        Input: nume - numele unui jucator - de tip string
        prenume - prenumele unui jucator - de tip string
        inaltime_noua - noua inaltime a unui jucator - de tip int
        Output: Se modifica lista de jucatori self._lista_jucatori: se actualizeaza inaltimea jucatorului cu nume si prenume date
        Exceptii: raise ExceptiiRepository("Jucator inexistent!")
        """
        self.read_all_from_file()
        RepositoryJucator.modificaInaltime(self, nume, prenume, inaltime_noua)
        self.write_all_to_file()
        
    def echipa(self):
        """
        Se formeaza echipa construita din jucatorii disponibili cu media de inaltime cea mai mare fomrata din 2 fundasi, 2 extreme si  un pivot
        Input: no input
        Output: Lista echipa - lista de jucatori
        Exceptii: no exceptions
        """
        self.read_all_from_file()
        return RepositoryJucator.echipa(self)  
    
    def genereaza(self,nume_fisier):
        """
        Se iau fiecare nume si prenume din fisierul dat si se genereaza aleator inaltimea si postul si salveaza jucatorul astfel creat
        Input: nume_fisier - de tip string
        Output: Returneaza un tuplu format din self._lista_jucatori modificata si nr - numarul de jucatori importati
        Exceptii: no exceptions
        """
        self.read_all_from_file()
        (self._lista_jucatori,nr)=RepositoryJucator.genereaza(self, nume_fisier)
        self.write_all_to_file()
        return nr
                    
