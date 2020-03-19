from domain import *
from exceptii import *

class ValidareContact():
    def __init__(self):
        pass
    
    def valid(self,contact):
        erori=[]
        if contact.getNume()=="":
            erori.append("numele nu poate fi vid!")
        if contact.getGrup() not in ["Prieteni","Familie","Job","Altele"]:
            erori.append("grup invalid!")
        if contact.getNrTelefon()=="" or not contact.getNrTelefon().isdigit():
            erori.append("numar de telefon invalid!")
        if len(erori)>0:
            raise ExceptiiValidare(erori)
    

