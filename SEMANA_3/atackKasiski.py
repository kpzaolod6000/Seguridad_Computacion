import math
import string

#Definir alfabeto 
def listAlphabet(chooseMod):
    if chooseMod == 27:
        alphabet = list(string.ascii_uppercase)
        alphabet.insert(14,'Ñ')
        return alphabet  
    elif chooseMod == 191:
        file = open('TableASCII191.txt', encoding='utf-8')
        alphabet = file.read()
        alphabet = list(alphabet)
        # print(data)
        file.close()

        return alphabet


#Frecuencia de letras
def Letterfrecuency(encrypt,mod_):
    alphabet = listAlphabet(mod_)
    freqAlph = {}
    for item in alphabet:
        freqAlph[item] = 0

    for item in encrypt:
        if (item in freqAlph):
            freqAlph[item] += 1
    return freqAlph

#CIFRADO DE VIGNERE
def getTextKey(data,key):
    
    keyText = [] 

    iClv = 0
    for i in range(len(data)):
        if(i%len(key) == 0):
            iClv = 0
        keyText.append(key[iClv])
        iClv += 1
    return keyText

#CIFRADO DE VIGNERE
def getAutoclave(data,key):
    
    keyText = [] 

    iClv = 0
    for i in range(len(key)):
        keyText.append(key[i])
    
    for i in range(len(data)-len(key)):
        keyText.append(data[i])

    return keyText


def getEncrypt(data,key,mod_): #ci = mi + ki mod n
    encrypt = data.copy()
    alphabet = listAlphabet(mod_)
    keyText = getTextKey(data,key)
    # print(keyText)

    n = len(alphabet)

    for i in range(len(data)):
        indexDt = alphabet.index(data[i])
        indexKy = alphabet.index(keyText[i])
        sumKey = indexDt + indexKy
        newKey = sumKey % n

        encrypt[i] = alphabet[newKey]
    return encrypt

def getDecryption(data,encrypt,key,mod_):
    decryption = encrypt.copy()
    alphabet = listAlphabet(mod_)
    keyText = getTextKey(data,key)

    n = len(alphabet)

    for i in range(len(encrypt)):
        indexDt = alphabet.index(encrypt[i])
        indexKy = alphabet.index(keyText[i])
        restKey = indexDt - indexKy
        charReal = restKey % n

        decryption[i] = alphabet[charReal]
    return decryption



#ATACK KASISKI
#================================================================================================================================
def findTrigrams(data,long_key):
    trigrams = []
    dicc = {}
    diccPosition = {}
    for i in range(len(data)-(long_key-1)):
        cont = i
        while cont < i+long_key:
            trigrams.append(data[cont])
            cont += 1
        text_ = "".join(trigrams)
        dicc[text_] = 0
        diccPosition[text_] = []
        trigrams = []

   

    for i in range(len(data)-(long_key-1)):   
        cont = i
        while cont < i+long_key:
            trigrams.append(data[cont])
            cont += 1

        # print(d1[x])
        # for first, second in dicc.items():

        for first in dicc:
            isEqual = True
            index = first # para definir el tipo de dato
            
            for x in range(len(first)):
                if trigrams[x] != first[x]:
                    isEqual = False
                    index = first
            if isEqual == True:
                dicc[index] += 1 
                diccPosition[index].append(i)
        trigrams = []
    return dicc, diccPosition


#MCD
def mcd(n1,n2):
    if n1<n2:
        i=n1
    else:
        i=n2
    while not (n1 % i == 0 and n2 % i == 0):
        i -= 1
    else:
        return i 
def mcd_n(n):
    numeros = list(n)
    resultado = mcd(numeros[0], numeros[1])
    if len(numeros) > 2:
        for n in numeros[2:]:
            resultado = mcd(resultado, n)
    return math.fabs(resultado)
   
def findLongMCD(dicc,diccPosition):

    listLong = []
    mcd = 0
    for first in dicc:
        if (dicc[first] > 1):
            print(first," -> ", dicc[first], ": index -> ",  diccPosition[first] , ": distancias -> ( ", end=' ')
            
            for x in range(len(diccPosition[first])-1):
                value = diccPosition[first][x+1] - diccPosition[first][x] 
                print(value, end=' ')
                listLong.append(value)
            print(')')
    print("\nLongitud: L = mcd(",listLong,") = ",end=' ')
    mcd = mcd_n(listLong)
    # for x, y in dicc.items():
    #     print(x, y)
    return mcd

def setSubCryptograms(data,L):
    subCrypto = {}

    for i in range(L):
        sub = "C" + str(i)
        subC = []
        for j in range(i,len(data),L):
            subC.append(data[j])
        subCrypto[sub] = subC
    
    #print
    # for x, y in subCrypto.items():
    #     print(x, y)
    return subCrypto

