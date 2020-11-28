from repository import *
from valid import *

class ServiceMelodie():
    def __init__(self,repo,valid):
        self.__repo=repo
        self.__valid=valid
        
    def addMelodie(self,melodie):
        self.__valid.validare(melodie)
        self.__repo.addMelodie(melodie)

    def modificaMelodie(self,artist,titlu,gen,durata):
        melodie=Melodie(artist,titlu,gen,durata)
        self.__valid.validare(melodie)
        self.__repo.modificaMelodie(artist,titlu,gen,durata)
        
    def addMelodiiRandom(self,nr):
        self.__repo.addMelodiiRandom(nr)
        
    def getListaMelodii(self):
        return self.__repo.getListaMelodii()