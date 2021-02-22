from domain.stud import Student
from repository.repo_student import RepositoryStudent
from exceptii.exceptii import RepositoryStudentException
import unittest
import random

class TesteStudent(unittest.TestCase):

    def test_creeaza_student(self):
        """
        Testam studentul
        """
        studentID=99
        nume="Olaru Marius"
        grup=1
        student = Student(studentID,nume,grup)
        self.assertTrue(student.getStudentID()==studentID)
        self.assertTrue(student.getNume()==nume)
        self.assertTrue(student.getGrup()==grup)
        student.setNume("Olaru Alexandru")
        self.assertTrue(student.getNume()=="Olaru Alexandru")
        alt_student = Student(99,"Olaru Laura",2)
        self.assertTrue(student == alt_student)

    def test_addStudent(self):
        studentID=99
        nume="Olaru Marius"
        grup=1
        student = Student(studentID,nume,grup)
        self.__repo = RepositoryStudent()
        self.__repo.clear_repo()
        self.assertTrue(self.__repo.size_lista_studenti()==0)
        self.__repo.addStudent(student)
        self.assertTrue(self.__repo.size_lista_studenti()==1)
        self.assertTrue(self.__repo.getListaStudenti()==[student])
        alt_student=Student(99,"Popescu Ionela",5)
        """
        try:
            self.__repo.addStudent(alt_student)
            assert(False)
        except RepositoryStudentException as re:
            assert(str(re)=="Exista deja un student cu acest ID!")
        """
        with self.assertRaises(RepositoryStudentException):
            self.__repo.addStudent(alt_student)
            
    def test_addStudent_black_box(self):
        self.__repo=RepositoryStudent()
        self.__listaIDuri=[]
        for i in range(1,11):
            studID=random.randint(1,10)
            tupluNume=('Ana','Laura','Maria','Andrei','Adrian','Marius')
            nume=random.choice(tupluNume)
            grup=random.randint(1,5)
            student=Student(studID,nume,grup)
            if studID in self.__listaIDuri:
                with self.assertRaises(RepositoryStudentException):
                    self.__repo.addStudent(student)
            else:
                antSize=self.__repo.size_lista_studenti()
                self.__repo.addStudent(student)
                self.assertTrue(self.__repo.size_lista_studenti()==antSize+1)
            self.__listaIDuri.append(studID)
            
    def test_modificaStudent(self):
        studentID=99
        nume="Olaru Marius"
        grup=1
        student = Student(studentID,nume,grup)
        self.__repo = RepositoryStudent()
        self.__repo.clear_repo()
        self.__repo.addStudent(student)
        self.__repo.modificaStudent(student,"Olaru Laura",10)
        stud=self.__repo.getListaStudenti()[-1]
        self.assertTrue(stud.getNume()=="Olaru Laura")
        self.assertTrue(stud.getGrup()==10)
        
    def test_deleteStudent(self):
        studentID=99
        nume="Olaru Marius"
        grup=1
        student = Student(studentID,nume,grup)
        self.__repo = RepositoryStudent()
        self.__repo.clear_repo()
        self.__repo.addStudent(student)
        """
        try:
            self.__repo.deleteStudent(100)
            assert(False)
        except RepositoryStudentException as re:
            assert(str(re)=="Studentul nu a fost gasit!")
        """
        with self.assertRaises(RepositoryStudentException):
            self.__repo.deleteStudent(100)
     
    '''       
    def ruleaza_teste(self):
        Testam functiile din repository
        self.__test_creeaza_student()
        self.__test_addStudent()
        self.__test_modificaStudent()
        self.__test_deleteStudent()
    '''
        
''''       
t = TesteStudent()
t.ruleaza_teste()
'''
