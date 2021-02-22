'''CREATE, READ, UPDATE, DELETE'''

from domain.stud import Student
from domain.notaStud import NotaStudent
from exceptii.exceptii import *
from utils import *

class RepositoryNota():
    
    def __init__(self):
        self._listaNote = []
        #self.initializare_lista_note()

    '''
    def initializare_lista_note (self):
        nota_1 = NotaStudent(100, (2,4), 10)
        self.addNota(nota_1)
        nota_2 = NotaStudent(101, (10,11), 2)
        self.addNota(nota_2)
        nota_3 = NotaStudent(102, (5,6), 4)
        self.addNota(nota_3)
    '''
        
    def clear_repo(self):
        self._listaNote.clear()
        
    def size_lista_note(self):
        """Dimensiunea _listaNote din repository
          returneaza un numar intreg"""
        return len(self._listaNote)

    def addNota(self,nota):
        """CREATE"""
        """
        Adaugarea unei noi note in lista
        nota - nota
        adauga nota in lista _listaNote, daca este gasita
        """
        for notaDinLista in self._listaNote:
            if notaDinLista.getStudentID()==nota.getStudentID() and notaDinLista.getNrLab_nrPb()==nota.getNrLab_nrPb():
                raise RepositoryStudentException("A fost deja asignată o notă!")
        self._listaNote.append(nota)
        
        
    def cautaNota(self,studID,nrLab_nrPb):
        """READ"""
        """
          Cauta nota dupa ID-ul unui student si dupa numarul laboratorului/problemei acestuia
          studID - ID-ul unui student
          nrLab_nrPb - numarul laboratorului/problemei
          returneaza nota
        """
        for nota in self._listaNote:
            if nota.getStudentID()==studID and nota.getNrLab_nrPb==nrLab_nrPb:
                return nota
            
    def deleteNota(self,nota):
        for i in self.getListaNote():
            if i==nota:
                self.getListaNote().remove(nota)
                return
    
    def getAll(self,studID):
        """
         Returneaza notele pentru un student dat
         student - student
        """
        rez = []
        for nota in self._listaNote:
            if nota.getStudentID()==studID:
                rez.append(nota.getNota())
        return rez
    
    def getAllForProblemaLab(self,nrLab_nrPb):
        """
         Returneaza toate notele pentru toti studentii de la fiecare problema de laborator
         nrLab_nrPb - tuplu de int, numarul laboratorului/problemei
         returneaza lista notelor
        """
        rez = []
        for nota in self._listaNote:
            if nota.getNrLab_nrPb()==nrLab_nrPb:
                notaStud = NotaStudent(nota.getStudentID(),nota.getNrLab_nrPb(),nota.getNota())
                rez.append(notaStud)
        return rez
    
    def getListaNote(self):
        """Obtinerea listei de note"""
        return self._listaNote
    
    def afisare_lista(self,lista):
        """Afisarea listei de note"""
        for element in lista:
            print(repr(element))
            
    def get_element(self,index):
        return self.getListaNote()[index]
            
    def sorteaza_note(self):
        #BubbleSort(self._listaNote, key=lambda nota:nota.getNota())
        ShellSort(self._listaNote)
            
class FileRepositoryNota(RepositoryNota):
    
    def __init__(self,filename,read_nota,write_nota):
        RepositoryNota.__init__(self)
        self.__filename = filename
        self.__read_nota = read_nota
        self.__write_nota = write_nota
        
    def __read_all_from_file(self):
        self._listaNote = []
        with open(self.__filename,"r") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    nota = self.__read_nota(line)
                    self._listaNote.append(nota)
    
    def __write_all_to_file(self):
        with open(self.__filename,"w") as f:
            for nota in self._listaNote:
                line = self.__write_nota(nota)
                f.write(line+"\n")    
        
    def addNota(self, nota):
        self.__read_all_from_file()
        RepositoryNota.addNota(self, nota)
        self.__write_all_to_file()
        
    def deleteNota(self, nota):
        self.__read_all_from_file()
        RepositoryNota.deleteNota(self, nota)
        self.__write_all_to_file()
        
    def cautaNota(self, nota):
        self.__read_all_from_file()
        return RepositoryNota.cautaNota(self, nota)
    
    def getListaNote(self):
        self.__read_all_from_file()
        return RepositoryNota.getListaNote(self)
    
    def sorteaza_note(self):
        self.__read_all_from_file()
        RepositoryNota.sorteaza_note(self)
        self.__write_all_to_file()


    
    