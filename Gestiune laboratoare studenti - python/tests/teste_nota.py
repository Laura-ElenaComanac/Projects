from domain.notaStud import NotaStudent
from repository.repo_nota import RepositoryNota
from exceptii.exceptii import RepositoryStudentException
import unittest

class test_nota(unittest.TestCase):

    def setUp(self):
        unittest.TestCase.setUp(self)

    def test_creeaza_nota(self):
        """
        Testam nota
        """
        studentID=99
        nrLab_nrPb=(4,5)
        nota=10
        notaStud = NotaStudent(studentID,nrLab_nrPb,nota)
        self.assertEqual(notaStud.getStudentID(),studentID)
        self.assertEqual(notaStud.getNrLab_nrPb(),nrLab_nrPb)
        self.assertEqual(notaStud.getNota(),nota)
        notaStud.setNrLab_nrPb((3,4))
        alta_notaStud = NotaStudent(99,(3,4),2)
        self.assertEqual(notaStud,alta_notaStud)
        self.__nota=notaStud

    def test_addNota(self):
        studentID=99
        nrLab_nrPb=(4,5)
        nota=10
        notaStud = NotaStudent(studentID,nrLab_nrPb,nota)
        self.__repo = RepositoryNota()
        self.__repo.clear_repo()
        self.assertTrue(self.__repo.size_lista_note()==0)
        self.__repo.addNota(notaStud)
        self.assertTrue(self.__repo.size_lista_note()==1)
        self.assertTrue(self.__repo.getListaNote()==[notaStud])
        alta_nota=NotaStudent(99,(4,5),5)
        '''
        try:
            self.__repo.addNota(alta_nota)
            assert(False)
        except RepositoryStudentException as re:
            self.assertTrue(str(re),"A fost deja asignată o notă!")
        '''
            
        with self.assertRaises(RepositoryStudentException):
            self.__repo.addNota(alta_nota)
            
    def tearDown(self):
        unittest.TestCase.tearDown(self)
      
    '''      
    def ruleaza_teste(self):
        Testam functiile din repository
        self.__test_creeaza_nota()
        self.__test_addNota()
    '''
