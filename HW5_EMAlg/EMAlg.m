% Problem 5.2: EM Algorithm for Noisy-OR Models
% Binary Random Variables: X ? {0, 1}^n
%                          Y ? {0, 1}
% Noisy-OR CPT = P(Y=1 | X) = 1 - product(1:n) (1-pi)^Xi
%   Noisy-OR Parameters: pi ? [0, 1]
% Function input: 
%   - xtext = 'x.txt'
%   - ytext = 'y.txt'
%
% Output: 
%   -EM algorithm that has log-likelihood probabilities and mistakes
%       for each iteration.
format long;

xtext = 'x.txt';
ytext = 'y.txt';

%import data in
X = importdata(xtext); %267 x 23 matrix
Y = importdata(ytext); %267 x 1 matrix

%parameters
T = 267;
n = 23;

%Used in n loop
pi = 1/n*ones(n,1);   %initialize pi
Ti = zeros(n, 1);   %number of examples where Xi=1

EMsum = 0;          %the summation in the EM update
prodCPT = ones(T, 1);%initialize P(Y=1|X)

%Used in 512 loop
L = zeros(512, 1);              %initialize log-likelihood
Lbuff = 0;
mistakes = zeros(512,1);        %initialize number of mistakes

%flags to check if log likelihood or CPT was calculated already
logged = 0;
CPTed = 0;
mistakecalc = 0;

for k=1:512
    for j=1:n
        %sum up the number of ex. where Xi=1; i=1:23
        count = X(:,j)==1;
        Ti(j) = sum(count);

        for i=1:T
            %% Part of the M step; CPT calculation 
            if CPTed == 0
                CPTbuffer = ones(n,1);              %initialize (1-pi)^X
                CPTbuffer = (CPTbuffer-pi);
                CPTbuffer = CPTbuffer.^transpose(X(i,:)); %(1-pi)^Xi | n x 1 vector
                prodCPT(i) = 1-prod(CPTbuffer);     %1- PI(1:n) CPTbuffer
            end

            %% Calculate SUM[logP(Y=yt | X=xt)]
            if logged == 0
                if Y(i) == 1
                    Lbuff = Lbuff + log(prodCPT(i));
                else
                    Lbuff = Lbuff + log(1-prodCPT(i));
                end    
            end
            
            %% Calculate # of Mistakes
            if mistakecalc == 0
                if Y(i) == 0 && prodCPT(i) >= 0.5   %false positive
                    mistakes(k) = mistakes(k) + 1;
                end
                if Y(i) == 1 && prodCPT(i) <= 0.5   %false negative
                    mistakes(k) = mistakes(k) + 1;
                end
            end
            
            %% Calculate pi EM Update
            EMsum = EMsum + Y(i)*X(i,j)*pi(j) / prodCPT(i);
        end
        CPTed = 1; %turn flag
        logged = 1; %turn flag
        mistakecalc = 1; %turn flag

        
        
        %EM update
        pi(j) = 1/Ti(j) * EMsum;

        %reset variables
        EMsum = 0;
        
    end
    L(k) = 1/T * Lbuff;
    
    %reset variables
    Lbuff = 0;
    
    %reset flags
    logged = 0;
    CPTed = 0; 
    mistakecalc = 0;
end