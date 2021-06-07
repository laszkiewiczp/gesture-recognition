#This script allows for finding the best SVM parameters

import pandas as pd
import numpy as np
from sklearn.svm import SVC
from sklearn.model_selection import GridSearchCV, PredefinedSplit
from sklearn.metrics import accuracy_score, make_scorer, classification_report

trainData = pd.read_csv("trainData.txt", delimiter = ",", header = None)
evaluateData = pd.read_csv("evaluateData.txt", delimiter = ",", header = None)

m, n = trainData.shape # m - number of training examples, (n-1) - number of features
evalM = len(evaluateData) # get number of examples from evaluation set

# This part is used to divide the data into train, test, and validate sets

trainX = trainData.loc[:, 0:(n-2)]  
trainY = trainData.loc[:, (n-1)]

testX = evaluateData.loc[0:(np.floor(evalM/2) - 1), 0:(n-2)]
testY = evaluateData.loc[0:(np.floor(evalM/2) - 1), (n-1)]

validateX = evaluateData.loc[(np.floor(evalM/2)):, 0:(n-2)]
validateY = evaluateData.loc[(np.floor(evalM/2)):, (n-1)]

trainTestX = pd.concat([trainX, testX])
trainTestY = pd.concat([trainY, testY])

train_indices = np.full((m,), -1, dtype = int)
test_indices = np.full(((int(np.floor(evalM/2))),), 0, dtype = int)
test_fold = np.append(train_indices, test_indices)

ps = PredefinedSplit(test_fold)

# Creating SVM models for choosing best parameters

tuned_parameters = {'decision_function_shape' : ['ovo'], 'kernel' : ['linear'], 'gamma' : [1e-3], 
                    'C' : [0.1, 0.3, 1, 3, 10, 30]}

clf = GridSearchCV(estimator = SVC(), param_grid = tuned_parameters, scoring = make_scorer(accuracy_score), n_jobs = -1, cv = ps)
clf.fit(trainTestX, trainTestY)

#Output part

means = clf.cv_results_['mean_test_score']
stds = clf.cv_results_['std_test_score']
for mean, std, params in zip(means, stds, clf.cv_results_['params']):
    print("%0.3f (+/-%0.03f) for %r" %(mean, std * 2, params))
print()
print("Best parameters set found on development set:")
print()
print(clf.best_params_)
print("Detailed classification report:")
print()
print("The model is trained on the full development set.")
print("The scores are computed on the full evaluation set.")
print()
validateY, predY = validateY, clf.predict(validateX)
print(classification_report(validateY, predY))
print()