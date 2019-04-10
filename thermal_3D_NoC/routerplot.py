import pandas as pd
res = open('result','r')
new = open('3DBFT2layerresult','w')
new.write('Router\tMin\tMax\tAvg\tCenter\n')
for line in res:
	if 'Router' in line:
		new.write('R'+line[line.find('Router')+6:])
res.close()
new.close()		

#pd.Dataframe
#line[line.find('\t')+1:]
		
