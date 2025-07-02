#Take Home Exam 2
#Dictionary and Total Income
our_following_dict = eval(input())
annual_income = float(input())
#1-)Base Tax Rate
income_level = our_following_dict.get("INCOME")
def base_tax_rate(income_level):
    if income_level == "low":
        return annual_income*(10/100)
    elif income_level == "middle":
        return annual_income*(20/100)
    elif income_level == "high":
        return annual_income*(30/100)
#2-)Marital_and_family_deductions
marital_status = our_following_dict.get("MARITAL_STATUS")
number_of_child = len(our_following_dict.get("CHILD"))
def marital_and_family_deductions(marital_status):
    if marital_status == "single":
        return 0
    elif marital_status == "married":
        return 500 + 300*number_of_child
    elif marital_status == "single_parent":
        return 600*number_of_child
#3-)Dependent Adjustments1
list_of_childs = list(map(int, our_following_dict.get("CHILD")))
t = lambda x:x<18
under_18 = filter(t,list_of_childs)
count_of_under_18 = len(list(under_18))
def dependent_adjustments1(count_of_under_18):
    return count_of_under_18*200
#4-)Dependent Adjustments2
special_needs = our_following_dict.get("SPECIAL_NEEDS")
def dependent_adjustments2(special_needs):
    if special_needs == True:
        return 1000
    else:
        return 0
#5-)Dependent Adjustments3
elderly_care = our_following_dict.get("ELDERLY_CARE")
def dependent_adjustments3(elderly_care):
    if elderly_care == True:
            return 800
    else:
            return 0
#6-)Residence Based Deduction
city_category = our_following_dict.get("CITY_CATEGORY")
def residence_based_deduction(city_category):
    if city_category == "urban":
        return 0
    elif city_category == "suburban":
        return 200
    elif city_category == "rural":
        return 400
#7-)Additional Deduction Criterias

#7.1-)Education
education = our_following_dict.get("EDUCATION")
def additional_deduction_criteria1(education):
    if education == True:
        return 500
    else:
        return 0
#7.2-)Healthcare
healthcare = our_following_dict.get("HEALTHCARE")
def additional_deduction_criteria2(healthcare):
    if healthcare == True:
        return 750
    else:
        return 0
#7.3-)Green Initiatives
green_initiatives = our_following_dict.get("GREEN_INITIATIVES")
def additional_deduction_criteria3(green_initiatives):
    if green_initiatives == True:
        return 300
    else:
        return 0
#8-)Property Adjustments
property_status = our_following_dict.get("PROPERTY_STATUS")
def property_adjustment(property_status):
    if property_status == "owns":
        return 0
    elif property_status == "rents":
        return 300
#9-)Duration Based Deduction
total_tax = base_tax_rate(income_level) - (marital_and_family_deductions(marital_status)+dependent_adjustments1(count_of_under_18)+dependent_adjustments2(special_needs)+dependent_adjustments3(elderly_care)+residence_based_deduction(city_category)+additional_deduction_criteria1(education)+additional_deduction_criteria2(healthcare)+additional_deduction_criteria3(green_initiatives)+property_adjustment(property_status))
taxpayer_duration = our_following_dict.get("TAXPAYER_DURATION")
def duration_based_deduction(taxpayer_duration):
    if taxpayer_duration == "new":
        return 0
    elif taxpayer_duration == "regular":
        return total_tax*(5/100)
    elif taxpayer_duration == "long_term":
        return total_tax*(10/100)
#Last Calculations
annual_deductions = marital_and_family_deductions(marital_status)+dependent_adjustments1(count_of_under_18)+dependent_adjustments2(special_needs)+dependent_adjustments3(elderly_care)+residence_based_deduction(city_category)+additional_deduction_criteria1(education)+additional_deduction_criteria2(healthcare)+additional_deduction_criteria3(green_initiatives)+property_adjustment(property_status)+duration_based_deduction(taxpayer_duration)

final_tax_amount = base_tax_rate(income_level) - annual_deductions
#final tax amount cannot be negative.
final_tax_amount = max(final_tax_amount, 0)


print("%.2f" % final_tax_amount)