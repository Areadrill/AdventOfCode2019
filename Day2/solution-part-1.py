with open('inputPart1.txt') as inputFile:
    inputTok = inputFile.read().split(",")

    for i in range(len(inputTok) // 4):
        (opcode, param1, param2, result) = inputTok[i*4:(i+1)*4]

        if opcode == "1":
            inputTok[int(result)] = int(inputTok[int(param1)]) + int(inputTok[int(param2)])
        elif opcode == "2":
            inputTok[int(result)] = int(inputTok[int(param1)]) * int(inputTok[int(param2)])
        else:
            break

    print(inputTok)
    