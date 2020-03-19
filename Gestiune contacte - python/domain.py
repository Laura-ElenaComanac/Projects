class Contact():
    def __init__(self,id,nume,nrTelefon,grup):
        self.__id=id
        self.__nume=nume
        self.__nrTelefon=nrTelefon
        self.__grup=grup
        
    def getId(self):
       return self.__id
   
    def getNume(self):
        return self.__nume
        
    def getNrTelefon(self):
        return self.__nrTelefon
    
    def getGrup(self):
        return self.__grup
    
    """
    def __equ__(self,other):
        return self.__nume==other.__nume
    """
    
    def __repr__(self):
        return "Id: %s, Nume: %s, Nr Telefon: %s, Grup: %s\n"%(self.__id,self.__nume,self.__nrTelefon,self.__grup)
    
    @staticmethod
    def read(line):
        parts=line.split(",")
        return Contact(parts[0].strip(),parts[1].strip(),parts[2].strip(),parts[3].strip())
    
    @staticmethod
    def write(obj):
        return str(obj.__id)+", "+str(obj.__nume)+", "+str(obj.__nrTelefon)+", "+str(obj.__grup)
    
