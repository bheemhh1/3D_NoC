import pandas as pd
import numpy as np

df = pd.read_csv('3DBFT2layerresult',sep='\t')
#df2 = pd.read_csv('cmeshstat',sep='\t')
import matplotlib.pyplot as plt

'''
mesh_max = np.array(df1['Max'])
meshshift_max = np.array(df2['Max'])

mesh_max = sum(mesh_max.tolist())/len(mesh_max.tolist())
meshshift_max = sum(meshshift_max.tolist())/len(meshshift_max.tolist())

print ((meshshift_max-273) - (mesh_max-273))/(mesh_max-273)
'''


ax1 = df.plot('Router','Max',style='ro-',fontsize=15)
ax2 = df.plot('Router','Center',style='y^-',ax=ax1,fontsize=15)
ax3 = df.plot('Router','Avg',color='green',ax=ax2,fontsize=15)
ax4 = df.plot('Router','Min',style='bs-',ax=ax3,fontsize=15)
ax4.legend()


plt.ylabel('Circuit element Temperature(in degree Kelvin)',size=15)
plt.xticks(df.index, df['Router'], rotation=90)

plt.show()

