'''valideaza si apeleaza din repository + statistici'''

from domain.probLab import ProblemaLaborator
from validare.valid_problemaLab import ValidatorProblemaLab
from repository.repo_problemaLab import RepositoryProblemaLab

class ServiceProblemaLab():
    def __init__(self,repo,valid):
        """
          Initializeaza service
          repo - repository - object to store problems
          valid - validator - object to validate problems
        """
        self.__repo = repo
        self.__valid = valid
        
    def creeaza(self,nrLab_nrPb, descriere, deadline):
        """
          Retine o problemă
          nrLab_nrPb ca tuplu de int, descriere si deadline ca string
          returneaza problema
          Post: problema adaugata in repository
          raise RepositoryStudentException - daca problema deja exista
          raise ValidatorStudentException - daca datele problemei sunt invalide
        """
        #valideaza studentul folosind un obiect validator
        self.__valid.validate(nrLab_nrPb, descriere, deadline)
        #creeaza obiectul problemaLab
        problemaLab = ProblemaLaborator(nrLab_nrPb, descriere, deadline)
        #Retine studentul in repository
        self.__repo.addProblemaLab(problemaLab)
        
        return problemaLab
    
    def sterge(self,nrLab_nrPb):
        """
        Sterge o problema
        nrLab_nrPb tuplu de int
        """
        self.__valid.validate_nr(nrLab_nrPb)
        self.__repo.deleteProblemaLab(nrLab_nrPb)
        
    def modifica(self, nrLab_nrPb, descriere, deadline):
        """
        Modifica informatiile unei probleme
        nrLab_nrPb ca tuplu de int, descriere si deadline ca string
        """
        self.__valid.validate(nrLab_nrPb, descriere, deadline)
        self.__repo.modificaProblemaLab(nrLab_nrPb, descriere, deadline)

    def cauta(self, nrLab_nrPb):
        """
        Cauta problema dupa nrLab_nrPb
        input: nrLab_nrPb
        output: problema gasita
        """
        return self.__repo.cautaProblemaLab(nrLab_nrPb)
    
    def get_problemeLab(self):
        """
        Returneaza lista tuturor problemelor din sistem
        """
        return self.__repo.getListaProblemeLab()
    
    def sorteaza_probleme(self):
        self.__repo.sorteaza_probleme()

    