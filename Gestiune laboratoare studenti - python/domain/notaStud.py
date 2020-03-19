class NotaStudent():
    
    def __init__(self, studentID, nrLab_nrPb, nota):
        # nrLab_nrPb este un t-uplu in care primul element este nr. laboratorului si al doilea este nr. problemei
        self.__studentID=studentID
        self.__nrLab_nrPb=nrLab_nrPb
        self.__nota=nota
        self.__nume=None
    
    def __repr__(self):
        return " studentID: %d\n nrLab_nrPb: %d_%d\n nota: %d\n" % (self.__studentID,self.__nrLab_nrPb[0],self.__nrLab_nrPb[1],self.__nota)
    
    def getStudentID(self):
        return self.__studentID
    
    def setStudentID(self, studentID):
        self.__nume=studentID
        
    def getNrLab_nrPb(self):
        return self.__nrLab_nrPb
    
    def setNrLab_nrPb(self, nrLab_nrPb):
        self.__nrLab_nrPb=nrLab_nrPb
        
    def getNota(self):
        return self.__nota
    
    def setNota(self, nota):
        self.__nota=nota 
        
    def getNumeStudent(self):
        return self.__nume
    
    def setNumeStudent(self, nume):
        self.__nume=nume
        
    def __eq__(self,other):
        return self.__studentID == other.__studentID and self.__nrLab_nrPb == other.__nrLab_nrPb
    
    def __lt__(self,other):
        return self.__nota< other.__nota
    
    def __gt__(self,other):
        return self.__nota > other.__nota
    
    @staticmethod
    def read_nota(line):
        parts = line.split(",")
        return NotaStudent(int(parts[0].strip()), (int(parts[1].strip()),int(parts[2].strip())), int(parts[3].strip()))
    
    @staticmethod
    def write_nota(notaStud):
        return str(notaStud.__studentID)+", "+str(notaStud.__nrLab_nrPb)+", "+str(notaStud.__nota)
    
    
