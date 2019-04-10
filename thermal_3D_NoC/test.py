import csv 
import array 
# csv file name 
filename = "TemP_power.csv"
import numpy as np 
# initializing the titles and rows list 
fields = [] 
rows = [] 
with open(filename, 'r') as csvfile: 
    # creating a csv reader object 
    csvreader = csv.reader(csvfile) 
      
    # extracting field names through first row 
    fields = csvreader.next() 
  
    # extracting each data row one by one 
    for row in csvreader: 
        rows.append(row) 
myList=[]
for row in rows[:1]: 
    # parsing each column of a row 
  for col in row: 
  	myList.append((col))
  	c=myList
print(myList)	
i=0
price = float(myList[i])
i=i+1
price = float(myList[i])
i=i+1
price = float(myList[i])
i=i+1
print(price)
#pd.DataFrame(elements).to_csv('new_core3D11.ptrace',sep=',',index=False)
