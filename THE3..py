#Take Home Exam 3(THE3)
#We have to find count of rectangles in pattern P.

#We should check the zeros inside rectangles since the rectangles should include at least one "0".
def checking_zero(pattern, top, left, bottom, right):
    for row in range(top + 1, bottom):
        for col in range(left + 1, right):
            if pattern[row][col] == "0":
                return True
    return False

#We also control condition of being rectangle. In order to control that we should examine "1"s as edges are created by "1"s.
def condition_of_being_rectangle(pattern, top, left, bottom, right):
    def checking_row(row_index): #We should check rows between left and right
        for columns_between_left_and_right in range(left, right+1):
            if pattern[row_index][columns_between_left_and_right] == "0": #Even one "0" disrupt the edge of rectangle.
                return False
        return True
    def checking_col(col_index): #We should check columns between top and bottom.
        for rows_between_left_and_right in range(top, bottom+1):
            if pattern[rows_between_left_and_right][col_index] == "0": #Similarly even one "0" disrupt the edge of rectangle.
                return False
        return True
    return checking_row(top) and checking_row(bottom) and checking_col(left) and checking_col(right) and checking_zero(pattern, top, left, bottom, right)
    #If all conditions above here were true, then the pattern sequence would be a rectangle.

#We should find unique top-left and bottom-right corners for rectangles so that every unique corner demonstrate a unique rectangle.
def finding_corners_of_rectangles(pattern):
    row_count = len(pattern)
    column_count = len(pattern[0])
    result = [] #rectangle's top left and right bottom corner
    for top in range(row_count):
        for left in range(column_count):
            if pattern[top][left]=="1":
                for bottom in range(top+1, row_count): #By taking range boundaries like this, we show that bottom index is greater than top index.
                    for right in range(left +1 ,column_count): #Similarly, by taking range boundaries like this, we show that right index is greater than left index.
                        if pattern[bottom][right]=="1" and condition_of_being_rectangle(pattern, top, left, bottom, right):
                                top_left_corner = pattern[top][left]
                                bottom_right_corner = pattern[bottom][right]
                                result.append([top_left_corner, bottom_right_corner])
    return result

#Finally we should calculate count of rectangles by finding length of result list which we found at the end of finding_corners_of_rectangles function.
def count_rectangles(P):
    return len(finding_corners_of_rectangles(P))





