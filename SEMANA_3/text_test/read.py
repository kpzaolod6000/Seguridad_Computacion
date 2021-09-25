myfile = open('text.txt', encoding='utf-8')
dato = myfile.read()

acents = ['á','é','í','ó','ú']
for x in dato:
    for y in acents:
        if(x == y):
            print("acentos")
myfile.close()