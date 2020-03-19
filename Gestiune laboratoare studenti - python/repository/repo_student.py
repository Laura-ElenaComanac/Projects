'''CREATE, READ, UPDATE, DELETE'''

from domain.stud import Student
from exceptii.exceptii import RepositoryStudentException
from utils import *

class RepositoryStudent():
    
    def __init__(self):
        self._listaStudenti = []
        #self.initializare_lista_studenti()

    '''
    def initializare_lista_studenti (self):
        student_1 = Student("100", "Laura", "5")
        self.addStudent(student_1)
        student_2 = Student("101", "Dragos", "2")
        self.addStudent(student_2)
        student_3 = Student("102", "Elena", "3")
        self.addStudent(student_3)
    '''
        
    def size_lista_studenti(self):
        """Dimensiunea _listaStudenti din repository
          returneaza un numar intreg"""
        return len(self._listaStudenti)

    def addStudent(self,student):
        """
        Adaugarea unui nou student in lista
        student - obiect de tip Student
        RepositoryStudentException: "Exista deja un student cu acest ID!"
        """
        for studentDinLista in self._listaStudenti:
            if studentDinLista.getStudentID()==student.getStudentID():
                raise RepositoryStudentException("Exista deja un student cu acest ID!")
        self._listaStudenti.append(student)
        
    def addStudent_recursiv(self,student,dim):
        """
        Adaugarea unui nou student in lista recursiv
        student - obiect de tip Student
        dim - dimensiunea de tip int a listei
        RepositoryStudentException: "Exista deja un student cu acest ID!"
        """
        #dim=len(self._listaStudenti)-1
        if dim>=0:
            if self._listaStudenti[dim].getStudentID()==student.getStudentID():
                raise RepositoryStudentException("Exista deja un student cu acest ID!")
            else:
                self.addStudent_recursiv(student,dim-1)
        else:      
            self._listaStudenti.append(student)
        
    def deleteStudent(self,studentID):
        '''
        Stergerea unui student din lista
        studentID - ID-ul studentului de tip int
        RepositoryStudentException: "Studentul nu a fost gasit!"
        '''
        gasit=0
        for student in self._listaStudenti:
            if student.getStudentID()==studentID:
                gasit=1
                self._listaStudenti.remove(student)
        if gasit==0:
            raise RepositoryStudentException("Studentul nu a fost gasit!")
        
    def cautaStudent(self,studID):
        '''
        Cautarea unui student in lista
        studID - ID-ul studentului de tip int
        RepositoryStudentException: "Nu există un student cu acest ID!"
        '''
        for student in self._listaStudenti:
            if student.getStudentID()==studID:
                return student
        raise RepositoryStudentException("Nu există un student cu acest ID!")
    
    def modificaStudent(self, student,numeNou,grupNou):
        '''
        Modifica numele si grupul unui student
        student - obiect de tip Student
        numeNou - numele nou al studentului de tip string
        grupNou - grupul nou al studentului de tip int
        RepositoryStudentException: "ID inexistent!"
        '''
        ok=False
        for studentDinLista in self._listaStudenti:
            if studentDinLista.getStudentID()==student.getStudentID():
                studentDinLista.setNume(numeNou)
                studentDinLista.setGrup(grupNou)
                ok=True
        if ok==False:
            raise RepositoryStudentException("ID inexistent!")
        
    def modificaStudent_recursiv(self, student,numeNou,grupNou,dim,ok):
        '''
        Modifica numele si grupul unui student recursiv
        student - obiect de tip Student
        numeNou - numele nou al studentului de tip string
        grupNou - grupul nou al studentului de tip int
        RepositoryStudentException: "ID inexistent!"
        '''
        if dim>=0:
            if self._listaStudenti[dim].getStudentID()==student.getStudentID():
                self._listaStudenti[dim].setNume(numeNou)
                self._listaStudenti[dim].setGrup(grupNou)
                ok=True
            else:
                self.modificaStudent_recursiv(student,numeNou,grupNou,dim-1,ok)
        else:
            if ok==False:
                raise RepositoryStudentException("ID inexistent!")
         
    def getListaStudenti(self):
        """Returneaza lista de studenti"""
        return self._listaStudenti
    
    def afisare_lista(self,lista):
        """Afiseaza lista de studenti"""
        for element in lista:
            print(repr(element))
            
    def clear_repo(self):
        """Curata repository"""
        self._listaStudenti.clear()
        
    def get_grupe(self):
        """Returneaza lista de grupe"""
        lista_grupe=[]
        for i in self.getListaStudenti():
            if i.getGrup() not in lista_grupe:
                lista_grupe.append(i.getGrup())
        return lista_grupe
        
    def get_grupa(self,studID):
        """
        Returneaza grupa studentului identificat dupa studID
        studID - ID-ul studentului de tip int
        """
        for i in self.getListaStudenti():
            if str(i.getStudentID())==str(studID):
                return i.getGrup()
            
    def sorteaza_studenti(self):
        BubbleSort(self._listaStudenti,cmp,reverse=False,key=lambda student:student.getStudentID())
        #ShellSort(self._listaStudenti)
        
