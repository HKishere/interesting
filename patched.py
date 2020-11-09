import pymysql
import time

print("开始更新补丁")
try:
    fp = open("patch.txt","r")
except FileNotFoundError:
    print("没有找到更新文件!")
    time.sleep(3)
else:
    fp.seek(0, 0)
    try:
        fsetting = open("HF1.2B_Config.ini","r")
    except FileNotFoundError:
        print("没有找到配置文件!")
        time.sleep(3)
    else:
        print("加载配置文件...")
        host = ""
        user = ""
        password = ""
        database = ""
        port = ""
        for each_line in fsetting:
            if each_line[:5] == "host=":
                host = each_line[5:len(each_line)-1]
            if each_line[:5] == "user=":
                user = each_line[5:len(each_line)-1]
            if each_line[:9] == "password=":
                password = each_line[9:len(each_line)-1]
            if each_line[:9] == "database=":
                database = each_line[9:len(each_line)-1]
            if each_line[:5] == "port=":
                port = each_line[5:len(each_line)-1]
            if host !="" and user != "" and password != "" and database != "" and port != "":
                break
        try:
            db = pymysql.connect(host=host, port=int(port), user=user, passwd=password, db=database)
        except:
            print("连接数据库失败!")
            time.sleep(3)
        else:
            sql=""
            cursor = db.cursor()
            cursor.execute("SELECT VERSION()")
            data = cursor.fetchone()
            print("MySQL version:%s"%data)
            print("更新中...")
            for each_line in fp:
                for each_char in each_line:
                    sql += each_char
                try:
                    cursor.execute(sql)
                except:
                    print("更新失败,检查SQL语句!")
                    time.sleep(3)
                else:
                    sql = ""
            print("更新成功!")
            time.sleep(3)
            db.close()
        fsetting.close()
    fp.close()
    input("按回车Enter键退出...")