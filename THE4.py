#Take Home Exam 4(THE4)
def Ψ_Operation(S):
    o_indices = []
    for i in range(len(S)):
        if S[i]=="o":
            o_indices.append(i)
    possible_words = []
    for index in o_indices:
        new_word = S[:index]+"x"+S[index+1:]
        possible_words.append(new_word)
    return possible_words

def FindingChildrenOfParents(L, node):
    possible_children_of_node = Ψ_Operation(node)
    children = []
    for child in possible_children_of_node:
        if child in L:
            children.append(child)
    return children

def FindingRoot(lst):
    root = lst[0]
    max_o_count = lst[0].count("o")
    for i in range(len(lst)):
        current_o_count = lst[i].count("o")
        if current_o_count>max_o_count:
            max_o_count = current_o_count
            root = lst[i]
    return root

def MakeTree(L, node):
    children = FindingChildrenOfParents(L, node)
    L.remove(node)
    if not children:
        return node
    else:
        result = [node]
        for child in children:
            subtree = [MakeTree(L, child)]
            result.extend(subtree)
        return result




def OX_to_tree(L):
    root = FindingRoot(L)
    newList = list(L)
    return MakeTree(newList, root)
