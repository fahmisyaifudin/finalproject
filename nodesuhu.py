import json
import time
import urllib2


def ambil_suhu():
    f = open ('datasuhu.txt')
    lineList = f.readlines()
    #f.write("")
    f.close()
    x = '{ '+ (lineList[len(lineList)-1]) + '}'
    y = json.loads(x)
    return y["Suhu"]
    
def ambil_kelembapan():
    f = open ('datakelembapan.txt')
    lineList = f.readlines()
    #f.write("")
    f.close()
    x = '{ '+ (lineList[len(lineList)-1]) + '}'
    y = json.loads(x)
    return y["Kelembapan"]
    
while True:
    try:
        print("Suhu : " + ambil_suhu())
        req = urllib2.Request('http://192.168.1.101/tes/prosessuhu.php?suhu='+ambil_suhu())
        response = urllib2.urlopen(req)
    except:
        pass
    try:
        print("Kelembapan : " + ambil_kelembapan())
        req = urllib2.Request('http://192.168.1.101/tes/proseskelembapan.php?kelembapan='+ambil_kelembapan())
        response = urllib2.urlopen(req)
    except:
        pass
    time.sleep(10)

