from exceptii.exceptii import ValidatorStudentException

class ValidatorNota():
    
    def __init__(self):
        pass
    
    def validate_id(self,studID):
        erori=[] 
        if studID=="": 
            erori.append("ID-ul nu poate fi vid!")
        elif studID.isalpha() or int(studID)<0:
            erori.append("ID invalid!")        
    
    def validate(self, studID, nrLab_nrPb, nota):
        erori=[] 
        if studID=="": 
            erori.append("ID-ul nu poate fi vid!")
        elif studID.isalpha() or int(studID)<0:
            erori.append("Id invalid!")
            
        if nrLab_nrPb=="": 
            erori.append("Problema nu poate fi vidă!")
        elif nrLab_nrPb[0]<0 or nrLab_nrPb[1]<0:
            erori.append("Problemă invalidă!")    
            
        if nota=="":
            erori.append("Nota nu poate fi vidă!")
        elif nota<=0 or nota>10:
            erori.append("Notă invalidă!")
            
        if len(erori)>0:
            raise ValidatorStudentException(erori)
        