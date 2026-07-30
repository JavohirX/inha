def applyF_filterG(L, f, g):
    newL = []
    for i in L:
        if g(f(i)) == True:
            newL.append(i)
    L[:] = newL
    if len(L) == 0:
        return -1
    else:
        return max(L)