
filename = "PopAlarmWin.xml"

src_path = "E:\\SVN_XIANAN\\XAzysx_BHF3.0\\trunk_207\\Code\\bin\\skin1920_1080\\Layout\\" + filename

targt_file_path = ["E:\\SVN_XIANAN\\XAzysx_BHF3.0\\trunk_207\\Code\\bin\\skin\\Layout\\", "E:\\SVN_XIANAN\\XAzysx_BHF3.0\\trunk_207\\Code\\bin\\skin2560_1440\\Layout\\" , "E:\\SVN_XIANAN\\XAzysx_BHF3.0\\trunk_207\\Code\\bin\\skin3840_2160\\Layout\\", "E:\\SVN_XIANAN\\XAzysx_BHF3.0\\trunk_207\\Code\\bin\\skin4096_2160\\Layout\\"]

for each in targt_file_path:
    each += filename
    src_file = open(src_path, "r", encoding='utf-8')
    temp = open(each,"w",encoding='utf-8')
    temp.write(src_file.read())
    temp.close()
    src_file.close()

src_file.close()
print("finish!")
