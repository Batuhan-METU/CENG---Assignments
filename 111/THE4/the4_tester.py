import time
from the4 import OX_to_tree
import copy
import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))


def flatten(lst):
    if not lst: return []
    if type(lst[0]) == list:
        return flatten(lst[0]) + flatten(lst[1:])
    return [lst[0]] + flatten(lst[1:])

def datum(tree): return tree if type(tree) != list else tree[0]
def children(tree): return [] if type(tree) != list else tree[1:]

def isNotPsi(child, parent):
    for i in range(len(child)):
        if child[i] == 'o' and parent[i] == 'x': return True
    return (len([1 for foo in child if foo == 'x']) - 1) != (len([1 for foo in parent if foo == 'x']))

def isValidTree(proposition):
    return (not any([isNotPsi(datum(child), datum(proposition)) for child in children(proposition)])) and (not any([not isValidTree(child) for child in children(proposition)])) if type(proposition) == list and len(proposition) != 1 else True

def doesNotHaveTwins(proposition):
    if type(proposition) != list: return True
    babies = [datum(child) for child in children(proposition)]
    seen = []
    for baby in babies:
        if baby in seen: return False
        seen.append(baby)
    return all([doesNotHaveTwins(child) for child in children(proposition)])

def hasBadStructure(proposition):
    return False if type(proposition) != list else len(proposition) == 1 or any([hasBadStructure(subtree) for subtree in proposition])

def isValid(proposition, case):
    if hasBadStructure(proposition): return (False, "Bad tree structure")
    if not isValidTree(proposition): return (False, "Not Psi")
    if not doesNotHaveTwins(proposition): return (False, "Twins")
    if len(flatten(proposition)) > len(case): return (False, "Added element")
    if len(flatten(proposition)) < len(case): return (False, "Discarded element")
    if sorted(flatten(proposition)) != sorted(case): return (False, "Changed element")
    return (True, "No problem")
    
folder = "./Cases"
input("press Enter to test small cases.")

file_name = os.path.join(folder, "Small Test Cases")
print(os.path.abspath(file_name))
small = open(file_name, 'r')
line = small.readline()
total_cases = 0
passed_cases = 0
while line:
    case_number = int(line.strip()[:-1])
    case = eval(small.readline().strip())
    o_case = copy.deepcopy(case)
    start_time = time.time()
    proposition = OX_to_tree(case)
    end_time = time.time()
    total_time = end_time - start_time
    result, problem = isValid(proposition, o_case)
    total_cases += 1
    passed_cases += result
    result_text = ["Failed", "Passed"][result]
    print(f"CASE: {case_number}   RESULT: {result_text}   TIME: {total_time*1000:.1f}ms   PROBLEM: {problem}")
    line = small.readline()
print(f"{passed_cases} cases passed out of {total_cases} cases")

small.close()

input("press Enter to test Medium cases.")

file_name = os.path.join(folder, "Medium Test Cases")
small = open(file_name, 'r')
line = small.readline()
total_cases = 0
passed_cases = 0
while line:
    case_number = int(line.strip()[:-1])
    case = eval(small.readline().strip())
    o_case = copy.deepcopy(case)
    start_time = time.time()
    proposition = OX_to_tree(case)
    end_time = time.time()
    total_time = end_time - start_time
    result, problem = isValid(proposition, o_case)
    total_cases += 1
    passed_cases += result
    result_text = ["Failed", "Passed"][result]
    print(f"CASE: {case_number}   RESULT: {result_text}   TIME: {total_time*1000:.1f}ms   PROBLEM: {problem}")
    line = small.readline()
print(f"{passed_cases} cases passed out of {total_cases} cases")

small.close()

input("press Enter to test Large cases.")

file_name = os.path.join(folder, "Large Test Cases")
small = open(file_name, 'r')
line = small.readline()
total_cases = 0
passed_cases = 0
while line:
    case_number = int(line.strip()[:-1])
    case = eval(small.readline().strip())
    o_case = copy.deepcopy(case)
    start_time = time.time()
    proposition = OX_to_tree(case)
    end_time = time.time()
    total_time = end_time - start_time
    result, problem = isValid(proposition, o_case)
    total_cases += 1
    passed_cases += result
    result_text = ["Failed", "Passed"][result]
    print(f"CASE: {case_number}   RESULT: {result_text}   TIME: {total_time*1000:.1f}ms   PROBLEM: {problem}")
    line = small.readline()
print(f"{passed_cases} cases passed out of {total_cases} cases")

small.close()

input("press Enter to test HUGE cases.")

file_name = os.path.join(folder, "HUGE Test Cases")
small = open(file_name, 'r')
line = small.readline()
total_cases = 0
passed_cases = 0
while line:
    case_number = int(line.strip()[:-1])
    case = eval(small.readline().strip())
    o_case = copy.deepcopy(case)
    start_time = time.time()
    proposition = OX_to_tree(case)
    end_time = time.time()
    total_time = end_time - start_time
    result, problem = isValid(proposition, o_case)
    total_cases += 1
    passed_cases += result
    result_text = ["Failed", "Passed"][result]
    print(f"CASE: {case_number}   RESULT: {result_text}   TIME: {total_time*1000:.1f}ms   PROBLEM: {problem}")
    line = small.readline()
print(f"{passed_cases} cases passed out of {total_cases} cases")

small.close()
