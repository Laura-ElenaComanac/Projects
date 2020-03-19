'''CREATE, READ, UPDATE, DELETE'''

from domain.probLab import ProblemaLaborator
from exceptii.exceptii import RepositoryProbLabException
from utils import *

class RepositoryProblemaLab():
    def __init__(self):
        self._listaProblemeLab = []
        #self.initializare_listaProblemeLab()

    '''
    def initializare_listaProblemeLab (self):
        problema_1 = ProblemaLaborator((2,4), "sume", "23.12.2019")
        self.addProblemaLab(problema_1)
        problema_2 = ProblemaLaborator((10,11), "scaderi", "23.04.2020")
        self.addProblemaLab(problema_2)
        problema_3 = ProblemaLaborator((5,6), "inmultiri", "10.12.2019")
        self.addProblemaLab(problema_3)
    '''
          
    def size_listaProblemeLab(self):
        """Dimensiunea _listaProblemeLab din repository
          returneaza un numar intreg"""
        return len(self._listaProblemeLab)

    def addProblemaLab(self,problemaLab):
        """CREATE"""
        """Adaugarea unei noi probleme in lista"""
        for problemaDinLista in self._listaProblemeLab:
            if problemaDinLista.getNrLab_nrPb()==problemaLab.getNrLab_nrPb():
                raise RepositoryProbLabException("Există deja o problemă de acest tip!")
        self._listaProblemeLab.append(problemaLab)
        
    def deleteProblemaLab(self,NrLab_nrPb):
        '''DELETE'''
        '''Stergerea unei probleme din lista'''
        gasit=0
        for problemaLab in self._listaProblemeLab:
            if problemaLab.getNrLab_nrPb()==NrLab_nrPb:
                gasit=1
                self._listaProblemeLab.remove(problemaLab)
        if gasit==0:
            raise RepositoryProbLabException("Problema nu a fost găsită!")
    
    def cautaProblemaLab(self,NrLab_nrPb):
        """READ"""
        for problemaLab in self._listaProblemeLab:
            if problemaLab.getNrLab_nrPb()==NrLab_nrPb:
                return problemaLab
    
    def modificaProblemaLab(self, NrLab_nrPb,descriereNoua,deadlineNou):
        '''UPDATE'''
        '''Functia modifica descrierea si deadline-ul unei probleme identificate dupa NrLab_nrPb'''
        ok=False
        for problemaLab in self._listaProblemeLab:
            if problemaLab.getNrLab_nrPb()==NrLab_nrPb:
                problemaLab.setDescriere(descriereNoua)
                problemaLab.setDeadline(deadlineNou)
                ok=True
        if ok==False:
            raise RepositoryProbLabException("Problemă inexistentă!")
         
    def getListaProblemeLab(self):
        """Obtinerea listei de probleme"""
        return self._listaProblemeLab
    
    def afisare_lista(self,lista):
        for element in lista:
            print(repr(element))
            
    def sorteaza_probleme(self):
        #BubbleSort(self._listaProblemeLab, key=lambda problemaLab:problemaLab.getNrLab_nrPb())
        ShellSort(self._listaProblemeLab)
            
class FileRepositoryProblemaLab(RepositoryProblemaLab):
    
    def __init__(self,filename,read_probLab,write_probLab):
        RepositoryProblemaLab.__init__(self)
        self.__filename = filename
        self.__read_probLab = read_probLab
        self.__write_probLab = write_probLab
        
    def __read_all_from_file(self):
        self._listaProblemeLab = []
        with open(self.__filename,"r") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    probLab = self.__read_probLab(line)
                    self._listaProblemeLab.append(probLab)
    
    def __write_all_to_file(self):
        with open(self.__filename,"w") as f:
            for probLab in self._listaProblemeLab:
                line = self.__write_probLab(probLab)
                f.write(line+"\n")    
        
    def addProblemaLab(self, probLab):
        self.__read_all_from_file()
        RepositoryProblemaLab.addProblemaLab(self, probLab)
        self.__write_all_to_file()
        
    def deleteProblemaLab(self, probLab):
        self.__read_all_from_file()
        RepositoryProblemaLab.deleteProblemaLab(self, probLab)
        self.__write_all_to_file()
        
    def modificaProblemaLab(self, probLab):
        self.__read_all_from_file()
        RepositoryProblemaLab.modificaProblemaLab(self, probLab)
        self.__write_all_to_file()
        
    def cautaProblemaLab(self, probLab):
        self.__read_all_from_file()
        return RepositoryProblemaLab.cautaProblemaLab(self, probLab)
    
    def getListaProblemeLab(self):
        self.__read_all_from_file()
        return RepositoryProblemaLab.getListaProblemeLab(self)
    
    def sorteaza_probleme(self):
        self.__read_all_from_file()
        RepositoryProblemaLab.sorteaza_probleme(self)
        self.__write_all_to_file()

