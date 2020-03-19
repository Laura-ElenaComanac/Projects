class ExceptiiValidatorMelodie(Exception):
    def __init__(self,erori):
        self.__erori=erori
    
    def getErori(self):
        return self.__erori
    
    def __str__(self):
        return str(self.__erori)
    
class Validator():
    def __init__(self):
        pass
    
    def validare(self,melodie):
        erori=[]
        #print(melodie.getDurata())
        if melodie.getDurata()<0 or melodie.getDurata()!=int(melodie.getDurata()):
            erori.append("durata nu e valida!")
        if melodie.getGen() not in ["Rock","Pop","Jazz","Altele"]:
            erori.append("genul nu e valid!")
        if len(erori)>0:
            raise ExceptiiValidatorMelodie(erori)