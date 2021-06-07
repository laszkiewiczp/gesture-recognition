%This function is used to divide the acceleration signal into four equally
%long pieces. Returns 4 arrays containing acceleration data as row vectors
%[ax, ay, az]

function [sig1, sig2, sig3, sig4] = cutData(signal)

n_pieces = 4; %the number of pieces that the signal will be divided into

[n_rows, ~] = size(signal);

piece_length = floor(n_rows/n_pieces);

sig1 = signal(1 : piece_length, :);
sig2 = signal((piece_length + 1) : (2 * piece_length), :);
sig3 = signal((2 * piece_length + 1) : (3 * piece_length), :);
sig4 = signal((3 * piece_length + 1) : end, :);

end