class ProblemaLaborator():
    
    def __init__(self, nrLab_nrPb, descriere, deadline):
        # nrLab_nrPb este un t-uplu in care primul element este nr. laboratorului si al doilea este nr. problemei
        self.__nrLab_nrPb=nrLab_nrPb
        self.__descriere=descriere
        self.__deadline=deadline
        
    def __repr__(self):
        return " nrLab_nrPb: %d_%d\n Descriere: %s\n Deadline: %s\n" % (self.__nrLab_nrPb[0],self.__nrLab_nrPb[1],self.__descriere,self.__deadline)
        
    def getNrLab_nrPb(self):
        return self.__nrLab_nrPb
    
    def setNrLab_nrPb(self, nrLab_nrPb):
        self.__nrLab_nrPb=nrLab_nrPb
        
    def getDescriere(self):
        return self.__descriere
    
    def setDescriere(self, descriere):
        self.__descriere=descriere
        
    def getDeadline(self):
        return self.__deadline
    
    def setDeadline(self, deadline):
        self.__deadline=deadline 
        
    def __eq__(self,other):
        return self.__nrLab_nrPb == other.__nrLab_nrPb
    
    def __lt__(self,other):
        return self.__nrLab_nrPb < other.__nrLab_nrPb
    
    def __gt__(self,other):
        return self.__nrLab_nrPb > other.__nrLab_nrPb
    
    @staticmethod
    def read_problemaLab(line):
        parts = line.split(",")
        return ProblemaLaborator((int(parts[0].strip()),int(parts[1].strip())),str(parts[2].strip()),str(parts[3].strip()))
    
    @staticmethod
    def write_problemaLab(problemaLab):
        return str(problemaLab.__nrLab_nrPb)+", "+str(problemaLab.__descriere)+", "+str(problemaLab.__deadline)
    
    