class FileRepositoryStudent(RepositoryStudent):
    
    def __init__(self,filename,read_stud,write_stud):
        RepositoryStudent.__init__(self)
        self.__filename = filename
        self.__read_stud = read_stud
        self.__write_stud = write_stud
        
    def __read_all_from_file(self):
        """
        Citeste din fisier si adauga in lista studentii
        """
        self._listaStudenti = []
        with open(self.__filename,"r") as f:
            lines = f.readlines() #returns a list containing the lines
            for line in lines:
                #line = line.strip()
                if line != "":
                    stud = self.__read_stud(line)
                    self._listaStudenti.append(stud)
    
    def __write_all_to_file(self):
        """
        Ia din lista si adauga in fisier studentii
        """
        with open(self.__filename,"w") as f:
            for stud in self._listaStudenti:
                line = self.__write_stud(stud)
                f.write(line+"\n")    
        
    def addStudent(self, stud):
        """
        Adaugarea unui nou student in lista, cu citire si scriere in fisier
        stud - obiect de tip Student
        RepositoryStudentException: "Exista deja un student cu acest ID!"
        """
        self.__read_all_from_file()
        RepositoryStudent.addStudent(self, stud)
        self.__write_all_to_file()
        
    def deleteStudent(self, stud):
        '''
        Stergerea unui student din lista, cu citire si scriere in fisier
        studentID - ID-ul studentului de tip int
        RepositoryStudentException: "Studentul nu a fost gasit!"
        '''
        self.__read_all_from_file()
        RepositoryStudent.deleteStudent(self, stud)
        self.__write_all_to_file()
        
    def modificaStudent(self, student,numeNou,grupNou):
        '''
        Modifica numele si grupul unui student, cu citire si scriere in fisier
        student - obiect de tip Student
        numeNou - numele nou al studentului de tip string
        grupNou - grupul nou al studentului de tip int
        RepositoryStudentException: "ID inexistent!"
        '''
        self.__read_all_from_file()
        RepositoryStudent.modificaStudent(self, student,numeNou,grupNou)
        self.__write_all_to_file()
        
    def cautaStudent(self, studID):
        '''
        Cautarea unui student in lista, cu citire din fisier
        studID - ID-ul studentului de tip int
        RepositoryStudentException: "Nu există un student cu acest ID!"
        '''
        self.__read_all_from_file()
        return RepositoryStudent.cautaStudent(self, studID)
    
    def getListaStudenti(self):
        """Returneaza lista de studenti, citita din fisier"""
        self.__read_all_from_file()
        return RepositoryStudent.getListaStudenti(self)
    
    def size_lista_studenti(self):
        """Dimensiunea _listaStudenti din repository, cu citire din fisier
        returneaza un numar intreg"""
        self.__read_all_from_file()
        return RepositoryStudent.size_lista_studenti(self)
    
    def addStudent_recursiv(self,student,dim):
        """
        Adaugarea unui nou student in lista recursiv, cu citire si scriere in fisier
        student - obiect de tip Student
        dim - dimensiunea de tip int a listei
        RepositoryStudentException: "Exista deja un student cu acest ID!"
        """
        self.__read_all_from_file()
        RepositoryStudent.addStudent_recursiv(self, student, dim)
        self.__write_all_to_file()
        
    def modificaStudent_recursiv(self, student,numeNou,grupNou,dim,ok):
        '''
        Modifica numele si grupul unui student recursiv, cu citire si scriere in fisier
        student - obiect de tip Student
        numeNou - numele nou al studentului de tip string
        grupNou - grupul nou al studentului de tip int
        RepositoryStudentException: "ID inexistent!"
        '''
        self.__read_all_from_file()
        RepositoryStudent.modificaStudent_recursiv(self, student, numeNou, grupNou, dim, ok)
        self.__write_all_to_file()
        
    def sorteaza_studenti(self):
        self.__read_all_from_file()
        RepositoryStudent.sorteaza_studenti(self)
        self.__write_all_to_file()
