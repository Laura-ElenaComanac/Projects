from domain.stud import Student
from domain.probLab import ProblemaLaborator
from domain.notaStud import NotaStudent
from validare.valid_nota import ValidatorNota
from repository.repo_student import RepositoryStudent
from repository.repo_nota import RepositoryNota
import repository
#from builtins import True

class DTO():
    
    def __init__(self,nume,medie):
        self.__nume=nume
        self.__medie=medie
      
    '''  
    def get_medie(self):
        return self.__medie
    
    def get_nume(self):
        return self.__nume
    '''
    
    @property
    def nume(self):
        return self.__nume
    
    @nume.setter
    def nume(self,value):
        self.nume=value
        
    @property
    def medie(self):
        return self.__medie
    
    @medie.setter
    def medie(self,value):
        self.medie=value
    
    def __lt__(self,other):
        if self.nume<other.nume:
            return True
        elif self.nume==other.nume and self.medie<other.medie:
            return True
        else:
            return False
    
    def __repr__(self):
        return "Nume student: %s, Medie student: %d\n" % (self.__nume,self.__medie)

class ServiceNota():
    
    def __init__(self,repoNota,validNota,repoStud,repoProbLab):
        """
          Initializeaza service
          repoNota - GradeRepository
          validNota - GradeValidator
          repoStud - StudentRepository
        """
        self.__repoNota = repoNota
        self.__validNota = validNota
        self.__repoStud = repoStud
        self.__repoProbLab =repoProbLab

    def notare(self,studID,nrLab_nrPb,nota):
        """
        Asigneaza o nota unui student pentru un laborator si o problema data
        studID String, ID-ul studentului
        NrLab_nrPb Integer, numar lab/numar problema
        nota Integer, nota studentului
        post: nota e retinuta
        returneaza nota
        """
        #cauta student
        student = self.__repoStud.cautaStudent(studID)
        #cauta problema
        problemaLab = self.__repoProbLab.cautaProblemaLab(nrLab_nrPb)
        #creeaza obiectul nota
        notaStud = NotaStudent(student.getStudentID(),problemaLab.getNrLab_nrPb(),nota)
        #valideaza nota
        self.__validNota.validate(studID,nrLab_nrPb,nota)
        #retine nota in repo
        self.__repoNota.addNota(notaStud)
        return notaStud

    def get_note(self):
        """
        Returneaza lista tuturor notelor din sistem
        """
        return self.__repoNota.getListaNote()
    
    '''
    def sortare(self,rez):
        i=j=0
        while i<=len(rez):
            while j<=len(rez):
                if rez[i][0]>rez[j][0]:
                    aux =rez[i]
                    rez[i]=rez[j]
                    rez[j]=aux
                elif rez[i][0]==rez[j][0] and rez[i][1]>rez[j][1]:
                    aux =rez[i]
                    rez[i]=rez[j]
                    rez[j]=aux
                j+=1
        i+=1
        return rez         
    '''
    
    def get_list_ord(self):
        """
        Returneaza lista tuturor studentilor cu nume si nota, ordonata alfabetic după nume, după notă.
        """
        situatie={}
        note=self.__repoNota.getListaNote()
        for nota in note: 
            studID=nota.getStudentID()
            if studID not in situatie:
                listaStudentNote=self.__repoNota.getAll(studID)
                situatie.update({studID:listaStudentNote})
        rez=[] #lista de tupluri
        for item in situatie.items():
            studID=item[0]
            studNote=item[1]
            student=self.__repoStud.cautaStudent(str(studID))
            stud=DTO(student.getNume(),sum(studNote)/len(studNote))
            rez.append(stud)
        #print(rez)
        #self.sortare(rez)
        rez.sort()
        return rez
    
    #def get_list_ord_2(self):
        
        
    def get_rest(self):
        """
        Returneaza lista tuturor studentilor cu media notelor de laborator mai mica decat 5
        """
        situatie={}
        note=self.__repoNota.getListaNote()
        for nota in note: 
            studID=nota.getStudentID()
            if studID not in situatie:
                listaStudentNote=self.__repoNota.getAll(studID)
                situatie.update({studID:listaStudentNote})
        rez=[]
        for item in situatie.items():
            studID=item[0]
            studNote=item[1]
            student=self.__repoStud.cautaStudent(str(studID))
            rest=DTO(student.getNume(),sum(studNote)/len(studNote))
            rez.append(rest)
        listaRest=[]
        for x in rez:
            if x.medie<5:
                listaRest.append(x)
        return listaRest
        #return [x for x in rez if x.get_media()<5]
        
    def get_medii_grupa(self):
        """
        Returneaza lista cu mediile pt fiecare grupa
        """
        note_grupe={}
        grupe=self.__repoStud.get_grupe()
        for i in grupe:
            note_grupe[i]=[]
        for i in self.__repoNota.getListaNote():
            grupa=str(self.__repoStud.get_grupa(i.getStudentID()))
            note_grupe[grupa].append(int(i.getNota()))    
        for i in grupe:
            note_grupe[i]=sum(note_grupe[i])/len(note_grupe[i])
        return note_grupe
    
    def stergeNoteStudID(self,studID):
        i=0
        n=self.__repoNota.size_lista_note()
        while i<n:
            nota=self.__repoNota.get_element(i)
            if str(studID)==str(nota.getStudentID()):
                self.__repoNota.deleteNota(nota)
                n=n-1
            else:
                i=i+1
                
    def stergeNoteProbLab(self,ProbLab):
        i=0
        n=self.__repoNota.size_lista_note()
        while i<n:
            nota=self.__repoNota.get_element(i)
            if ProbLab==nota.getNrLab_nrPb():
                self.__repoNota.getListaNote().deleteNota(nota)
                n=n-1
            else:
                i=i+1  
                
    def sorteaza_note(self):
        self.__repoNota.sorteaza_note()
        
            