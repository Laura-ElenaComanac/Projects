class ExceptiiRepository(Exception):
    pass

class ExceptiiValidare(Exception):
    def __init__(self,erori):
        self.__erori=erori
        
    def getErori(self):
        return self.__erori
    
    def __str__(self):
        return str(self.__erori)
