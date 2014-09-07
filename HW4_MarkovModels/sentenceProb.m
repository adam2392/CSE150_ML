%Problem 4.2c and d and e
%Considering the sentence "<s>The stock market fell by one hundred
% points last week."
%Compare log likelihoods w/ unigram and bigram model and mixture model
%
%Function input: 
%       - unifile = 'unigram.txt'
%       - bifile = 'bigram.txt'
%       - vocabFile = 'vocab.txt'
%       - phrase = '<s>The stock market fell by one hundred
% points last week.'
%
%Output: 
%   -log likelihoods of unigram and bigram model: Lu and Lb

function [Lu, Lb, optimalLambda] = sentenceProb (unifile, bifile, vocabFile, phrase)
%     unifile = 'unigram.txt';
%     bifile = 'bigram.txt';
%     vocabFile = 'vocab.txt';
%     %phrase = '<s> THE STOCK MARKET FELL BY ONE HUNDRED POINTS LAST WEEK.';
%     phrase = '<s> THE SIXTEEN OFFICIALS SOLD FIRE INSURANCE.';
    
    %import the data
    unigram = importdata(unifile);
    bigram = importdata(bifile);
    vocab = importdata(vocabFile);
    
    %get count(w1,w2)
    count = bigram(:,3); %counts(w1, w2)
   
    %Find the spaces in the sentence
    space = find(phrase == ' ');
    
    %Make space into a nonsense vector of length 1
    if isempty(space)
        space = 0;
    end
    
    %Vectors to store probUni and probBi and probMix
    probUni = zeros(length(space),1);
    probBi = zeros(length(space),1);
    probMix = zeros(length(space),1);
    
    %weight
    lambda = 0:0.01:1;
    
    %initialization of log-likelihood of mixture model vector
    Lm = zeros(length(lambda), 1);

    for h=1:length(lambda)
        %loop through each space
        for i=1:length(space)
            %Check to see if we already calculated all the probabilities
            %saves time -> skip straight to Lm calculation
            if h==1
                %check if this is the first space
                %and get the next word
                if(i==1)
                    %only one word
                    if space == 0
                        word = phrase(1:end-1);
                    elseif length(space) == 1
                        word = phrase(1:space(i)-1);
                        nextword = phrase(space(i)+1:end-1);
                    else
                        word = phrase(1:space(i)-1);
                        nextword = phrase(space(i)+1:space(i+1)-1);
                    end
                elseif(i<length(space))
                    word = phrase(space(i-1)+1:space(i)-1);
                    nextword = phrase(space(i)+1:space(i+1)-1);
                else
                    word = phrase(space(i-1)+1:space(i)-1);
                    nextword = phrase(space(i)+1:end-1);
                end

                %% Unigram model
                %find the word
                if i==1
                    %Check if it is only a single word
                    if space == 0
                        index = ismember(vocab, word);
                        probUni(i) = unigram(index) / sum(unigram);
                    end
                else
                    index = ismember(vocab, word);
                    probUni(i-1) = unigram(index) / sum(unigram); 
                end

                %% Bigram model
                if space == 0
                    %Single word, do nothing
                else
                    %index finds word
                    index = find(ismember(vocab, word));

                    %find the next word index
                    nextIndex = find(ismember(vocab, nextword));

                    indices = bigram(:,1)==index;%find row #'s of that indexed word
                    counts = count(indices); %get the counts(word, nextword)

                    %get the row # in bigram that satisfies 'index' and 'nextIndex'
                    found = find(bigram(:,1)==index & bigram(:,2)==nextIndex);

                    c = bigram(found,3);    %this is the count for nextword|word
                    if isempty(found)
                        probBi(i) = 0;
                    else
                        probBi(i) = c/sum(counts);
                    end
                end

                %Reached end of the phrase
                if space == 0
                    period = find(phrase == '.');   
                elseif i==length(space)
                    %find the last word for Unigram model
                    period = find(phrase  == '.');
                    word = phrase(space(end)+1:period-1);
                    %find the word
                    index = ismember(vocab, word);
                    probUni(end) = unigram(index) / sum(unigram);
                end
            end %end of if statement to handle all the probability computations for Pu and Pb

            %% Mixture Model
            if i>1
                probMix(i-1) = (1-lambda(h))*probUni(i-1) + lambda(h)*probBi(i-1);

                if i==length(space) %check if this is last iteration
                    probMix(end) = (1-lambda(h))*probUni(end) + lambda(h)*probBi(end);
                end
            end
        end %end of looop through sentence
        Lm(h) = log(prod(probMix)); %some value of Lh based on the current iteration of lambda
    end  
    Lu = log(prod(probUni));
    Lb = log(prod(probBi)); 
    
    %plot lambda vs Lm to find optimum lambda with maximum Lm
    plot(lambda, Lm);
    xlabel('lambda 0:1');
    ylabel('Log-likelihood Lm');
    title('Lm vs. lambda');
    
    maxindex = Lm == max(Lm);
    optimalLambda = lambda(maxindex);
end