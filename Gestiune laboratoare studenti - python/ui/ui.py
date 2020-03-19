from domain.stud import Student
from domain.probLab import ProblemaLaborator
from service.service_student import ServiceStudent
from service.service_problemaLab import ServiceProblemaLab
from service.service_nota import ServiceNota
from validare.valid_student import ValidatorStudent
from validare.valid_problemaLab import ValidatorProblemaLab
from exceptii.exceptii import *

class Console:
    def __init__(self,service_student,service_problemaLab,service_nota):
        self.__service_student=service_student
        self.__service_problemaLab=service_problemaLab
        self.__service_nota=service_nota
        
    def __ui_addStudent(self):
        """
        Adauga studentul de la tastatura
        """
        while True:
            studID = input("Introduceți ID-ul studentului: ")
            nume = input("Introduceți numele studentului: ")
            grup = input("Introduceți grupul studentului: ")
            try:
                student=Student(studID,nume,grup)
                self.__service_student.creeaza(student)
                print("")
                print("Studentul a fost adăugat.")
                print("")
                break
            
            except ValidatorStudentException as ex:
                erori=ex.get_erori()
                print("")
                for i in range(len(erori)):
                    print(erori[i])
                print("")
            except RepositoryStudentException:
                print("")
                print("Există deja un student cu acest ID! Reintroduceți datele:")
                print("")   
    
    def __ui_deleteStudent(self):
        """
        Sterge un student
        """
        while True:
            studID = input("Introduceți ID-ul studentului: ")
            try:
                self.__service_student.sterge(studID)
                self.__service_nota.stergeNoteStudID(studID)
                print("")
                print("Studentul a fost șters cu succes!")
                print("")
                break
            except ValidatorStudentException as ex:
                erori=ex.get_erori()
                print("")
                for i in range(len(erori)):
                    print(erori[i])
                print("")
            except RepositoryStudentException:
                print("")
                print("Nu există un student cu acest ID!")
                print("")
            
    def __ui_modificaStudent(self):
        """
        Modifica un student
        """
        while True:
            studID = input("Introduceți ID-ul studentului: ")
            nume = input("Introduceți numele nou al studentului: ")
            grup = input("Introduceți grupul nou al studentului: ")
            try:
                self.__service_student.modifica(studID, nume, grup)
                print("")
                print("Student modificat cu succes!")
                print("")
                break
            except RepositoryStudentException:
                print("")
                print("Nu există un student cu acest ID!")
                print("")
            except ValidatorStudentException as ex:
                erori=ex.get_erori()
                print("")
                for i in range(len(erori)):
                    print(erori[i])
                print("")
         
    def __ui_cautaStudent(self):
        """
        Cauta un student in functie de ID
        """
        studID = input("Introduceți ID-ul studentului: ")
        try:
            print("")
            print("Studentul căutat este: ")
            print("")
            print(self.__service_student.cauta(studID))
        except ValidatorStudentException as ex:
                erori=ex.get_erori()
                print("")
                for i in range(len(erori)):
                    print(erori[i])
                print("")
        except RepositoryStudentException:
                print("")
                print("Nu există un student cu acest ID!")
                print("")
          
    def __ui_addProblemaLab(self):
        """
        Adauga problema de la tastatura
        """
        while True:
            nrLab=int(input('Introduceți numărul laboratorului: '))
            nrPb=int(input('Introduceți numărul problemei: '))
            NrLab_nrP=(nrLab,nrPb)
            descriere = input("Introduceți descrierea problemei: ")
            deadline = input("Introduceți deadline-ul problemei: ")
            try:
                self.__service_problemaLab.creeaza(NrLab_nrP, descriere, deadline)
                print("")
                print("Problema a fost adăugată.")
                print("")
                break
            except ValidatorProblemaLabException as ex:
                erori=ex.get_erori()
                print("")
                for i in range(len(erori)):
                    print(erori[i])
                print("")
            except RepositoryProbLabException:
                print("")
                print("Există deja o problemă de acest tip! Reintroduceți datele:")
                print("")   
    
    def __ui_deleteProblemaLab(self):
        """
        Sterge o problema
        """
        while True:
            nrLab=int(input('Introduceți numărul laboratorului: '))
            nrPb=int(input('Introduceți numărul problemei: '))
            NrLab_nrP=(nrLab,nrPb)
            try:
                self.__service_problemaLab.sterge(NrLab_nrP)
                self.__service_nota.stergeProbLab(NrLab_nrP)
                print("")
                print("Problema a fost ștearsă cu succes!")
                print("")
                break
            except ValidatorProblemaLabException as ex:
                erori=ex.get_erori()
                print("")
                for i in range(len(erori)):
                    print(erori[i])
                print("")
            except RepositoryProbLabException:
                print("")
                print("Nu există o problemă de acest tip!")
                print("")
            
    def __ui_modificaProblemaLab(self):
        """
        Modifica o problema
        """
        while True:
            nrLab=int(input('Introduceți numărul laboratorului: '))
            nrPb=int(input('Introduceți numărul problemei: '))
            NrLab_nrP=(nrLab,nrPb)
            descriere = input("Introduceți noua descriere a problemei: ")
            deadline = input("Introduceți noul deadline al problemei: ")
            try:
                self.__service_problemaLab.modifica(NrLab_nrP, descriere, deadline)
                print("")
                print("Problemă modificată cu succes!")
                print("")
                break
            except ValidatorProblemaLabException as ex:
                erori=ex.get_erori()
                print("")
                for i in range(len(erori)):
                    print(erori[i])
                print("")
            except RepositoryProbLabException:
                print("")
                print("Nu există o problemă de acest tip")
                print("")
         
    def __ui_cautaProblemaLab(self):
        """
        Cauta o problema in functie de NrLab_nrP
        """
        nrLab=int(input('Introduceți numărul laboratorului: '))
        nrPb=int(input('Introduceți numărul problemei: '))
        NrLab_nrP=(nrLab,nrPb)
        try:
            print("")
            print("Problema căutată este: ")
            print("")
            print(self.__service_problemaLab.cauta(NrLab_nrP))
        except ValidatorProblemaLabException as ex:
                erori=ex.get_erori()
                print("")
                for i in range(len(erori)):
                    print(erori[i])
                print("")
        except RepositoryProbLabException:
                print("")
                print("Nu există o problemă de acest tip!")
                print("")
     
    def  __ui_notareLaborator(self):
        """
        Asigneaza nota studentului cu laboaratorul/problema sa
        """
        while True:
            studID = input("Introduceți ID-ul studentului: ")
            nrLab=int(input('Introduceți numărul laboratorului: '))
            nrPb=int(input('Introduceți numărul problemei: '))
            nrLab_nrPb=(nrLab,nrPb)
            nota = int(input("Introduceți nota studentului: "))
            try:
                self.__service_nota.notare(studID,nrLab_nrPb,nota)
                print("")
                print("Nota a fost asignată.")
                print("")
                break
            except ValidatorStudentException as ex:
                erori=ex.get_erori()
                print("")
                for i in range(len(erori)):
                    print(erori[i])
                print("")
            except RepositoryStudentException:
                print("")
                print("A fost deja asignată o notă! Reintroduceți datele:")
                print("")   
                
    def __ui_create_random_students(self):
        number_of_students=int(input("Introduceți numărul de studenți: "))
        self.__service_student.create_random_students(number_of_students)
        print("")
        print("Studenții au fost generați.")
        print("")
        
    def __ui_StudentiOrdonati(self):
        ordonat=self.__service_nota.get_list_ord()
        if(len(ordonat)==0):
            print("Nu există studenți cu note!")
        else:
            print("")
            print("Studenții ordonați alfabetic sunt: ")
            print("")
            for i in ordonat:
                print(i)
        
    def __ui_StudentiRestantieri(self):
        rest=self.__service_nota.get_rest()
        if(len(rest)==0):
            print("Nu există restanțieri!")
        else:
            print("")
            print("Studenții cu media notelor de laborator mai mică decât 5 sunt: ")
            print("")
            print(rest)
            
    def __ui_raportMedieGrupe(self):
        note_grupe=self.__service_nota.get_medii_grupa()
        print("Mediile notelor pentru fiecare grupa sunt: ")
        for grupa in note_grupe:
            print('Grupa: {}, Medie: {}'.format(str(grupa),str(note_grupe[grupa])))
            
    def __ui_sortare_lista(self):
        numeLista=input("Introduceti numele listei pe care doriti sa o sortati - studenti, probleme sau note: ")
        try:
            if numeLista=="studenti":
                self.__service_student.sorteaza_studenti()
            elif numeLista=="probleme":
                self.__service_problemaLab.sorteaza_probleme()
            elif numeLista=="note":
                self.__service_nota.sorteaza_note()
            print("")
            print("Lista a fost sortată cu succes!")
            print("")
        except ValueError as ve:
            print(str(ve))       
                
    def __ui_afisare_liste_complete(self):
        lista_studenti=self.__service_student.get_studenti()
        print("")
        if len(lista_studenti)==0:
            print("Nu există studenti!")
        else:
            print('Lista completă de studenți este: ')
        for student in lista_studenti:
            print('ID student: {}, Nume student: {}, Grup: {}'.format(student.getStudentID(),student.getNume(),student.getGrup()))
        print("")
        
        lista_probleme=self.__service_problemaLab.get_problemeLab()
        if len(lista_probleme)==0:
            print("Nu există probleme!")
        else:
            print('Lista completă de probleme este:\n')
        for problema in lista_probleme:
            print('NrLab_nrP: {}, Descriere: {}, Deadline: {}'.format(problema.getNrLab_nrPb(),problema.getDescriere(),problema.getDeadline()))
        print("")
        
        lista_note=self.__service_nota.get_note()
        if len(lista_note)==0:
            print("Nu există note!")
        else:
            print('Lista completă de note este:\n')
        for nota in lista_note:
            print('ID student: {}, NrLab_nrPb: {}, Nota: {}'.format(nota.getStudentID(),nota.getNrLab_nrPb(),nota.getNota()))
        print("") 
           
    def run(self):
        while True:  
            meniu='''
             Listă opțiuni:
             0: Ieșire din aplicație
             1: Adăugare student
             2: Ștergere student
             3: Modificare student
             4: Căutare student
             5: Adăugare problemă
             6: Ștergere problemă
             7: Modificare problemă
             8: Căutare problemă
             9: Notare laborator
            10: Studenții ordonați alfabetic după nume, după notă
            11. Studenții restanțieri
            12: Afișare liste complete
            13. Raport medie grupe
            14: Generare studenți random
            15: Sortare lista
            '''
            print(meniu)
            
            self.__comenzi ={
            "1":self.__ui_addStudent,
            "2":self.__ui_deleteStudent,
            "3":self.__ui_modificaStudent,
            "4":self.__ui_cautaStudent,
            "5":self.__ui_addProblemaLab,
            "6":self.__ui_deleteProblemaLab,
            "7":self.__ui_modificaProblemaLab,
            "8":self.__ui_cautaProblemaLab,
            "9":self.__ui_notareLaborator,
            "10":self.__ui_StudentiOrdonati,
            "11":self.__ui_StudentiRestantieri,
            "12":self.__ui_afisare_liste_complete,
            "13":self.__ui_raportMedieGrupe,
            "14":self.__ui_create_random_students,
            "15":self.__ui_sortare_lista
            }
            comanda=input("Introduceți o opțiune de la 0 la 15: ")
            if comanda in self.__comenzi:
                try:
                    self.__comenzi[comanda]()
                except ValueError as ve:
                    print(str(ve))
            elif comanda=="0":
                print("Ați părăsit aplicația!")
                return
            else:
                print("Comandă invalidă!")
