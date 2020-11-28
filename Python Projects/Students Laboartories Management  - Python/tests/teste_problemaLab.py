from domain.probLab import ProblemaLaborator
from repository.repo_problemaLab import RepositoryProblemaLab
from exceptii.exceptii import RepositoryProbLabException
import unittest

class TesteProblemaLab(unittest.TestCase):

    def setUp(self):
        unittest.TestCase.setUp(self)

    def test_creeaza_problemaLab(self):
        """
        Testam problema
        """
        NrLab_nrPb=(7,3)
        descriere="Numarare"
        deadline="10.12.2019"
        problemaLab = ProblemaLaborator(NrLab_nrPb,descriere,deadline)
        self.assertTrue(problemaLab.getNrLab_nrPb()==NrLab_nrPb)
        self.assertTrue(problemaLab.getDescriere()==descriere)
        self.assertTrue(problemaLab.getDeadline()==deadline)
        problemaLab.setDescriere("Adunare")
        self.assertTrue(problemaLab.getDescriere()=="Adunare")
        alta_problemaLab = ProblemaLaborator((7,3),"Impartire","11.11.2019")
        self.assertTrue(problemaLab == alta_problemaLab)
        self.__problemaLab = problemaLab

    def test_addProblemaLab(self):
        NrLab_nrPb=(7,3)
        descriere="Numarare"
        deadline="10.12.2019"
        problemaLab = ProblemaLaborator(NrLab_nrPb,descriere,deadline)
        self.__repo = RepositoryProblemaLab()
        self.assertTrue(self.__repo.size_listaProblemeLab()==0)
        self.__repo.addProblemaLab(problemaLab)
        self.assertTrue(self.__repo.size_listaProblemeLab()==1)
        self.assertTrue(self.__repo.getListaProblemeLab()==[problemaLab])
        alta_problemaLab=ProblemaLaborator((7,3),"Scadere","12.12.2019")
        """
        try:
            self.__repo.addProblemaLab(alta_problemaLab)
            assert(False)
        except RepositoryProbLabException as re:
            assert(str(re)=="Există deja o problemă de acest tip!")
        """
        with self.assertRaises(RepositoryProbLabException):
            self.__repo.addProblemaLab(alta_problemaLab)
            
    def test_modificaProblemaLab(self):
        NrLab_nrPb=(7,3)
        descriere="Numarare"
        deadline="10.12.2019"
        problemaLab = ProblemaLaborator(NrLab_nrPb,descriere,deadline)
        self.__repo = RepositoryProblemaLab()
        self.__repo.addProblemaLab(problemaLab)
        self.__repo.modificaProblemaLab((7,3),"Scadere","13.12.2019")
        probLab=self.__repo.getListaProblemeLab()[-1]
        self.assertTrue(probLab.getDescriere()=="Scadere")
        self.assertTrue(probLab.getDeadline()=="13.12.2019")
        
    def test_deleteProblemaLab(self):
        NrLab_nrPb=(7,3)
        descriere="Numarare"
        deadline="10.12.2019"
        problemaLab = ProblemaLaborator(NrLab_nrPb,descriere,deadline)
        self.__repo = RepositoryProblemaLab()
        self.__repo.addProblemaLab(problemaLab)
        """
        try:
            self.__repo.deleteProblemaLab((8,6))
            assert(False)
        except RepositoryProbLabException as re:
            assert(str(re)=="Problema nu a fost găsită!")
        """
        with self.assertRaises(RepositoryProbLabException):
            self.__repo.deleteProblemaLab((8,6))
          
    def tearDown(self):
        unittest.TestCase.tearDown(self)
      
    """
    def ruleaza_teste(self):
        '''Testam functiile din repository'''
        self.__test_creeaza_problemaLab()
        self.__test_addProblemaLab()
        self.__test_modificaProblemaLab()
        self.__test_deleteProblemaLab()
    """
