%This function is used to normalize the signal with respect to its own

function [signal] = normalizeSignal(signal)

mi = mean(signal, 1);
sigma = std(signal, 0, 1);

r = size(signal, 1);
MI = [];
SIGMA = [];

for i = 1:r
    MI = [MI; mi];
    SIGMA = [SIGMA; sigma];
end

signal = (signal - MI)./SIGMA;

end