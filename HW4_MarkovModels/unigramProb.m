%Problem 4.2a
%Compute the maximum likelihood estimate of the
%unigram distribution in the file 'unigram.txt'
%Function input: 'unigram.txt'
%Output: Table of all words w that start w/ letter A
%       Along w/ unigram probabilities

function [T, probUni] = unigramProb (file, vocabFile, letter)

%     file = 'unigram.txt';
%     vocabFile = 'vocab.txt';

    A = importdata(file);
    B = importdata(vocabFile);

    wordArray = zeros(500,1);   %Array to hold whether a word starts w/ 'A'
    
    for i=1:length(B)
        %Check if the first letter is 'A'
        if B{i}(1) == letter
            wordArray(i) = 1;
        end
    end

    %Find the indices that satisfy condition of first letter being 'A'
    foundIndices = find(wordArray > 0);

    %Output
    T = B(foundIndices);
    probUni = A(foundIndices) / sum(A);
end