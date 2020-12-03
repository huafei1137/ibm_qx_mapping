import os
import re
import pdb

with open('hhh.txt', 'w') as fff:
    m = []
    for fn in  os.listdir('results'):
    #print(fn)
        fff.write(f'{fn}\n')
        with open(os.path.join('results', fn), 'r') as f:
            ln = f.readlines()
        for i,l in enumerate(ln):
            if 'maximum' in l:
                fff.write(f'{l}\n')
                l_ = l.split()
                for ss in l_:
                    if ss.startswith('are'):
                        m.append(float(ss[3:]))
                if float(ss[3:]) >= 5:
                    print(f'{float(ss[3:])} occurance name is {fn}')
            if 'the critical path' in l:
                fff.write(f'{l}\n')
                l_ = l.split()
                n = []
                for s in l_:
                    if s.startswith('is'):
                        n.append(float(s[2:]))
                # print(n[1]-n[0])
                num = n[1] - n[0]
                if num > 0:
                    fff.write(f'{l}\n')
                    fff.write(f'{n[1] - n[0]}\n')
    print(m)
    for i in range(1,11):
        kcount = m.count(i)
        print(f'{i} CNOT occurance is : {kcount}\n')

