from exceptii.exceptii import ValidatorStudentException  

class ValidatorStudent():
    
    def __init__(self):
        pass
    
    def validate_id(self,studID):
        erori=[] 
        if studID=="": 
            erori.append("ID-ul nu poate fi vid!")
        elif studID.isalpha() or int(studID)<0:
            erori.append("ID invalid!")        
    
    def validate(self, student):
        erori=[] 
        if student.getStudentID()=="": 
            erori.append("ID-ul nu poate fi vid!")
        elif student.getStudentID().isalpha() or int(student.getStudentID())<0:
            erori.append("Id invalid!")
            
        if student.getNume()=="":
            erori.append("Numele nu poate fi vid!")
        elif student.getNume().isdigit():
            erori.append("Nume invalid!")
            
        if student.getGrup()=="":
            erori.append("Grupul nu poate fi vid!")
        elif student.getGrup().isalpha() or int(student.getStudentID())<0:
            erori.append("Grup invalid!")
        
        if len(erori)>0:
            raise ValidatorStudentException(erori)

    

