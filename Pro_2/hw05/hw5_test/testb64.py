import os
import string


def studentc(inp, out, mode):
  # inp: input filename
  # out: output filename
  # mode: 'd' or 'e'
  # cont: content of output file (bytes type)

  cmd = "./hw0501 -%s %s -o %s > trash"%(mode, inp, out)
  os.system(cmd)
  print(">>>     %s"%cmd)

  with open(out, "rb") as f:
    cont = f.read()

  return cont


def base64(inp, out, mode):
  # inp: input filename
  # out: output filename
  # mode: 'd' or 'e'
  # cont: content of output file (bytes type)

  #base64 a.txt > b.txt
  #base64 -d b.txt > c.txt

  if mode == 'e':
  	mode = ''
  elif mode == 'd':
    mode = '-d'
  cmd = "base64 %s %s > %s"%(inp, mode, out)
  # print(">>>     %s"%cmd)  
  os.system(cmd)
  print(">>>     %s"%cmd)

  with open(out, "rb") as f:
  	cont = f.read()

  return cont[:-1]
  

def cmp(cont1, cont2):
  error = 0

  if len(cont1) != len(cont2):
    print("cmp:    lenth error (%d:%d)"%(len(cont1), len(cont2)))
  
  diff = len(cont1) - len(cont2)
  if len(cont1) > len(cont2):
  	length = len(cont2)
  else:
  	length = len(cont1)
  	diff = -diff

  diff_sum = 0	
  diff_pos = []

  for i in range(length):
    if cont1[i] != cont2[i]:
      diff_sum+=1
      diff_pos.append(i)

  if diff_sum != 0 or diff != 0:
  	error = 1

  if error == 1:
    if diff != 0:
  	  print("cmp:    compare with no out of range data %d byte(s)"%diff)
    print("cmp:    %d diffrent byte(s)"%diff_sum)
    print("cmp:    positions of diffrent byte(s)")
    print("cmp:    ", end='')
    # [print(pos, end=', ') for pos in diff_pos]
    print()

  if error == 0:
  	return 1
  else:
  	return 0


def b64_len_chk(b64):
  return len(b64)%4


def test_1(testfile):
  print("\ntest_1: start")

  b64out_e = "b64out1_e.txt"
  stuout_e = "stuout1_e.txt"
  
  stu_content = studentc(testfile, stuout_e, "e")
  b64_content = base64(testfile, b64out_e, "e")


  remainder = b64_len_chk(stu_content.decode().replace("\n", ""))
  if remainder != 0:
  	print("b64:base64 string length error")
  	print("b64:b64%%4 = %d"%remainder)

  if cmp(stu_content, b64_content) == 1:
  	print("test_1: perfect!")
  	return 1
  else:
  	print("test_1: failed")
  	return 0




def test_2(testfile):
  print("\n\ntest_2: start")

  b64out_e = "b64out2_e.txt"
  stuout_d = "stuout2_d.txt"

  base64(testfile, b64out_e, "e")  
  stu_content = studentc(b64out_e, stuout_d, "d")

  with open(testfile, "rb") as f:
  	ori_content = f.read()


  if cmp(stu_content, ori_content) == 1:
    print("test_2: perfect!\n")
    return 1
  else:
    print("test_2: failed\n") 
    return 0


def test_3(testfile):
  print("\ntest_3: start")
  tail = testfile.split('.')[-1]
  stuout_e = "stuout3_e.txt"
  stuout_d = "stuout3_d.%s"%tail

  studentc(testfile, stuout_e, "e")  
  stu_content = studentc(stuout_e, stuout_d, "d")

  with open(testfile, "rb") as f:
  	ori_content = f.read()

  cmp(stu_content, ori_content)

  cmd = "eog %s"%stuout_d
  print(">>>     %s"%cmd)
  os.system(cmd)


  ans = input("Does the picture show correctly on screen ? (Y/n) : ")
  if(ans[0].lower() == "y"):
  	print("test_3: perfect!")
  	return 1
  else:
  	print("test_3: failed") 
  	return 0






score = 0

testfile_1 = "1.txt"
testfile_2 = "test_2.txt"
testfile_3 = "img.jpg"


if test_1(testfile_1) == 1:
  score += 10
if test_2(testfile_1) == 1:
  score += 10
if test_3(testfile_3) == 1:
  score += 5

print("\n\nscore: %d"%score)





