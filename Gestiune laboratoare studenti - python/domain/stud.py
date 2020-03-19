class Student():
    
    def __init__(self, studentID, nume, grup):
        self.__studentID=studentID
        self.__nume=nume
        self.__grup=grup
        
    def __repr__(self):
        return " ID student: %s\n Nume student: %s\n Grup student: %s\n" % (self.__studentID,self.__nume,self.__grup)
        
    def getStudentID(self):
        return self.__studentID
    
    def setStudentID(self, studentID):
        self.__studentID=studentID
        
    def getNume(self):
        return self.__nume
    
    def setNume(self, nume):
        self.__nume=nume
        
    def getGrup(self):
        return self.__grup
    
    def setGrup(self, grup):
        self.__grup=grup
      
    def __eq__(self,other):
        return self.__studentID == other.getStudentID()
    
    def __gt__(self,other):
        return int(self.__studentID)>int(other.__studentID)
    
    def __lt__(self,other):
        return int(self.__studentID)<int(other.__studentID)
    
    @staticmethod
    def read_student(line):
        parts = line.split(",")
        return Student(parts[0].strip(),parts[1].strip(),parts[2].strip())
    
    @staticmethod
    def write_student(student): 
        return str(student.__studentID)+", "+str(student.__nume)+", "+str(student.__grup)
    
    
