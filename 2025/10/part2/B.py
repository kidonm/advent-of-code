import pulp as pulp
from pulp import PULP_CBC_CMD


def read_word(word):
    ret = word[1:-1]
    ret = ret.split(',')
    ret = [int(e) for e in ret]
    return ret


def readone(line):
    prob = line.strip()
    prob = prob.split(" ")
    prob = prob[1:]
    buttons = [read_word(e) for e in prob[:-1]]
    targets = read_word(prob[-1])

    coeffs = [[] for _ in range(len(targets))]


    for ixt, t in enumerate(targets):
        for ixb, b in enumerate(buttons):
            for e in b:
                if e == ixt:
                    coeffs[ixt].append(ixb)

    return coeffs, targets, len(buttons)


if __name__ == "__main__":
    # file = open("../A.in", "r")
    file = open("../A.in", "r")

    lines = file.readlines()

    tot = 0;

    for line in lines:
        coeffs, targets, N = readone(line)

        # print("Coeffs:", coeffs)
        # print("Targets:", targets)
        # print("N:", N)

        prob = pulp.LpProblem(f"test", pulp.LpMinimize)

        # print(len(coeffs), len(targets))

        # define variables
        vars = [pulp.LpVariable(f"x{i}", lowBound=0, cat=pulp.LpInteger) for i in range(N)]

        # print(vars)

        prob += pulp.lpSum(vars)

        for c, t in zip(coeffs, targets):
            prob += pulp.lpSum([vars[cc] for cc in c]) == t

        # print(prob)

        prob.solve(PULP_CBC_CMD(msg=False))
        # print("\n--- Solution Status ---")
        # print("Status:", pulb.LpStatus[prob.status])

        cost = sum(v.varValue for v in prob.variables())
        print(cost)
        tot += int(cost)

    print(tot)

        # for c, t in zip(coeffs, targets):
        #     prob += pulb.lpSum([1 * pulb.LpVariable(f"x{b}", cat='Binary') for b in c]) >= t