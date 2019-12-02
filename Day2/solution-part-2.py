def runProgram(instructions, arg1, arg2):

    testInput = instructions[:]
    testInput[1] = arg1
    testInput[2] = arg2

    for i in range(len(instructions) // 4):
        (opcode, param1, param2, result) = inputTok[i*4:(i+1)*4]

        if opcode == "1":
            testInput[int(result)] = int(testInput[int(param1)]) + int(testInput[int(param2)])
        elif opcode == "2":
            testInput[int(result)] = int(testInput[int(param1)]) * int(testInput[int(param2)])
        else:
            break

    return testInput[0]


with open('input.txt') as inputFile:
    inputTok = inputFile.read().split(",")

    for i in range(100):
        for j in range(100):
            if runProgram(inputTok, i, j) == 19690720:
                print(i*100 + j)
                break