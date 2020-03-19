from domain import *
from exceptii import *

class ValidareJucator():
    def __init__(self):
        pass
    
    def validare(self,jucator):
        erori=[]
        if jucator.getNume()=="":
            erori.append("Numele nu poate fi vid!")
        if jucator.getPrenume()=="":
            erori.append("Prenumele nu poate fi vid!")
        if jucator.getPost() not in ["Fundas","Pivot","Extrema"]:
            erori.append("Post invalid!")
        if int(jucator.getInaltime())<0:
            erori.append("Inaltime invalida!")
        if len(erori)>0:
            raise ExceptiiValidare(erori)


