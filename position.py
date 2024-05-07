import pyautogui
import time
import pandas as pd

time.sleep(5)
print(pyautogui.position())

tabela = pd.read_csv("produtos.csv")