from exceptii.exceptii import ValidatorProblemaLabException

class ValidatorProblemaLab():
    
    def __init__(self):
        pass
    
    def validate_nr(self,nrLab_nrPb):
        erori=[] 
        if nrLab_nrPb=="": 
            erori.append("Problema nu poate fi vidă!")
        elif nrLab_nrPb[0]<0 or nrLab_nrPb[1]<0:
            erori.append("Problemă invalidă!")        
    
    def validate(self, nrLab_nrPb,descriere,deadline):
        erori=[] 
        if nrLab_nrPb=="": 
            erori.append("Problema nu poate fi vidă!")
        elif nrLab_nrPb[0]<0 or nrLab_nrPb[1]<0:
            erori.append("Problemă invalidă!")  
            
        if descriere=="":
            erori.append("Descrierea nu poate fi vidă!")
        elif descriere.isdigit():
            erori.append("Descriere invalidă!")
            
        if deadline=="":
            erori.append("Deadline-ul nu poate fi vid!")
        elif deadline.isdigit():
            erori.append("Deadline invalid!")
        
        if len(erori)>0:
            raise ValidatorProblemaLabException(erori)
