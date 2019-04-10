cores = 8
rows = 4
layers = 2

for z in range(layers):
	filename = 'shift_core_layer'+str(z)
	fplan = open(filename+'.flp','w')
	if(z!=layers-1):
		timtsv = open('shift_timtsv'+str(z)+'.flp','w')
	
	for y in range(rows):
		for x in range(cores):
			fplan.write('Icache_'+str(x+cores*y+rows*cores*z)+'\t0.003100\t0.002600\t'+str(x*0.006200)+'\t'+str(0.001280+y*0.007480)+'\n')
			fplan.write('Dcache_'+str(x+cores*y+rows*cores*z)+'\t0.003100\t0.002600\t'+str(0.003100+x*0.006200)+'\t'+str(0.001280+y*0.007480)+'\n')
			fplan.write('Bpred_0_'+str(x+cores*y+rows*cores*z)+'\t0.001033\t0.000700\t'+str(x*0.006200)+'\t'+str(0.003880+y*0.007480)+'\n')
			fplan.write('Bpred_1_'+str(x+cores*y+rows*cores*z)+'\t0.001033\t0.000700\t'+str(0.001033+x*0.006200)+'\t'+str(0.003880+y*0.007480)+'\n')
			fplan.write('Bpred_2_'+str(x+cores*y+rows*cores*z)+'\t0.001033\t0.000700\t'+str(0.002067+x*0.006200)+'\t'+str(0.003880+y*0.007480)+'\n')
			fplan.write('DTB_0_'+str(x+cores*y+rows*cores*z)+'\t0.001033\t0.000700\t'+str(0.003100+x*0.006200)+'\t'+str(0.003880+y*0.007480)+'\n')
			fplan.write('DTB_1_'+str(x+cores*y+rows*cores*z)+'\t0.001033\t0.000700\t'+str(0.004133+x*0.006200)+'\t'+str(0.003880+y*0.007480)+'\n')
			fplan.write('DTB_2_'+str(x+cores*y+rows*cores*z)+'\t0.001033\t0.000700\t'+str(0.005167+x*0.006200)+'\t'+str(0.003880+y*0.007480)+'\n')
			fplan.write('FPAdd_0_'+str(x+cores*y+rows*cores*z)+'\t0.001100\t0.000900\t'+str(x*0.006200)+'\t'+str(0.004580+y*0.007480)+'\n')
			fplan.write('FPAdd_1_'+str(x+cores*y+rows*cores*z)+'\t0.001100\t0.000900\t'+str(0.001100+x*0.006200)+'\t'+str(0.004580+y*0.007480)+'\n')
			fplan.write('FPReg_0_'+str(x+cores*y+rows*cores*z)+'\t0.000550\t0.000380\t'+str(x*0.006200)+'\t'+str(0.005480+y*0.007480)+'\n')
			fplan.write('FPReg_1_'+str(x+cores*y+rows*cores*z)+'\t0.000550\t0.000380\t'+str(0.000550+x*0.006200)+'\t'+str(0.005480+y*0.007480)+'\n')
			fplan.write('FPReg_2_'+str(x+cores*y+rows*cores*z)+'\t0.000550\t0.000380\t'+str(0.001100+x*0.006200)+'\t'+str(0.005480+y*0.007480)+'\n')
			fplan.write('FPReg_3_'+str(x+cores*y+rows*cores*z)+'\t0.000550\t0.000380\t'+str(0.001650+x*0.006200)+'\t'+str(0.005480+y*0.007480)+'\n')		
			fplan.write('FPMul_0_'+str(x+cores*y+rows*cores*z)+'\t0.001100\t0.000950\t'+str(x*0.006200)+'\t'+str(0.005860+y*0.007480)+'\n')
			fplan.write('FPMul_1_'+str(x+cores*y+rows*cores*z)+'\t0.001100\t0.000950\t'+str(0.001100+x*0.006200)+'\t'+str(0.005860+y*0.007480)+'\n')
			fplan.write('FPMap_0_'+str(x+cores*y+rows*cores*z)+'\t0.001100\t0.000670\t'+str(x*0.006200)+'\t'+str(0.006810+y*0.007480)+'\n')
			fplan.write('FPMap_1_'+str(x+cores*y+rows*cores*z)+'\t0.001100\t0.000670\t'+str(0.001100+x*0.006200)+'\t'+str(0.006810+y*0.007480)+'\n')
			fplan.write('IntMap_'+str(x+cores*y+rows*cores*z)+'\t0.000900\t0.001350\t'+str(0.002200+x*0.006200)+'\t'+str(0.006130+y*0.007480)+'\n')		
			fplan.write('IntQ_'+str(x+cores*y+rows*cores*z)+'\t0.001300\t0.001350\t'+str(0.003100+x*0.006200)+'\t'+str(0.006130+y*0.007480)+'\n')
			fplan.write('IntExec_'+str(x+cores*y+rows*cores*z)+'\t0.001800\t0.002230\t'+str(0.004400+x*0.006200)+'\t'+str(0.004580+y*0.007480)+'\n')
			fplan.write('FPQ_'+str(x+cores*y+rows*cores*z)+'\t0.000900\t0.001550\t'+str(0.002200+x*0.006200)+'\t'+str(0.004580+y*0.007480)+'\n')
			fplan.write('LdStQ_'+str(x+cores*y+rows*cores*z)+'\t0.001300\t0.000950\t'+str(0.003100+x*0.006200)+'\t'+str(0.005180+y*0.007480)+'\n')
			fplan.write('ITB_0_'+str(x+cores*y+rows*cores*z)+'\t0.000650\t0.000600\t'+str(0.003100+x*0.006200)+'\t'+str(0.004580+y*0.007480)+'\n')
			fplan.write('ITB_1_'+str(x+cores*y+rows*cores*z)+'\t0.000650\t0.000600\t'+str(0.003750+x*0.006200)+'\t'+str(0.004580+y*0.007480)+'\n')
			fplan.write('IntReg_0_'+str(x+cores*y+rows*cores*z)+'\t0.000900\t0.000670\t'+str(0.004400+x*0.006200)+'\t'+str(0.006810+y*0.007480)+'\n')
			fplan.write('IntReg_1_'+str(x+cores*y+rows*cores*z)+'\t0.000900\t0.000670\t'+str(0.005300+x*0.006200)+'\t'+str(0.006810+y*0.007480)+'\n')
			fplan.write('Router_'+str(x+cores*y+rows*cores*z)+'\t0.001100\t0.001100\t'+str(0.002550+x*0.006200)+'\t'+str(0.000180+y*0.007480)+'\n')
			fplan.write('TSV_'+str(x+cores*y+rows*cores*z)+'\t0.001100\t0.000180\t'+str(0.002550+x*0.006200)+'\t'+str(y*0.007480)+'\n')
			fplan.write('Fill_0_'+str(x+cores*y+rows*cores*z)+'\t0.002550\t0.001280\t'+str(x*0.006200)+'\t'+str(y*0.007480)+'\n')
			fplan.write('Fill_1_'+str(x+cores*y+rows*cores*z)+'\t0.002550\t0.001280\t'+str(0.003650+x*0.006200)+'\t'+str(y*0.007480)+'\n')
			if(z!=layers-1):
				timtsv.write('TIM_unit_'+str(x+cores*y+rows*cores*z)+'\t0.006200\t0.007300\t'+str(x*0.006200)+'\t'+str(0.000180+y*0.007480)+'\n')
				timtsv.write('TIM_tsv_'+str(x+cores*y+rows*cores*z)+'\t0.001100\t0.000180\t'+str(0.002550+x*0.006200)+'\t'+str(y*0.007480)+'\n')
				timtsv.write('Filler_0_'+str(x+cores*y+rows*cores*z)+'\t0.002550\t0.000180\t'+str(x*0.006200)+'\t'+str(y*0.007480)+'\n')
				timtsv.write('Filler_1_'+str(x+cores*y+rows*cores*z)+'\t0.002550\t0.000180\t'+str(0.003650+x*0.006200)+'\t'+str(y*0.007480)+'\n')
	fplan.close()
	if(z!=layers-1):
		timtsv.close()

