from collections import defaultdict 

t = int(input())

correctCodes = set(["A01", "A02", "A03", "A04", "B01", "B02", "B03", "B04", "C01", "C02", "C03", "C04", "D01", "D02", "D03", "D04", "E01", "E02", "E03", "E04", "F01", "F02", "F03", "F04", "G01", "G02", "G03", "G04"])


while(t):
    t -= 1
    s = input()
    n = len(s)
    i = 0
    j = 0
    l = 0
    r = 0
    map = defaultdict(int)
    valid = True

    for k in range(0, n, 3):
        code = s[k: k + 3]
        #print(code)

        if(code not in correctCodes):
            print(-1, code, sep=" ")
            valid = False
            break

        if(map[code] == 1):
            i = k
            j = k + 2
            #print(i, j)
            map.clear()
        else:
            j = k + 2
            #print(code, j)

        if((j - i + 1) > (r - l + 1)):
            l = i
            r = j

        map[code] += 1
    
    if(not valid):
        continue
    
    competitions = 0
    entertainment = 0
    socialGatherings = 0
    dinners = 0
    processions = 0
    trainingWorkshops = 0
    exams = 0
    print((r - l + 1) // 3, end=" ")

    for i in range(l, r + 1, 3):
        print(s[i: i + 3], end = " ")
        if(s[i] == 'A'):
            competitions += 1
        if(s[i] == 'B'):
            entertainment += 1
        if(s[i] == 'C'):
            socialGatherings += 1
        if(s[i] == 'D'):
            dinners += 1
        if(s[i] == 'E'):
            processions += 1
        if(s[i] == 'F'):
            trainingWorkshops += 1
        if(s[i] == 'G'):
            exams += 1
    
    if(competitions):
        print(competitions, "Competitions", sep =" ", end=" ")
    if(entertainment):
        print(entertainment, "Entertainment", sep =" ", end=" ")
    if(socialGatherings):
        print(socialGatherings, "Social Gatherings", sep =" ", end=" ")
    if(dinners):
        print(dinners, "Dinners", sep =" ", end=" ")
    if(processions):
        print(processions, "Processions", sep =" ", end=" ")
    if(trainingWorkshops):
        print(trainingWorkshops, "Training Workshops", sep =" ", end=" ")
    if(exams):
        print(exams, "Exams", sep =" ", end=" ")
    print()

    