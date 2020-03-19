from repository.repo_student import *
from repository.repo_problemaLab import *
from repository.repo_nota import *
from service.service_student import ServiceStudent
from service.service_problemaLab import ServiceProblemaLab
from service.service_nota import ServiceNota
from tests.teste_student import TesteStudent
from tests.teste_problemaLab import TesteProblemaLab
#from tests.teste_nota import TesteNota
from ui.ui import Console
from validare.valid_student import ValidatorStudent
from validare.valid_problemaLab import ValidatorProblemaLab
from validare.valid_nota import ValidatorNota
from domain.stud import Student
from domain.probLab import ProblemaLaborator
from domain.notaStud import NotaStudent

"""
testeStud=TesteStudent()
testeProbLab=TesteProblemaLab()
testeNota=TesteNota()
testeStud.ruleaza_teste()
testeProbLab.ruleaza_teste()
testeNota.ruleaza_teste()
"""
repoStud=FileRepositoryStudent("studenti.txt",Student.read_student,Student.write_student)
repoProbLab=FileRepositoryProblemaLab("probleme.txt",ProblemaLaborator.read_problemaLab,ProblemaLaborator.write_problemaLab)
repoNota=FileRepositoryNota("note.txt",NotaStudent.read_nota,NotaStudent.write_nota)
validStud=ValidatorStudent()
validProbLab=ValidatorProblemaLab()
validNota=ValidatorNota()
serviceStud=ServiceStudent(repoStud,validStud)
serviceProbLab=ServiceProblemaLab(repoProbLab,validProbLab)
serviceNota=ServiceNota(repoNota,validNota,repoStud,repoProbLab)
ui=Console(serviceStud,serviceProbLab,serviceNota)

ui.run()

