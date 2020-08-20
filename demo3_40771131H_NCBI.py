import pdfkit
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.common.exceptions import NoSuchElementException
from selenium.webdriver.common.by import By
from bs4 import BeautifulSoup
from urllib.parse import urlparse
from urllib.request import urlopen 
import math, time, sys, os, requests, pyautogui
import tkinter as tk

#下載圖片副函式
def get_image(url, pic_name):
    driver.get(url) #去那網址
    time.sleep(1)
    
    #讓瀏覽器抓取長和寬
    width = driver.execute_script("return document.documentElement.scrollWidth")
    height = driver.execute_script("return document.documentElement.scrollHeight")
    
    #瀏覽器設定長寬，再截圖
    driver.set_window_size(width, height)
    time.sleep(1)
    driver.save_screenshot(pic_name)

#url = 'https://www.ncbi.nlm.nih.gov/nuccore/AJ535677.4'
print("搜尋")
pi = input('>>>').strip()   #Survivin
url = 'https://www.ncbi.nlm.nih.gov/nuccore/?term=' + pi

#開啟，並跑pdfkit
chromedriver = r"C:\Program Files (x86)\Google\Chrome\Application\chromedriver.exe"
confg = pdfkit.configuration(wkhtmltopdf=r'C:\ITSA73\wkhtmltox\bin\wkhtmltopdf.exe')
os.environ["webdriver.chrome.driver"] = chromedriver
chrome_options = Options()

#長截圖模式
chrome_options.add_argument('headless')

driver = webdriver.Chrome(chromedriver,options=chrome_options)

#取得搜尋結果的每個超連結，一一探訪
url2 = 'https://www.ncbi.nlm.nih.gov'
html = requests.get(url).text
sp = BeautifulSoup(html, 'html.parser')
all_title = (sp.find_all('p','title','a'))
pa = 1
for i in all_title:
    name = (str(i).split('href="')[1]).split('"')[0]
    name2 = name.split('/')[2]
    url3 = url2 + name
    get_image(url3, "{}_{}.png".format(pa,name2))
    print("{}_{}.png已下載完成...".format(pa,name2))

    #這裡我只讓pdf下載一次，有點花時間
    if pa!=1:
        pa+=1
        continue
    #下載過，下面就不會再執行了
    try:
        pdfkit.from_url(url3, "{}_{}.pdf".format(pa,name2),configuration=confg)
        #pdfkit.from_url(url3, "{}_{}.pdf".format(pa,name2))
        print("{}_{} 下載完成...".format(pa,name2))
        
    except:
        print("{}_{} 無法讀取".format(pa,name2))
    pa+=1

#關掉瀏覽器
driver.close()
    



