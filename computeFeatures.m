%This function produces features from the acceleration signal

function [features] = computeFeatures(accData)

gradients = computeGradient(accData);

accData = normalizeSignal(accData);
gradients = normalizeSignal(gradients);

[acc1, acc2, acc3, acc4] = cutData(accData);
[grad1, grad2, grad3, grad4] = cutData(gradients);

meanAcc1 = mean(acc1, 1);
meanAcc2 = mean(acc2, 1);
meanAcc3 = mean(acc3, 1);
meanAcc4 = mean(acc4, 1);

meanGrad1 = mean(grad1, 1);
meanGrad2 = mean(grad2, 1);
meanGrad3 = mean(grad3, 1);
meanGrad4 = mean(grad4, 1);

stdAcc1 = std(acc1, 0, 1);
stdAcc2 = std(acc2, 0, 1);
stdAcc3 = std(acc3, 0, 1);
stdAcc4 = std(acc4, 0, 1);

stdGrad1 = std(grad1, 0, 1);
stdGrad2 = std(grad2, 0, 1);
stdGrad3 = std(grad3, 0, 1);
stdGrad4 = std(grad4, 0, 1);


features = [meanAcc1, meanAcc2, meanAcc3, meanAcc4, meanGrad1, meanGrad2, meanGrad3, meanGrad4, stdAcc1, stdAcc2, stdAcc3, stdAcc4, stdGrad1, stdGrad2, stdGrad3, stdGrad4];

end