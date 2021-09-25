import re
import string

# Read
myfile = open('HERALDOSNEGROS_pre.txt', encoding='utf-8')
data = myfile.read()
data = list(data)
# print(data)
myfile.close()

# Alphabet
def listAlphabet():
    alphabet = list(string.ascii_uppercase)
    alphabet.insert(14,'Ñ')
    return alphabet

# get Text key
def getTextKey(data,key):

    keyText = [] 

    iClv = 0
    for i in range(len(data)):
        if(i%len(key) == 0):
            iClv = 0
        keyText.append(key[iClv])
        iClv += 1
    return keyText

def getEncrypt(data,keyText,alphabet): #ci = mi + ki mod n
    encrypt = data.copy()
    n = len(alphabet)

    for i in range(len(data)):
        indexDt = alphabet.index(data[i])
        indexKy = alphabet.index(keyText[i])
        sumKey = indexDt + indexKy
        newKey = sumKey % n

        encrypt[i] = alphabet[newKey]
    return encrypt

def getDecryption(encrypt,keyText,alphabet):
    decryption = encrypt.copy()
    n = len(alphabet)

    for i in range(len(encrypt)):
        indexDt = alphabet.index(encrypt[i])
        indexKy = alphabet.index(keyText[i])
        restKey = indexDt - indexKy
        charReal = restKey % n

        decryption[i] = alphabet[charReal]
    return decryption

keyText = getTextKey(data,"CIELO")
alphabet = listAlphabet()
encrypt = getEncrypt(data,keyText,alphabet)
decryption = getDecryption(encrypt,keyText,alphabet)

print(alphabet)
print(data)
print(keyText)
print(encrypt)
print(decryption)
