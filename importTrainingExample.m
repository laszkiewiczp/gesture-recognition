%This function returns a matrix whose rows correspond to the acceleration
%vector in instants of time [ax, ay, az]

function [A] = importTrainingExample(n_gesture, n_ex)

dir = sprintf('gesture-data/Gesture %d/%d.txt', n_gesture, n_ex);

A = importdata(dir);
A = A.*(9.81/1024);
end