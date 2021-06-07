%This function computes derivatives of all the acceleration components over
%time. The input is a matrix containing acceleration data in the form of
%[ax, ay, az] being row vectors representing the acceleration components in
%an instant of time

function [grad] = computeGradient(accData)

ax = accData(:, 1);
ay = accData(:, 2);
az = accData(:, 3);

grad_x = gradient(ax);
grad_y = gradient(ay);
grad_z = gradient(az);

grad = [grad_x, grad_y, grad_z];

end