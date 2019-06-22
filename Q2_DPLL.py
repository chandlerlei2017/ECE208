def UR(clauses):
    for clause in clauses:
        if len(clause) != 1:
            break
        for temp in clauses:
            if -clause[0] in temp:
                temp.remove(-clause[0])
                temp.remove

def BCP(clauses, var):
    i = 0
    
    while (i < len(clauses)):
        if var in clauses[i]:
            del clauses[i]
            i -= 1
        elif -var in clauses[i] and len(clauses[i]) != 0:
            clauses[i].remove(-var)
        elif -var in clauses[i]:
            return 0
        i += 1

    
    
    if len(clauses) == 0:
        return 1
    else:
        return 2
            
def DPLL(clauses):
    
    res = BCP(clauses, clauses[0][0])
    
    if res == 0:
        return "UNSAT"
    if res == 1:
        return "SAT"
    
if __name__ == "__main__":
    f = open("Input/CNF_1.txt", "r")
    clauses = f.readlines()
    for i in range(len(clauses)):
        clauses[i] = [int(d) for d in clauses[i].split(" ")]
        
    DPLL(clauses)
    print(clauses)