tim = open('shift_TIM_layer.flp','w')
tim.write('TIM_1\t'+str(cores*0.006200)+'\t'+str(rows*0.007480)+'\t0.000000\t0.000000\n')
tim.close()		
import pandas as pd
from collections import OrderedDict
elements = OrderedDict()
df = pd.read_csv('gcc.ptrace',sep='\t')


for z in range(layers):
	for y in range(rows):
		for x in range(cores):
			elements['Icache_'+str(x+cores*y+rows*cores*z)] = list(df['Icache']) 
			elements['Dcache_'+str(x+cores*y+rows*cores*z)] = list(df['Dcache'])
			elements['Bpred_0_'+str(x+cores*y+rows*cores*z)] = list(df['Bpred_0'])
			elements['Bpred_1_'+str(x+cores*y+rows*cores*z)] = list(df['Bpred_1'])
			elements['Bpred_2_'+str(x+cores*y+rows*cores*z)] = list(df['Bpred_2'])
			elements['DTB_0_'+str(x+cores*y+rows*cores*z)] = list(df['DTB_0'])
			elements['DTB_1_'+str(x+cores*y+rows*cores*z)] = list(df['DTB_1'])
			elements['DTB_2_'+str(x+cores*y+rows*cores*z)] = list(df['DTB_2'])
			elements['FPAdd_0_'+str(x+cores*y+rows*cores*z)] = list(df['FPAdd_0'])
			elements['FPAdd_1_'+str(x+cores*y+rows*cores*z)] = list(df['FPAdd_1'])
			elements['FPReg_0_'+str(x+cores*y+rows*cores*z)] = list(df['FPReg_0'])
			elements['FPReg_1_'+str(x+cores*y+rows*cores*z)] = list(df['FPReg_1'])
			elements['FPReg_2_'+str(x+cores*y+rows*cores*z)] = list(df['FPReg_2'])
			elements['FPReg_3_'+str(x+cores*y+rows*cores*z)] = list(df['FPReg_3'])
			elements['FPMul_0_'+str(x+cores*y+rows*cores*z)] = list(df['FPMul_0'])
			elements['FPMul_1_'+str(x+cores*y+rows*cores*z)] = list(df['FPMul_1'])
			elements['FPMap_0_'+str(x+cores*y+rows*cores*z)] = list(df['FPMap_0'])
			elements['FPMap_1_'+str(x+cores*y+rows*cores*z)] = list(df['FPMap_1'])
			elements['IntMap_'+str(x+cores*y+rows*cores*z)] = list(df['IntMap'])
			elements['IntQ_'+str(x+cores*y+rows*cores*z)] = list(df['IntQ'])
			elements['IntReg_0_'+str(x+cores*y+rows*cores*z)] = list(df['IntReg_0'])
			elements['IntReg_1_'+str(x+cores*y+rows*cores*z)] = list(df['IntReg_1'])
			elements['IntExec_'+str(x+cores*y+rows*cores*z)] = list(df['IntExec'])
			elements['FPQ_'+str(x+cores*y+rows*cores*z)] = list(df['FPQ'])
			elements['LdStQ_'+str(x+cores*y+rows*cores*z)] = list(df['LdStQ'])
			elements['ITB_0_'+str(x+cores*y+rows*cores*z)] = list(df['ITB_0'])
			elements['ITB_1_'+str(x+cores*y+rows*cores*z)] = list(df['ITB_1'])
			elements['Router_'+str(x+cores*y+rows*cores*z)] = [0.42]*100
	 		elements['TSV_'+str(x+cores*y+rows*cores*z)] = [0.0005376]*100
			elements['Fill_0_'+str(x+cores*y+rows*cores*z)] =	[0]*100
			elements['Fill_1_'+str(x+cores*y+rows*cores*z)] =	[0]*100	
		
pd.DataFrame(elements).to_csv('shift_core3D.ptrace',sep='\t',index=False)
