%Script to Run Solution to HW2.2
%% Setup of data
%format long;
%import text data
A = importdata('zipcode.txt', '\t');

%get the zip codes
zip = A.data(:,1);

%get the populations and analyze density
pop = A.data(:,2);

density = pop/sum(pop); %population prior probability P(Z=z)

%% Answer Most Population? & Do Bayes Rule Computation
%Find the five most populated zip codes, and calculate population densities
% orderPop = sort(pop, 'descend');
% orderPop = orderPop(1:5);
% 
% %Top 5 populated zip codes
% topFive = find(A.data >= orderPop(5));

probE = zeros(1, length(zip)); %initialize P(D=di | Z=z) vector
numerator = zeros(1, length(zip));
probD = zeros(length(zip),10);   %initialize a 1x10 vector
denominator = 0;
parsezip = zeros(5,1);
posterior = zeros(1, length(zip));
predictive = zeros(10,1);


correctDigits = [-1, -1, 7, 0, 3];
wrongDigits = [4, 5, 8, 9];
%%

%For loop to calculate posterior probabilities + handle predictive prob at
%the same time
for i=1:length(zip)
    %convert to string and parse it into parsezip to hold all digits in
    %that zip code
    string = num2str(zip(i));
    if(length(string)== 4)
        string = strcat('0', string);
    end
    parsezip(1) = str2double(string(1));
    parsezip(2) = str2double(string(2));
    parsezip(3) = str2double(string(3));
    parsezip(4) = str2double(string(4));
    parsezip(5) = str2double(string(5));    
        
    %posterior Solve for P(E|Z=z)
    probE(i) = analyzeZip (parsezip, correctDigits, wrongDigits); 
    
    %->numerator of posterior
    numerator(i) = probE(i)*density(i); 
    
    %->denominator of posterior
    denominator = denominator + probE(i)*density(i);
    
    %loop through digits 0->9
    for kk=1:10
        if ismember(kk-1, parsezip)
            probD(i, kk) = 1;
        else
            probD(i, kk) = 0;
        end
    end    
end

%posterior
posterior = numerator/denominator;

%predictive
predictive = transpose(probD)*transpose(posterior);