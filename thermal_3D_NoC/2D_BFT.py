cmesh = 2
rows = 2
layers = 1


for z in range(layers):
	filename = 'new_BFT_layer'+str(z)
	fplan = open(filename+'.flp','w')
	if(z!=layers-1):
		timtsv = open('BFT_timtsv'+str(z)+'.flp','w')
	
	for sy in range(2):
		for sx in range(2):
			for y in range(rows):
				for x in range(cmesh):
					for j in range(2):
						for i in range(2):
							fplan.write('Icache_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.003100\t0.002600\t'+str(i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('Dcache_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.003100\t0.002600\t'+str(0.003100+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('Bpred_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001033\t0.000700\t'+str(i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.002600+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('Bpred_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001033\t0.000700\t'+str(0.001033+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.002600+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('Bpred_2_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001033\t0.000700\t'+str(0.002067+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.002600+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('DTB_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001033\t0.000700\t'+str(0.003100+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.002600+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('DTB_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001033\t0.000700\t'+str(0.004133+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.002600+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('DTB_2_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001033\t0.000700\t'+str(0.005167+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.002600+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('FPAdd_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001100\t0.000900\t'+str(i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.003300+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('FPAdd_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001100\t0.000900\t'+str(0.001100+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.003300+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('FPReg_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.000550\t0.000380\t'+str(i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.004200+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('FPReg_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.000550\t0.000380\t'+str(0.000550+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.004200+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('FPReg_2_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.000550\t0.000380\t'+str(0.001100+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.004200+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('FPReg_3_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.000550\t0.000380\t'+str(0.001650+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.004200+j*0.007710+y*0.01693+sy*0.03386)+'\n')
					
							fplan.write('FPMul_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001100\t0.000950\t'+str(i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.004580+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('FPMul_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001100\t0.000950\t'+str(0.001100+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.004580+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('FPMap_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001100\t0.000670\t'+str(i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.005530+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('FPMap_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001100\t0.000670\t'+str(0.001100+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.005530+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('IntMap_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.000900\t0.001350\t'+str(0.002200+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.004850+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('IntQ_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001300\t0.001350\t'+str(0.003100+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.004850+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('IntReg_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.000900\t0.000670\t'+str(0.004400+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.005530+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('IntReg_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.000900\t0.000670\t'+str(0.005300+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.005530+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('IntExec_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001800\t0.002230\t'+str(0.004400+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.003300+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('FPQ_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.000900\t0.001550\t'+str(0.002200+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.003300+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('LdStQ_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.001300\t0.000950\t'+str(0.003100+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.003900+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('ITB_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.000650\t0.000600\t'+str(0.003100+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.003300+j*0.007710+y*0.01693+sy*0.03386)+'\n')
							fplan.write('ITB_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)+'\t0.000650\t0.000600\t'+str(0.003750+i*0.006200+x*0.01506+sx*0.03012)+'\t'+str(0.003300+j*0.007710+y*0.01693+sy*0.03386)+'\n')
					fplan.write('Router_'+str(x+cmesh*y+rows*cmesh*sx+2*rows*cmesh*sy+4*rows*cmesh*z)+'\t0.001330\t0.001330\t'+str(0.005535+x*0.01506+sx*0.03012)+'\t'+str(0.006380+y*0.01693+sy*0.03386)+'\n')
					fplan.write('TSV_'+str(x+cmesh*y+rows*cmesh*sx+2*rows*cmesh*sy+4*rows*cmesh*z)+'\t0.001330\t0.000180\t'+str(0.005535+x*0.01506+sx*0.03012)+'\t'+str(0.006200+y*0.01693+sy*0.03386)+'\n')
					fplan.write('Fill_0_'+str(x+cmesh*y+rows*cmesh*sx+2*rows*cmesh*sy+4*rows*cmesh*z)+'\t0.005535\t0.001510\t'+str(x*0.01506+sx*0.03012)+'\t'+str(0.006200+y*0.01693+sy*0.03386)+'\n')
					fplan.write('Fill_1_'+str(x+cmesh*y+rows*cmesh*sx+2*rows*cmesh*sy+4*rows*cmesh*z)+'\t0.005535\t0.001510\t'+str(0.006865+x*0.01506+sx*0.03012)+'\t'+str(0.006200+y*0.01693+sy*0.03386)+'\n')
			
			
					if(z!=layers-1):
			
						timtsv.write('TIM_unit_0_'+str(x+cmesh*y+rows*cmesh*sx+2*rows*cmesh*sy+4*rows*cmesh*z)+'\t0.012400\t0.006200\t'+str(x*0.01506+sx*0.03012)+'\t'+str(y*0.01693+sy*0.03386)+'\n')
						timtsv.write('TIM_unit_1_'+str(x+cmesh*y+rows*cmesh*sx+2*rows*cmesh*sy+4*rows*cmesh*z)+'\t0.012400\t0.007530\t'+str(x*0.01506+sx*0.03012)+'\t'+str(0.006380+y*0.01693+sy*0.03386)+'\n')
						timtsv.write('TIM_tsv_'+str(x+cmesh*y+rows*cmesh*sx+2*rows*cmesh*sy+4*rows*cmesh*z)+'\t0.001330\t0.000180\t'+str(0.005535+x*0.01506+sx*0.03012)+'\t'+str(0.006200+y*0.01693+sy*0.03386)+'\n')
						timtsv.write('Filler_0_'+str(x+cmesh*y+rows*cmesh*sx+2*rows*cmesh*sy+4*rows*cmesh*z)+'\t0.005535\t0.000180\t'+str(x*0.01506+sx*0.03012)+'\t'+str(0.006200+y*0.01693+sy*0.03386)+'\n')
						timtsv.write('Filler_1_'+str(x+cmesh*y+rows*cmesh*sx+2*rows*cmesh*sy+4*rows*cmesh*z)+'\t0.005535\t0.000180\t'+str(0.006865+x*0.01506+sx*0.03012)+'\t'+str(0.006200+y*0.01693+sy*0.03386)+'\n')
						
						
			fplan.write('Fill_1_0_'+str(sx+2*sy+4*z)+'\t0.002660\t0.01391\t'+str(0.012400+sx*0.03012)+'\t'+str(sy*0.03386)+'\n')
			fplan.write('Fill_1_1_'+str(sx+2*sy+4*z)+'\t0.002660\t0.01391\t'+str(0.012400+sx*0.03012)+'\t'+str(0.01693+sy*0.03386)+'\n')
			fplan.write('Fill_1_2_'+str(sx+2*sy+4*z)+'\t0.012400\t0.00302\t'+str(sx*0.03012)+'\t'+str(0.01391+sy*0.03386)+'\n')
			fplan.write('Fill_1_3_'+str(sx+2*sy+4*z)+'\t0.012400\t0.00302\t'+str(0.015060+sx*0.03012)+'\t'+str(0.01391+sy*0.03386)+'\n')
			
			fplan.write('Fill_1_4_'+str(sx+2*sy+4*z)+'\t0.001330\t0.00151\t'+str(0.012400+sx*0.03012)+'\t'+str(0.01391+sy*0.03386)+'\n')
			fplan.write('Router_1_0_'+str(sx+2*sy+4*z)+'\t0.001330\t0.001330\t'+str(0.012400+sx*0.03012)+'\t'+str(0.01560+sy*0.03386)+'\n')
			fplan.write('TSV_1_0_'+str(sx+2*sy+4*z)+'\t0.001330\t0.000180\t'+str(0.012400+sx*0.03012)+'\t'+str(0.01542+sy*0.03386)+'\n')
			
			fplan.write('Fill_1_5_'+str(sx+2*sy+4*z)+'\t0.001330\t0.00151\t'+str(0.01373+sx*0.03012)+'\t'+str(0.01542+sy*0.03386)+'\n')
			fplan.write('Router_1_1_'+str(sx+2*sy+4*z)+'\t0.001330\t0.001330\t'+str(0.01373+sx*0.03012)+'\t'+str(0.01409+sy*0.03386)+'\n')
			fplan.write('TSV_1_1_'+str(sx+2*sy+4*z)+'\t0.001330\t0.000180\t'+str(0.01373+sx*0.03012)+'\t'+str(0.01391+sy*0.03386)+'\n')
			
			if(z!=layers-1):
				timtsv.write('TIM_unit_1_0_'+str(sx+2*sy+4*z)+'\t0.002660\t0.01391\t'+str(0.012400+sx*0.03012)+'\t'+str(sy*0.03386)+'\n')
				timtsv.write('TIM_unit_1_1_'+str(sx+2*sy+4*z)+'\t0.002660\t0.01391\t'+str(0.012400+sx*0.03012)+'\t'+str(0.01693+sy*0.03386)+'\n')
				timtsv.write('TIM_unit_1_2_'+str(sx+2*sy+4*z)+'\t0.012400\t0.00302\t'+str(sx*0.03012)+'\t'+str(0.01391+sy*0.03386)+'\n')
				timtsv.write('TIM_unit_1_3_'+str(sx+2*sy+4*z)+'\t0.012400\t0.00302\t'+str(0.015060+sx*0.03012)+'\t'+str(0.01391+sy*0.03386)+'\n')
			
				timtsv.write('TIM_unit_1_4_'+str(sx+2*sy+4*z)+'\t0.001330\t0.00151\t'+str(0.012400+sx*0.03012)+'\t'+str(0.01391+sy*0.03386)+'\n')
				timtsv.write('Filler_1_0_'+str(sx+2*sy+4*z)+'\t0.001330\t0.001330\t'+str(0.012400+sx*0.03012)+'\t'+str(0.01560+sy*0.03386)+'\n')
				timtsv.write('TIM_tsv_1_0_'+str(sx+2*sy+4*z)+'\t0.001330\t0.000180\t'+str(0.012400+sx*0.03012)+'\t'+str(0.01542+sy*0.03386)+'\n')
			
				timtsv.write('TIM_unit_1_5_'+str(sx+2*sy+4*z)+'\t0.001330\t0.00151\t'+str(0.01373+sx*0.03012)+'\t'+str(0.01542+sy*0.03386)+'\n')
				timtsv.write('Filler_1_1_'+str(sx+2*sy+4*z)+'\t0.001330\t0.001330\t'+str(0.01373+sx*0.03012)+'\t'+str(0.01409+sy*0.03386)+'\n')
				timtsv.write('TIM_tsv_1_1_'+str(sx+2*sy+4*z)+'\t0.001330\t0.000180\t'+str(0.01373+sx*0.03012)+'\t'+str(0.01391+sy*0.03386)+'\n')

				
				
				
	fplan.write('Fill_2_0_'+str(z)+'\t0.02746\t0.00302\t'+str(0.00000)+'\t'+str(0.03084)+'\n')
	fplan.write('Fill_2_1_'+str(z)+'\t0.02746\t0.00302\t'+str(0.03012)+'\t'+str(0.03084)+'\n')
	fplan.write('Fill_2_2_'+str(z)+'\t0.00266\t0.03084\t'+str(0.02746)+'\t'+str(0.00000)+'\n')
	fplan.write('Fill_2_3_'+str(z)+'\t0.00266\t0.03084\t'+str(0.02746)+'\t'+str(0.03386)+'\n')
	
	fplan.write('Router_2_0_'+str(z)+'\t0.001330\t0.001330\t'+str(0.02746)+'\t'+str(0.03102)+'\n')
	fplan.write('TSV_2_0_'+str(z)+'\t0.001330\t0.000180\t'+str(0.02746)+'\t'+str(0.03084)+'\n')
			
	fplan.write('Router_2_1_'+str(z)+'\t0.001330\t0.001330\t'+str(0.02746)+'\t'+str(0.03253)+'\n')
	fplan.write('TSV_2_1_'+str(z)+'\t0.001330\t0.000180\t'+str(0.02746)+'\t'+str(0.03235)+'\n')
	
	fplan.write('Router_2_2_'+str(z)+'\t0.001330\t0.001330\t'+str(0.02879)+'\t'+str(0.03102)+'\n')
	fplan.write('TSV_2_2_'+str(z)+'\t0.001330\t0.000180\t'+str(0.02879)+'\t'+str(0.03084)+'\n')
			
	fplan.write('Router_2_3_'+str(z)+'\t0.001330\t0.001330\t'+str(0.02879)+'\t'+str(0.03253)+'\n')
	fplan.write('TSV_2_3_'+str(z)+'\t0.001330\t0.000180\t'+str(0.02879)+'\t'+str(0.03235)+'\n')
	
			
	fplan.close()
	if(z!=layers-1):
		timtsv.write('TIM_unit_2_0_'+str(z)+'\t0.02746\t0.00302\t'+str(0.00000)+'\t'+str(0.03084)+'\n')
		timtsv.write('TIM_unit_2_1_'+str(z)+'\t0.02746\t0.00302\t'+str(0.03012)+'\t'+str(0.03084)+'\n')
		timtsv.write('TIM_unit_2_2_'+str(z)+'\t0.00266\t0.03084\t'+str(0.02746)+'\t'+str(0.00000)+'\n')
		timtsv.write('TIM_unit_2_3_'+str(z)+'\t0.00266\t0.03084\t'+str(0.02746)+'\t'+str(0.03386)+'\n')
	
		timtsv.write('Filler_2_0_'+str(z)+'\t0.001330\t0.001330\t'+str(0.02746)+'\t'+str(0.03102)+'\n')
		timtsv.write('TIM_tsv_2_0_'+str(z)+'\t0.001330\t0.000180\t'+str(0.02746)+'\t'+str(0.03084)+'\n')
			
		timtsv.write('Filler_2_1_'+str(z)+'\t0.001330\t0.001330\t'+str(0.02746)+'\t'+str(0.03253)+'\n')
		timtsv.write('TIM_tsv_2_1_'+str(z)+'\t0.001330\t0.000180\t'+str(0.02746)+'\t'+str(0.03235)+'\n')
	
		timtsv.write('Filler_2_2_'+str(z)+'\t0.001330\t0.001330\t'+str(0.02879)+'\t'+str(0.03102)+'\n')
		timtsv.write('TIM_tsv_2_2_'+str(z)+'\t0.001330\t0.000180\t'+str(0.02879)+'\t'+str(0.03084)+'\n')
			
		timtsv.write('Filler_2_3_'+str(z)+'\t0.001330\t0.001330\t'+str(0.02879)+'\t'+str(0.03253)+'\n')
		timtsv.write('TIM_tsv_2_3_'+str(z)+'\t0.001330\t0.000180\t'+str(0.02879)+'\t'+str(0.03235)+'\n')
	
		timtsv.close()
		   

tim = open('BFT_TIM_layer.flp','w')
tim.write('TIM_1\t'+str(0.05758)+'\t'+str(0.0647)+'\t0.000000\t0.000000\n')
tim.close()	
import csv 
import array 
# csv file name 
filename = "TemP_power.csv"
import numpy as np 
# initializing the titles and rows list 
fields = [] 
rows1 = [] 
with open(filename, 'r') as csvfile: 
    # creating a csv reader object 
    csvreader = csv.reader(csvfile) 
      
    # extracting field names through first row 
    fields = csvreader.next() 
  
    # extracting each data row one by one 
    for row in csvreader: 
        rows1.append(row) 
myList=[]
for row in rows1[:1]: 
    # parsing each column of a row 
  for col in row: 
  	myList.append((col))
  	#c=myList
#print(myList)	
#price = float(myList[2])
i=0;

import pandas as pd
from collections import OrderedDict
elements = OrderedDict()
df = pd.read_csv('gcc.ptrace',sep='\t')
for z in range(layers):

	for sy in range(2):
		for sx in range(2):
			for y in range(rows):
				for x in range(cmesh):
					for j in range(2):
						for i in range(2):

							elements['Icache_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] =  list(df['Icache'])
							elements['Dcache_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['Dcache'])
							elements['Bpred_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['Bpred_0'])
							elements['Bpred_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['Bpred_1'])
							elements['Bpred_2_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['Bpred_2'])
							elements['DTB_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['DTB_0'])
							elements['DTB_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['DTB_1'])
							elements['DTB_2_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['DTB_2'])
							elements['FPAdd_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['FPAdd_0'])
							elements['FPAdd_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['FPAdd_1'])
							elements['FPReg_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['FPReg_0'])
							elements['FPReg_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['FPReg_1'])
							elements['FPReg_2_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['FPReg_2'])
							elements['FPReg_3_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['FPReg_3'])
							elements['FPMul_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['FPMul_0'])
							elements['FPMul_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['FPMul_1'])
							elements['FPMap_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['FPMap_0'])
							elements['FPMap_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['FPMap_1'])
							elements['IntMap_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['IntMap'])
							elements['IntQ_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['IntQ'])
							elements['IntReg_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['IntReg_0'])
							elements['IntReg_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['IntReg_1'])
							elements['IntExec_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['IntExec'])
							elements['FPQ_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['FPQ'])
							elements['LdStQ_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['LdStQ'])
							elements['ITB_0_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['ITB_0'])
							elements['ITB_1_'+str(i+2*j+4*x+cmesh*4*y+rows*cmesh*4*sx+2*rows*cmesh*4*sy+4*rows*cmesh*4*z)] = list(df['ITB_1'])
					elements['Router_'+str(x+cmesh*y+rows*cmesh*sx+2*rows*cmesh*sy+4*rows*cmesh*z)] = [float(myList[i])]*100
					i=i+1
			 		elements['TSV_'+str(x+cmesh*y+rows*cmesh*sx+2*rows*cmesh*sy+4*rows*cmesh*z)] = [0.0005376]*100
					elements['Fill_0_'+str(x+cmesh*y+rows*cmesh*sx+2*rows*cmesh*sy+4*rows*cmesh*z)] =	[0]*100	
					elements['Fill_1_'+str(x+cmesh*y+rows*cmesh*sx+2*rows*cmesh*sy+4*rows*cmesh*z)] =	[0] *100
					
			elements['Fill_1_0_'+str(sx+2*sy+4*z)] = [0]*100
			elements['Fill_1_1_'+str(sx+2*sy+4*z)] = [0]*100
			elements['Fill_1_2_'+str(sx+2*sy+4*z)] = [0]*100
			elements['Fill_1_3_'+str(sx+2*sy+4*z)] = [0]*100
			
			elements['Fill_1_4_'+str(sx+2*sy+4*z)] = [0]*100
			elements['Router_1_0_'+str(sx+2*sy+4*z)] = [float(myList[i])]*100
			i=i+1
			elements['TSV_1_0_'+str(sx+2*sy+4*z)] = [0.0005376]*100
			
			elements['Fill_1_5_'+str(sx+2*sy+4*z)] = [0]*100
			elements['Router_1_1_'+str(sx+2*sy+4*z)] = [float(myList[i])]*100
			i=i+1
			elements['TSV_1_1_'+str(sx+2*sy+4*z)] = [0.0005376]*100
			
	elements['Fill_2_0_'+str(z)] =  [0]*100
	elements['Fill_2_1_'+str(z)] =  [0]*100
	elements['Fill_2_2_'+str(z)] =  [0]*100
	elements['Fill_2_3_'+str(z)] =  [0]*100
	
	elements['Router_2_0_'+str(z)] =  [float(myList[i])]*100
	i=i+1
	elements['TSV_2_0_'+str(z)] =  [0.0005376]*100
	elements['Router_2_1_'+str(z)] =  [float(myList[i])]*100
	i=i+1
	elements['TSV_2_1_'+str(z)] =  [0.0005376]*100
	elements['Router_2_2_'+str(z)] =  [float(myList[i])]*100
	i=i+1
	elements['TSV_2_2_'+str(z)] =  [0.0005376]*100
	elements['Router_2_3_'+str(z)] =  [float(myList[i])]*100
	i=i+1
	elements['TSV_2_3_'+str(z)] =  [0.0005376]*100
	
					
pd.DataFrame(elements).to_csv('new_BFT.ptrace',sep='\t',index=False)

