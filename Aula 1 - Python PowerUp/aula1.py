# https://dlp.hashtagtreinamentos.com/python/intensivao/login

import pyautogui as pag
import time
import pandas as pd

pag.PAUSE = 1

# abrir o chrome
pag.press("win")
pag.write("chrome")
pag.press("enter")

# entrar no site
pag.write("https://dlp.hashtagtreinamentos.com/python/intensivao/login")
pag.press("enter")

time.sleep(2) # pra poder carregar a tela com tempo
# login
pag.click(x=151, y=331)
pag.write("sofia@teste.com")
pag.press("tab")
pag.write("teste")
pag.press("tab")
pag.press("enter")  
time.sleep(2)

# pandas le o arquivo com os dados
data = pd.read_csv("produtos.csv")

for row in data.index:

    id = data.loc[row, "codigo"]
    brand = data.loc[row, "marca"]
    type = data.loc[row, "tipo"]
    cat = str(data.loc[row, "categoria"])
    price = str(data.loc[row, "preco_unitario"])
    cost = str(data.loc[row, "custo"])
    obs = str(data.loc[row, "obs"])

    pag.click(x=125, y=234)
    pag.write(id)
    pag.press("tab")
    pag.write(brand)
    pag.press("tab")
    pag.write(type)
    pag.press("tab")
    pag.write(cat)
    pag.press("tab")
    pag.write(price)
    pag.press("tab")
    pag.write(cost)
    pag.press("tab")
    if obs != "nan":
        pag.write(obs)
    pag.press("tab")
    pag.press("enter")
    pag.scroll(3000)


