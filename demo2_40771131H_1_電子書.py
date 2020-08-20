from selenium import webdriver
from selenium.common.exceptions import NoSuchElementException
from selenium.webdriver.common.by import By
from bs4 import BeautifulSoup
from urllib.parse import urlparse
from urllib.request import urlopen 
import math, time, sys, os, requests, pyautogui
import tkinter as tk

global name,i
name, i = '', 0

#叫我控制的driver睡覺一下
def gosleep(sec):
    driver.implicitly_wait(sec)

#關掉我寫的視窗，把使用者輸入的值傳到外面
def close_window (): 
    global name
    global i
    name, i= str(bookname_entry.get()), int(startpage_entry.get())
    window.destroy()


#開自動化控制瀏覽器
url = 'http://lib.ebookservice.tw/il/#account/sign-in'
#driver= webdriver.Chrome(r"C:\Program Files (x86)\Google\Chrome\Application\chromedriver.exe")
driver= webdriver.Firefox() #用火狐開
driver.maximize_window()    #視窗最大化

gosleep(100)
driver.get(url) #去台灣雲端書庫@宜蘭(我住宜蘭，也可以登高雄的把網站IP弄掉，換掉經緯度即可)

#搜尋平台上懸浮視窗
gosleep(100)
driver.find_element_by_class_name('bootstrap-dialog-footer-buttons')
e= driver.find_elements_by_tag_name('button')
gosleep(100)
driver.find_element_by_class_name("bootstrap-dialog-body")

#從所有按鈕中找到內文為"我知道了"的按鈕，然後按下去
for y in e:
    if (str(y.text)=='我知道了'):
        time.sleep(2)
        y.click()
        break

#找輸入帳號／密碼的欄位，並輸入
e = driver.find_element_by_id("accountIdText")
e.send_keys(input())
e = driver.find_element_by_id("passwordText")
e.send_keys(input())

#利用絕對路徑(XPATH)找到登入的按鈕，按下去
e = driver.find_element_by_xpath('/html/body/div[1]/div/div[7]/div/div/div[2]/div/form/div[5]/div/button')
e.click()

gosleep(100)


pp = '1'
while not(pp=='-1'):
    print("---開始搜尋---")
    pp = input('>>>')
    gosleep(5)
    e = driver.find_element_by_id("keywordText")
    e.clear()
    e.send_keys(pp)
    e = driver.find_element_by_xpath('/html/body/div[1]/div/div[3]/div/div[2]/div/div[1]/form/button')
    e.click()
    gosleep(5)
    kk = driver.find_elements_by_class_name("bookTitle")
    kpindex = 0
    for i in kk:
        print("[{}]. {}".format(kpindex,i.text))
        kpindex+=1

    print("\n※輸入'-1'則結束")
    print("-----提示-----")
    print("1) 重新搜尋")
    print("2) 選取書籍")
    check = input('>>>')
    if check =='-1':
        break
    elif check =='1':
        continue
    elif check =='2':
        print("\n書籍編號")
        nob = input('>>>')
        try:
            nob = nob.replace('[','')
            nob = nob.replace(']','')
            nob = nob.strip()
            kk[int(nob)].click()
            print("您選定的書籍為：{}".format(kk[int(nob)].text))
            #可以再增加借閱、取消等服務
            break
        except:
            print("您輸入的編號超出範圍")
            print("現在開始重新搜尋")
    else:
        print("別鬧了大大，沒有1和2以外的選項")
        print("幫你重新搜尋\n")
            
   

    
#模擬按鍵盤上的EXC
#pyautogui.press('exc')

url3= 'http://voler.ebookservice.tw'

#製作使用者介面


#先製作大視窗，顏色、大小、標題
window = tk.Tk()
window.title('E-Book App')
window.geometry('400x150')
window.configure(background='white')

header_label = tk.Label(window, text='E-Book Setting')
header_label.pack()

#第一格輸入的欄位(書籍名稱)
bookname_frame = tk.Frame(window) #外框
bookname_frame.pack(side=tk.TOP)
bookname_label = tk.Label(bookname_frame, text='書籍名稱') #顯示文字[提示]
bookname_label.pack(side=tk.LEFT)
bookname_entry = tk.Entry(bookname_frame)   #使用者輸入的欄位
bookname_entry.pack(side=tk.LEFT)

#同上，不過是第二格輸入的欄位(起始頁碼)
startpage_frame = tk.Frame(window)
startpage_frame.pack(side=tk.TOP)
startpage_label = tk.Label(startpage_frame, text='起始頁碼')
startpage_label.pack(side=tk.LEFT)
startpage_entry = tk.Entry(startpage_frame)
startpage_entry.pack(side=tk.LEFT)

#result_label = tk.Label(window)
#result_label.pack()

#寫使用者按的按鈕，丟在我的介面內
#提示內容是Download，至於這按鈕要做的事情直接寫在副函式
button = tk.Button(window, text='Download...', command= close_window)
button.pack()

#執行完畢後，繼續執行py這隻程式
window.mainloop()


#取得目前我程式所在的工作路徑，字串拼貼後就能用來丟進我建立資料夾
#檢查重複輸入與否
now = str(os.getcwd())
pkk = ''
kk= ''
while os.path.isdir(('{}\{}{}{}'.format(now,name,kk,pkk))):
    if (len(pkk))==0:   pkk = 0
    pkk+=1
    name = "{}_{}".format(name, pkk)

#建立資料夾，名稱是使用者輸入的書名
os.mkdir(name)

k=0 #127/128

#跑無限迴圈把電子借閱介面的圖片原始檔一一爬出來
while 1:
    #這是python的例外處理，以免因為錯誤而跳error而無法持續
    try:
        gosleep(10)
        #使用BeautifulSoup解析html把輪廓弄出來 (目前瀏覽器所在頁面的html)
        sp = BeautifulSoup(driver.page_source, "html.parser")
        gosleep(10)
        #找html內所有 有img的標籤(裡面的src標籤內會有網址)
        imge2 = sp.find_all(['img'])
        gosleep(10)
        imge = imge2[k].get('src') #抓原始圖檔網址
        full_path=url3+str(imge)    #配上原本主機的網址，得出最終圖片原始網址
        gosleep(10)
        #用urlopen可以剖析網址中的內容，而且更可以針對這個網址直接做事情(如post, get等)
        image = urlopen(full_path)
        gosleep(10)
        #fp = open('{}{}.jpg'.format(name,i), 'wb')
        #在剛剛新增的資料夾新增一個 書名i.jpg的空白jpg
        fp = open('{}\{}\{}_{}.jpg'.format(now,name,name,i), 'wb')
        gosleep(10)
        #將剛剛剖析的圖片網址，寫進去空白檔案(變成正常圖檔)
        fp.write(image.read())
        gosleep(10)
        #關掉檔案，並輸出說XXX下載完成
        fp.close()
        gosleep(10)
        print('{}_{}.jpg 下載完成...'.format(name,i))
        i,k = i+1, k+1
        #driver.save_screenshot("")

        #找往右按的按鈕，然後按下去
        gosleep(10)
        e=driver.find_element_by_xpath("/html/body/div[@class='_voler_nextNavigator']")
        gosleep(10)
        e.click()
        gosleep(10)
    #如果來到這裡，表示翻完了，或是過程中出了什麼差錯
    except:
        #說明截圖幾張了，然後關掉自動化瀏覽器
        print("已經完成囉，截圖數：{}張".format(i))
        driver.close()
        break
