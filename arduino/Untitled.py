
# coding: utf-8

# In[1]:


from keras.models import Sequential
from keras.layers import Dense
import numpy
# fix random seed for reproducibility
numpy.random.seed(7)


# In[2]:


import pandas as pd
data = pd.read_csv("dataNeur.csv", names = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"])


# In[3]:


data.head()


# In[10]:


# split into input (X) and output (Y) variables
X = data[["1", "2", "3", "4", "5"]]
Y = data[["6", "7", "8", "9", "10"]]
X.head()


# In[5]:


# create model
model = Sequential()
model.add(Dense(5, input_dim=5, activation='relu'))
model.add(Dense(5, activation='relu'))
model.add(Dense(5, activation='sigmoid'))


# In[6]:


model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])


# In[8]:


model.fit(X, Y, epochs=10, batch_size=10)


# In[24]:


pred = model.predict(df)
pred


# In[21]:


d = {'1' : [0], 
     '2' : [300], 
     '3' : [0], 
     '4' : [0], 
     '5' : [0]}
df = pd.DataFrame(data=d)
df

