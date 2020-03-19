from domain import *
from exceptii import *
from random import choice

class RepositoryMelodie():
    def __init__(self):
        self._lista_melodii=[]
        
    def getListaMelodii(self):
        return self._lista_melodii
    
    def addMelodie(self,melodie):
        for mel in self._lista_melodii:
            if mel.getArtist()==melodie.getArtist() and mel.getTitlu()==melodie.getTitlu():
                raise ExceptiiMelodie("melodie deja existenta")
        self._lista_melodii.append(melodie)
    
    def modificaMelodie(self,artist,titlu,gen,durata):
        nr=0
        for melodie in self._lista_melodii:
            if melodie.getArtist()==artist and melodie.getTitlu()==titlu:
                melodie.setGen(gen)
                melodie.setDurata(durata)
                nr=nr+1
        if nr==0:
            raise ExceptiiMelodie("nu exista melodia!")
        
    def addMelodiiRandom(self,nr):
        lista_titluri=[]
        lista_artisti=[]
        lista_genuri=[]
        lista_durate=[]
        genuri=["Rock","Pop","Jazz","Altele"]
        consoane=range(ord("a"),ord("z"))
        consoane=list(consoane)
        vocale=[]
        v="aeiou"
        for i in v:
            vocale.append(ord(i))
            consoane.remove(ord(i))
        for j in range (0,nr):
            cuvant1=""
            cuvant2=""
            for i in range(0,8):
                if i==3:
                    cuvant1+=" "
                    cuvant2+=" "
                else:
                    if i%2==0:
                        cuvant1+=chr(choice(consoane))
                        cuvant2+=chr(choice(consoane))
                    else:
                        cuvant1+=chr(choice(vocale))
                        cuvant2+=chr(choice(vocale))
            lista_titluri.append(cuvant1)
            lista_artisti.append(cuvant2)
            lista_genuri.append(choice(genuri))
            lista_durate.append(choice(list(range(0,600))))
        print("melodiile random sunt: ")
        for j in range (0,nr):
            titlu=lista_titluri[j]
            artist=lista_artisti[j]
            gen=lista_genuri[j]
            durata=lista_durate[j]
            melodie=Melodie(titlu,artist,gen,durata)
            print("")
            print(melodie)
            print("")
            self._lista_melodii.append(melodie)
        
class FileRepositoryMelodie():
    def __init__(self,filename,read,write):
        RepositoryMelodie.__init__(self)
        self.__filename=filename
        self.__read=read
        self.__write=write
        
    def read_all_from_file(self):
        self._lista_melodii=[]
        with open(self.__filename,"r") as file:
            lines=file.readlines()
            for line in lines:
                line=line.strip()
                if line!="":
                    obj=self.__read(line)
                    self._lista_melodii.append(obj)
                    
    def write_all_to_file(self):
        with open(self.__filename,"w") as file:
            for obj in self._lista_melodii:
                line=self.__write(obj)
                file.write(line+'\n')
                
    def addMelodie(self,melodie):
        self.read_all_from_file()
        RepositoryMelodie.addMelodie(self, melodie)
        self.write_all_to_file()
        
    def modificaMelodie(self,artist,titlu,gen,durata):
        self.read_all_from_file()
        RepositoryMelodie.modificaMelodie(self,artist,titlu,gen,durata)
        self.write_all_to_file()
        
    def addMelodiiRandom(self,nr):
        self.read_all_from_file()
        RepositoryMelodie.addMelodiiRandom(self, nr)
        self.write_all_to_file()
        
    def getListaMelodii(self):
        self.read_all_from_file()
        return RepositoryMelodie.getListaMelodii(self)
        
        
        
        
        
    
