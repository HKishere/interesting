ft = open("./text.txt","r")
fp = open("./patch","w")
ft.seek(0, 0)

choose = input('输入1加密\n输入2解密\n')

if choose == '1':
    for each_line in ft:
        for each_char in each_line:
            each_char = ord(each_char)
            encrypted_code = each_char + 3
            encrypted_code = chr(encrypted_code)
            fp.write(encrypted_code)
    fp.write("\n")

if choose == '2':
    for each_line in ft:
        for each_char in each_line:
            each_char = ord(each_char)
            encrypted_code = each_char - 3
            encrypted_code = chr(encrypted_code)
            fp.write(encrypted_code)
