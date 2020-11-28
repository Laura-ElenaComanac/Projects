class Jucator():
    def __init__(self,nume,prenume,inaltime,post):
        self.__nume=nume
        self.__prenume=prenume
        self.__inaltime=inaltime
        self.__post=post
    
    def __repr__(self):
        return "Nume: %s, Prenume: %s, Inaltime: %d, Post: %s"%(self.__nume,self.__prenume,self.__inaltime,self.__post)
    
    def getNume(self):
        return self.__nume
    
    def getPrenume(self):
        return self.__prenume
    
    def getInaltime(self):
        return self.__inaltime
    
    def getPost(self):
        return self.__post
    
    def setInaltime(self,inaltime):
        self.__inaltime=inaltime
    
    def __eq__(self,other):
        return self.__nume==other.__nume and self.__prenume==other.__prenume
    
    @staticmethod
    def read(line):
        parts=line.split(", ")
        return Jucator(parts[0].strip(),parts[1].strip(),int(parts[2].strip()),parts[3].strip())
    
    @staticmethod
    def write(obj):
        return str(obj.__nume)+", "+str(obj.__prenume)+", "+str(obj.__inaltime)+", "+str(obj.__post)
        


