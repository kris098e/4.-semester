from sklearn import datasets # import sklearn datasets

iris = datasets.load_iris() # load iris dataset
x = iris.data               # a key
y = iris.target             # a key
# print(iris.keys()) / prints keys
print(x.shape, y.shape)


import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

data = np.hstack([x, y.reshape(-1,1)])
df = pd.DataFrame(data, columns=iris.feature_names + ['species'])
sns.pairplot(df, hue='species', height=2.5) # plot pairplot
