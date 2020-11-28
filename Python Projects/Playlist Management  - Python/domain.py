class Melodie():
    def __init__(self,titlu,artist,gen,durata):
        self.__titlu=titlu
        self.__artist=artist
        self._gen=gen
        self._durata=durata
        
    def __repr__(self):
        return "Titlu: %s, Artist: %s, Gen: %s, Durata: %d" %(self.__titlu,self.__artist,self._gen,self._durata)
        
    def getTitlu(self):
        return self.__titlu
    
    def getArtist(self):
        return self.__artist
    
    def getGen(self):
        return self._gen
    
    def getDurata(self):
        return self._durata
    
    def setGen(self,gen):
        self._gen=gen
        
    def setDurata(self,durata):
        self._durata=durata
    
    def __equ__(self,other):
        return self.__titlu==other.__titlu and self.__artist==other.__artist
    
    @staticmethod
    def read(line):
        parts =line.split(', ')
        return Melodie(parts[0].strip(),parts[1].strip(),parts[2].strip(),int(parts[3].strip()))
    
    @staticmethod
    def write(obj):
        return str(obj.__titlu)+", "+str(obj.__artist)+", "+str(obj._gen)+", "+str(obj._durata)

