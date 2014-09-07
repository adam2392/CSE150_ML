 % Problem 6.1: Viterbi Algorithm for Speech Recognition
% Random Variables: 
%   - St = {1,2,...,26}
%   - Ot = {0, 1}
%                          
% Function input: 
%   - initialState = 'initialStateDistribution.txt'
%   - transitionMatrix = 'transitionMatrix.txt'
%   - emissionMatrix = 'emissionMatrix.txt'
%   - observations = 'observations.txt'
%
% Output: 
%   - Viterbi algorithm to compute most probable sequence of 
%       hidden states conditioned on the particular sequence
%       of observations.

A = 'initialStateDistribution.txt';
B = 'transitionMatrix.txt';
C = 'emissionMatrix.txt';
D = 'observations.txt';

initialState = importdata(A);
transitionMatrix = importdata(B);
emissionMatrix = importdata(C);
observations = importdata(D);

n = 26;         %# of hidden states

L = zeros(n, length(observations));
Ltrack = zeros(1, length(observations));

%% base case 1st column
logpi = log(initialState);
logbi = log(emissionMatrix);

logaij = log(transitionMatrix);

%create the first column of the L matrix
if observations(1)==0
    L(:,1) = logpi + logbi(:, 1);
else
    L(:,1) = logpi + logbi(:, 2);
end

%get indices of max 
Ltrack(1) = find(L(:,1)==max(L(:,1)));

%% from time t to time t+1
%fill in matrix L
for i=2:length(observations)    
    for j=1:26
        L(j,i) = max(L(:,i-1)+transpose(logaij(j,:)));
    end
    
    %add logbj(O(t+1)) depending on what the observation is
    if observations(i)==0
        L(:,i) = L(:, i) + logbi(:, 1);
    else
        L(:,i) = L(:, i) + logbi(:, 2);
    end
    
    %get indices of max
    %if i~=length(observations)
        temp = find(L(:,i)==max(L(:,i)));
        Ltrack(i) = temp(1);
    %end
end

%most likeley sequence
phit = zeros(1,length(observations));
k = 1;

for i=1:length(observations)
    if i==1
        phit(k) = Ltrack(i);
        k = k+1;
    else
        if phit(k-1) == Ltrack(i)
        else
            phit(k) = Ltrack(i);
            k = k+1;
        end
    end
end
  
time = 1:48000;

plot(time,Ltrack); 