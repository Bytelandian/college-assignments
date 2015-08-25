clear all
clc

load('credit.mat')
input=data;
output=label;
[m,n]=size(input);
counta=1;
countb=1;
for i=1:m
    if output(i)==1
        a(counta,1)=input(i,1);
        a(counta,2)=input(i,2);
        counta=counta+1;
    else
        b(countb,1)=input(i,1);
        b(countb,2)=input(i,2);
        countb=countb+1;
    end
end
scatter(a(:,1),a(:,2),'o')
hold on
scatter(b(:,1),b(:,2),'x')   
xlabel('x1')
ylabel('x2')
title('Dataset and Non-Linear Decision Boundary')

for i=1:10
    w1(i,1)=-0.1 + (0.2) * rand();
end
input=featuretransform(input,3);
features=9;
options = optimset('GradObj', 'on', 'MaxIter', 100);
[w objval] = fminunc(@(w)(objgradcompute(w, input, output,0)), w1, options)
plotdecisionboundary(w, input,output)



figure
scatter(a(:,1),a(:,2),'o')
hold on
scatter(b(:,1),b(:,2),'x') 
xlabel('x1')
ylabel('x2')
title('Dataset and Discriminant Function Decision Boundary')
lindiscriminant(input,output);