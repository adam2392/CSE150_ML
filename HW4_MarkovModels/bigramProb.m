%Problem 4.2b
%Compute the maximum likelihood estimate of the
%bi distribution in the file 'bigram.txt'
%Function input: 
%       - file = 'bigram.txt'
%       - vocabFile = 'vocab.txt'
%       - letter = 'THE'
%Output: Table of 10 most likely words w' that follow word 'THE'
%       Along w/ bigram probabilities

function [T, probBi] = bigramProb (file, vocabFile, word)
%     file = 'bigram.txt';
%     vocabFile = 'vocab.txt';
%     word = 'THE';
    %import the data
    A = importdata(file);
    B = importdata(vocabFile);
    
    w1 = A(:,1);    %index(word 1) 
    w2 = A(:,2);    %index(word 2)
    count = A(:,3); %counts(w1, w2)
   
    indexofWord = find(ismember(B, word)); %find the index for the word
    indices = find(w1==indexofWord);       %find row #'s of that indexed word
    
    %find the indices of all the words after indexed 'word'
    wordAfter = w2(indices);
    
    %get the counts(word, wordAfter)
    count = count(indices);

    orderCount = sort(count, 'descend'); %get the top 10 words
    topten = count>=orderCount(10);%get the top 10 word's index
    
    %get the top ten wordAfters
    T = B(wordAfter(topten));

    %get the top
    probBi = orderCount(1:10) / sum(count);
end
