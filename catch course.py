import pyautogui as pag
import time as t
import random as r

def add():
    pag.click(46, 247)
    
def inputnum():
    pag.click(235, 256)
    pag.typewrite('2816', 0.25)
    
def save():
    pag.click(701, 505)
    #
    t.sleep(r.randint(2,5)/3)
    pag.click(612, 640)
    
def saveok():
    pag.click(646, 641)
    
def addtime():
    pag.click(825, 172)
    t.sleep(5)
    pag.click(692, 452)
    t.sleep(3)
    pag.click(284, 171)
    
def basic():
    add()
    t.sleep(3.5)
    inputnum()
    
def getit():
    save()
    t.sleep((r.randint(3,6))/3)
    saveok()
    t.sleep((r.randint(3,6)/10))

input('When you finish yout setting, then press enter in your keyboard.')

while 1:
    t.sleep(3.5)
    p = 0
    basic()
    while p < 300:
        getit()
        p+=1
    addtime()
