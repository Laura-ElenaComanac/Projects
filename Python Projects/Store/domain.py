class Produs():
    def __init__(self,id,denumire,pret):
        self.__id=id
        self.__denumire=denumire
        self.__pret=pret
        
    def __repr__(self):
        return "Id: %s, Denumire: %s, Pret: %s\n"%(self.__id,self.__denumire,self.__pret)
        
    def getId(self):
        return self.__id
    
    def getDenumire(self):
        return self.__denumire
    
    def getPret(self):
        return self.__pret
    
    @staticmethod
    def read(line):
        parts=line.split(", ")
        return Produs(parts[0],parts[1],parts[2])
    
    @staticmethod
    def write(obj):
        return str(obj.__id)+", "+ str(obj.__denumire)+", "+ str(obj.__pret)