def frecuencySubCrypto(subCrypto,mod_):
    alphabet = listAlphabet(mod_)
    
    freqLetterSub = []
    for x, y in subCrypto.items():
        freqAlph = {}
        for item in alphabet:
            freqAlph[item] = 0
        for item in y:
            if (item in freqAlph):
                freqAlph[item] += 1
            # else:
            #     freqAlph[item] = 0
        print(x, y)
        # for m, n in freqAlph.items():
        #     print(m, end=' ')
        # print()
        sub = []
        for m, n in freqAlph.items():
            sub.append(n)
            # print(n, end=' ')
        print()
        freqLetterSub.append(sub)


    return freqLetterSub

            
def getKey(freqAlph,mod_):
    
    alphabet = listAlphabet(mod_)
    rule = "AEO"
    idxRule = [] 
    for i in rule:
        idxRule.append(alphabet.index(i))

    # for i in idxRule:
    #     print(i)
    keyResult = []
    for m in range(len(freqAlph)):
        triAlphTarget =  rule
        freqAlphTarget = idxRule.copy()
        max_ = 0
        for n in range(len(freqAlph[m])):
            triAlph_ = []
            freqAlph_ = []
            for nex in idxRule:
                
                next_ = n + nex
                if next_ > len(alphabet)-1:
                    next_ = next_ - (len(alphabet)-1) 
                    next_ = next_-1 #posicion del array
                
                if freqAlph[m][next_] >=2 :
                    triAlph_.append(alphabet[next_])
                    freqAlph_.append(freqAlph[m][next_])
                else:
                    break
            if(len(triAlph_) == 3):
                Sum = sum(freqAlph_)
                if Sum > max_:
                    max_ = Sum
                    triAlphTarget = triAlph_
                    freqAlphTarget = freqAlph_.copy()
        
        for k in triAlphTarget:
            print(k,end='')
        
        print(end='( ')
        for l in freqAlphTarget:
            print(l,end=' ')
        print(end=')')

        keyResult.append(triAlphTarget[0])

            # print(freqAlph[m][n],end=' ')
        print()
    return keyResult


def atackKasiski(data,long_key,mod_): 
    print("\nPOLIGRAMAS FRECUENTES\n")
    dicc,diccPosition = findTrigrams(data,long_key)
    L = int(findLongMCD(dicc,diccPosition)) # longitud posible clave

    print(L,"\n")
    print("\nSUBCRIPTOGRAMAS\n")
    subCrypto = setSubCryptograms(data,L)
    
    
    freqAlph = frecuencySubCrypto(subCrypto,mod_)
    print("\nDiagrama de Frecuencia de los criptogramas\n")
    
    alphabet = listAlphabet(mod_)
    
    print("   ",end=' ')
    for abc in alphabet:
        print(abc,end='  ')
    print()
    for m in range(len(freqAlph)):
        print('C'+ str(m),end=': ')
        for n in range(len(freqAlph[m])):
            print(freqAlph[m][n],end='  ')
        print()
    print()

    print("\nPosible clave: ")
    key_ = getKey(freqAlph,mod_)
    print("\n",key_)
    print("CLAVE: ","".join(key_))
    
    #Decriptions
    print("\nMensaje Descifrado: \n")
    msmDecrypt = getDecryption(data,data,key_,mod_)# data pos 2 = texto encriptado
    print()
    print("".join(msmDecrypt))
    
#================================================================================================================================


def main():
    # Read
    myfile = open('Criptoanalizar_19.txt', encoding='utf-8')
    data = myfile.read()
    data = list(data)
    myfile.close()
    # key_ = "MAR"
    mod_ = 27 # ESCOJER MOD
    
    # msmEncrypt = getEncrypt(data,key_,mod_)
    # print("".join(msmEncrypt))
    # msmDecrypt = getDecryption(data,msmEncrypt,key_,mod_)
    # print("".join(msmDecrypt))
    
    # with open('result.txt', 'w') as f:
    #     f.write("".join(msmEncrypt))
        
    # print("Cantidad de Frecuencias")
    # frecuency = Letterfrecuency(msmEncrypt,mod_)
    # for x in frecuency:
    #     print(x," -> ",frecuency[x])

    # LECTURA TEXTO
    #  Read
    # myfile = open('text_15.txt', encoding='utf-8')
    # data = myfile.read()
    # data = list(data)
    # key_ = "HIELO"
    
    # mod_ = 27 # ESCOJER MOD

    # Decriptions
    # msmDecrypt = getDecryption(data,data,key_,mod_)
    # print("".join(msmDecrypt))
    
    # #establece longitud de los bigramas,trigramas o etc
    long_key = 4
    atackKasiski(data,long_key,mod_)



    #cuestionario final ejercicio 4
    # data = "IZLQOD"
    # data = list(data)
    # key_ = "SOL"
    # mod_ = 27 # ESCOJER MOD

    # msmDecrypt = getDecryption(data,data,key_,mod_)
    # freqAlph = print("".join(msmDecrypt))

    


    #getAutoclave

    # print()
    # data = "HABIAUNAVEZ"
    # data = list(data)
    # key_ = "CIRCO"
    # mod_ = 27
    # autokey = getAutoclave(data,key_)
    # print(autokey)


    # print(data)
   

if __name__ == "__main__":
    main()


