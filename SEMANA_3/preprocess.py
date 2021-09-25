import re
myfile = open('CF_text_1.txt', encoding='utf-8')
dato = myfile.read()
dato = list(dato)
myfile.close()

# Substitution of following characters: j x i, h x i, ñ x n, k x l, u x v, w x v, y x z
def removeLetters():
    for x in range(len(dato)):
        if(dato[x] == 'j' or dato[x] == 'h' ):
            dato[x] = 'i'
        elif(dato[x] == 'ñ'):
            dato[x] = 'n'
        elif(dato[x] == 'k'):
            dato[x] = 'l'
        elif(dato[x] == 'u' or dato[x] == 'w'):
            dato[x] = 'v'
        elif(dato[x] == 'y'):
            dato[x] = 'z'
def removeAccents():
    accents = ['á','é','í','ó','ú']
    notAcents = ['a','e','i','o','u']
    for x in range(len(dato)):
        for y in range(len(accents)):
            if( dato[x] == accents[y]):
                dato[x] = notAcents[y] 

def convertToUpper(dato):
    
    # print(arreglo)
    dato = "".join(dato)
    dato = dato.upper()
    dato = list(dato)
    return dato

def removePuntuationSigns(dato):
    
    dato = "".join(dato)
    dato = re.sub(r'[^\w\s]', '', dato)
    dato = list(dato)
    return dato
def removeSpaceLineBreaks(dato):
    
    dato = "".join(dato)
    dato = re.sub(r'[\n\s]', '', dato)
    dato = list(dato)
    return dato

removeLetters()
removeAccents()
dato = convertToUpper(dato)
dato = removePuntuationSigns(dato)
dato = removeSpaceLineBreaks(dato)


dato = "".join(dato)
print(dato)

with open('Pre_CF_text_1.txt', 'w') as f:
    f.write(dato)