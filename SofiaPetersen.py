# Sofia Petersen candidata ao estágio

import requests
from bs4 import BeautifulSoup

def extract_all_content(url):
    response = requests.get(url)

    if response.status_code == 200:
        soup = BeautifulSoup(response.text, 'html.parser')

        content_set = set()

        for element in soup.find_all():
            content = element.get_text(strip=True)
            if content:
                content_set.add(content)
        
        return content_set

url = "http://www.bianca.com"

conteudo = extract_all_content(url)

print (conteudo)
