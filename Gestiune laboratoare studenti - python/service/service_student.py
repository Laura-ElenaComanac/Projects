'''valideaza si apeleaza din repository + statistici'''

from domain.stud import Student
from validare.valid_student import ValidatorStudent
from repository.repo_student import RepositoryStudent
import string
import random
from exceptii.exceptii import RepositoryStudentException

class ServiceStudent():
    def __init__(self,repo,valid):
        """
          Initializeaza service
          repo - repository - object to store students
          valid - validator - object to validate students
        """
        self.__repo = repo
        self.__valid = valid
        
    def creeaza(self,student):
        """
          Retine un student
          studID si grup ca int, nume ca string
          returneaza studentul
          Post: studentul adaugat in repository
          raise RepositoryStudentException - daca studentul deja exista
          raise ValidatorStudentException - daca datele studentului sunt invalide
        """
        self.__valid.validate(student)
        #valideaza studentul folosind un obiect validator
        #self.__repo.addStudent(student)
        dim=self.__repo.size_lista_studenti()-1
        self.__repo.addStudent_recursiv(student,dim)
        #Retine studentul in repository
        #return student
    
    def sterge(self,studID):
        """
        Sterge un student
        studID int
        """
        self.__valid.validate_id(studID)
        self.__repo.deleteStudent(studID)
        
    def modifica(self, studID, nume, grup):
        """
        Modifica informatiile unui student
        studID si grup ca int, nume ca string
        """
        student=self.__repo.cautaStudent(studID)
        self.__valid.validate(student)
        dim=self.__repo.size_lista_studenti()-1
        ok=False
        self.__repo.modificaStudent_recursiv(student,nume,grup,dim,ok)

    def cauta(self, studID):
        """
        Cauta student dupa ID
        input: studID
        output: studentul gasit
        """
        return self.__repo.cautaStudent(studID)
    
    def get_studenti(self):
        """
        Returneaza lista tuturor studentilor din sistem
        """
        return self.__repo.getListaStudenti()
    
    def create_random_student(self):
        """
        Returneaza random un student
        """
        string_len=10
        letters=string.ascii_letters
        st_name=' '.join(random.choice(letters) for i in range(string_len))
        st_id=random.randint(1,100)
        st_grup=random.randint(1,100)
        return Student(st_id, st_name, st_grup)
    
    def create_random_students(self, number_of_students):
        """
        Returneaza number_of_students studenti
        """
        for n in range(number_of_students):
            student=self.create_random_student()
            try:
                self.__repo.addStudent(student)
            except RepositoryStudentException:
                n-=1
                
    def sorteaza_studenti(self):
        self.__repo.sorteaza_studenti()
                
    