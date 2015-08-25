function [ a ] = featuretransform(X, degree)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
    
    [m,n]=size(X);
    a(:,1)=ones(m,1);
    count=2;
    for i=1:degree
        for x=0:i
            a(:,count)=(X(:,2).^x).*(X(:,1).^(i-x));
            count=count+1;
        end
    end

end

