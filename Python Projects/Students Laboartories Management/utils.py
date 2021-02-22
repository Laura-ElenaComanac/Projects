def cmp(a,b):
    if a>b:
        return 1
    else:
        return 0

def BubbleSort(lista,cmp,reverse,key=lambda x:x):
    if reverse==False:
        ord=1
        #crescator
    else:
        ord=0
    sortat=False
    while not sortat:
        sortat=True
        for i in range(1,len(lista)):
            if cmp(key(lista[i-1]),key(lista[i]))==ord:
                lista[i-1], lista[i] = lista[i], lista[i-1]
                sortat=False
                
def ShellSort(lista):
    gap = len(lista) // 2
    while gap > 0:
        for i in range(gap, len(lista)):
            temp = lista[i]
            j = i
            while j >= gap and lista[j - gap] > temp:
                lista[j] = lista[j - gap]
                j -= gap
            lista[j] = temp
        gap //= 2