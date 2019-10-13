while True:
    try:
        ip = int(input())
        mask = int(input())
        port = int(input())
        
        for i in range(3, -1, -1):
            tmp = 255 << i * 8
            if i != 0: print(str((ip & tmp) >> i * 8), end = ".")
            else: print(str(ip & tmp), end = "")
        print("\\" + str(mask) + " ===> " + str(port))

    except:
        break
