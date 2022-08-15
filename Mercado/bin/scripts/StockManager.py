

def LeitorEstoque(produto): # le o estoque.txt e retorna o produto pedido, caso encontrado
    
    


    file = open("estoque.txt", "r")        
    caracteres = file.read()
    
    lista = ""
    for x in range (0, len(caracteres)):
        if (x > 0 and x < len(caracteres)-1):
            lista += caracteres[x]
          
    lista = lista.split("/")
    
    verif = 0
    for i in lista:
        i = i.split("-")
        if ( i[0] == produto):
            produto = i[0] + "-" + i[1]
            verif = 1
    
    if ( verif == 0):   # se verif aponta erro, produto retorna com Erro
        produto = "Erro"

    
    file.close()
    return produto # retorna produto e quantidade

def AdicionaEstoque(produto):   # adiciona ao estoque.txt novo produto ou quantidades

    if (len(produto) > 30 or len(produto) <= 0):    # verifica entrada maliciosa
        return "Erro";

    erros = ["\n\nTamanho do estoque errado, limite entre 0 a 999 produtos.\n\n", "\n\nEntrada maliciosa detectada, por favor PARE! Use valores de 0 a 999.\n\n", "\n\nProduto preenchido com tamanho maior que o permitido, 70 caracteres!\n\n",
    "\n\nProduto mal preenchido, nao preencha produtos com espacos desnecessarios!\n\n"]
    erro = 0
    file = open("estoque.txt", "r") 
    
    if(len(produto) > 1 and produto != " "):
        for i in range (0, len(produto)): # verifica entradas com espacos a mais
            if(produto == " "):
                erro += 1
                if(erro > 1):
                    erro = 3
                    print(erros[erro])
                    return "Erro"
            else:
                erro = 0
    else:
        erro = 2
        print(erros[erro])
        return "Erro"
    caracteres = file.read()

    file.close()
    lista = ""

    for x in range (0, len(caracteres)):
        if (x > 0 and x < len(caracteres)-1):
            lista += caracteres[x]
            
    
    
    naolistado = [];
    lista = lista.split("/")
    estanalista = 0

    

    for i in range(0, len(lista)):
            lista[i] = lista[i].split("-")

    indexdoitem = 0;
    for i in range (0, len(lista)):
        if( lista[i][0] == produto):
            estanalista = 1
            indexdoitem = i
    if(estanalista == 0):
        naolistado.append(produto)
    verif = 0
   
    while verif == 0 :
        try:    # protege a funcao contra entradas maliciosas
            x = int(input("Digite a quantidade de " +  produto + " : "))
            if(x < 1000 and x > 0):
                verif = 1
 
            else:
                print(" erro encontrado ! - ", erros[0])
        except:
            print(" erro encontrado ! - ", erros[1])
            return "Erro" # retorna que  algo tentou quebrar a funcao
   

    
    file = open("estoque.txt", "w") 
    if (estanalista == 0):
        naolistado.append(str(x))
        lista.append(naolistado)
        indexdoitem = len(lista)-1
    else:
        
        lista[indexdoitem][1] =str(int(lista[indexdoitem][1])+ x)
        file.write("/")
    for i in lista:
        file.write(i[0] + "-")
        file.write(i[1] + "/")
        
    file.close()
    return lista[indexdoitem][1] # retorna valor do item

def RetiradoEstoque(produto): # retira quantidade do produto no arquivo estoque.txt
    
    if (len(produto) > 30 or len(produto) <= 0):
        return "Erro"; 

    file = open("estoque.txt", "r")        
    caracteres = file.read()
   
    lista = ""
    for x in range (0, len(caracteres)):
        if (x > 0 and x < len(caracteres)-1):
            lista += caracteres[x]
    
    
    lista = lista.split("/")
    
    ind = 0
    verif = 0
    
    
    for i in  range(0, len(lista)):
        lista[i] = lista[i].split("-")
        if(lista[i][0] == produto):
            ind = i
            verif = 1
    if(verif != 0 ):
        verif = 0
        
        
        while verif == 0 :
            
            try: 
                x = int(input("Digite a quantidade de " +  produto + " : "))
            
                if(x <= int(lista[ind][1]) and x > 0):
                    verif = 1
                else:
                    erro = 0
                    print(" erro encontrado ! - Tamanho do estoque errado, limite entre 1 a ", lista[ind][1])
            except:
                erro = 1
                print(" erro encontrado ! - Entrada maliciosa detectada, por favor PARE! Use valores de 1 ", lista[ind][1])
    else:
        return "Erro"
    
    lista[ind][1] = str(int(lista[ind][1])- x)
    file.close()
    file = open("estoque.txt", "w")         
    file.write("/")
    for i in lista:
        file.write(i[0] + "-")
        file.write(i[1] + "/")


    file.close()
    return  lista[ind][1]

def EmFalta(faltantes): # procura no arquivo texto estoque.txt os produtos com 0 de estoque

    

    file = open("estoque.txt", "r")        
    caracteres = file.read()

    lista = ""
    for x in range (0, len(caracteres)):
        if (x > 0 and x < len(caracteres)-1):
            lista += caracteres[x]
    
    file.close()
    
    lista = lista.split("/")
    
    ind = 0
    verif = 0
    faltantes = ""
    for i in range(0, len(lista)):
        lista[i] = lista[i].split("-")
        if(lista[i][1] == "0"):
            faltantes = faltantes + lista[i][0] + "\n"
    file.close()
    return faltantes