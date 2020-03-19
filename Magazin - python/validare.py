from domain import *
from exceptii import *

class ValidMagazin():
    def __init__(self):
        pass
    
    def valid(self,produs):
        erori=[]
        if produs.getId()=="":
            erori.append("id invalid!")
        if produs.getDenumire()=="":
            erori.append("denumire invalida!")
        if produs.getPret()=="":
            erori.append("pret invalid!")
        if len(erori)>0:
            raise ExceptiiValidare(erori)


