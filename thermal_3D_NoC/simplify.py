import pandas as pd
df1 = pd.read_csv('min.steady',sep='\t')
df2 = pd.read_csv('max.steady',sep='\t')
df3 = pd.read_csv('avg.steady',sep='\t')
df4 = pd.read_csv('center.steady',sep='\t')

r2 = df2.iloc[:,1]
r3 = df3.iloc[:,1]
r4 = df4.iloc[:,1]
df = df1.join(r2).join(r3).join(r4)
df.to_csv('result',sep ='\t',index=False)
