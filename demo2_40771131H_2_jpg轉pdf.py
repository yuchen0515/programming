import os,glob
from PIL import Image

def imgtopdf(pdf_name):
    jpg_files,png_files = glob.glob("*.jpg"),glob.glob("*.png") #取得工作目錄下jpg.png檔
    new_pic = jpg_files.copy()+png_files.copy() #將jpg和png加入到new_pic內
    im_list = []

    #輸出目前處理的圖像名單
    print("\nProcessing......")

    #對檔名作分割排序
    for i in range(len(new_pic)-1):
        for j in range(len(new_pic)-1-i):
            if int((new_pic[j].split('.jpg')[0]).split('_')[1]) > int((new_pic[j+1].split('.jpg')[0]).split('_')[1]):
                temp = new_pic[j]
                new_pic[j] = new_pic[j+1]
                new_pic[j+1] = temp

    
    for i in range(len(new_pic)):
        if i%2==0:  print()
        print("P.{}".format(i+1),new_pic[i],end='\t')

    #讓使用者選擇需要的圖像
    while 1:
        name = (input("\n請問有哪些圖像是不想放進PDF檔的，一一輸入編號[若輸入完畢請輸入'OK']").strip()).lower()
        name = name.strip('p.')
        if name=='ok':  break
        new_pic.pop(int(name)-1)
        print("\n-----請再次確認檔案與編號-----")
        
        for i in range(len(new_pic)):
            if i%2==0:  print()
            print("P.{}".format(i+1),new_pic[i],end='\t')
        
    #開iml檔案，其餘檔案則透過迴圈加進去iml內，並存成pdf檔
    im1 = Image.open(new_pic[0])
    new_pic.pop(0)
    for i in new_pic:
        img = Image.open(i)
        #if img.mode == "RGBA":  img = img.convert('RGB')
        im_list.append(img)
    
    #im1.save(pdf_name, "PDF", resolution=100.0, save_all=True, append_images=im_list, quality=100)
    im1.save(pdf_name, "PDF", resolution=100.0, save_all=True, append_images=im_list)
    print("-------------------------")
    print("\noutput:", pdf_name)

#執行函式，檢查使用者輸入檔名是否包含pdf，沒有就幫他加上去
if __name__ == '__main__':
    pdf_name = input("Please input the name of combined pdf...：").strip()
    pdf=''
    if ".pdf" not in pdf_name:
        pdf='.pdf'
    imgtopdf(pdf_name="{}{}".format(pdf_name,pdf))
    input("\npull everyone to exit...")
