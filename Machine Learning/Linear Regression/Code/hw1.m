clear all
close all
clc

load('abalone.mat')             % Loading Data
a=abalone;
[m,n]=size(a);
a=[zeros(m,2) a ];
[m,n]=size(a);
for i=1:m                       %Transforming first attribute
    if (a(i,3)==0)
        a(i,1)=1;
        a(i,2)=0;
        a(i,3)=0;
    elseif (a(i,3)==1)
        a(i,1)=0;
        a(i,2)=1;
        a(i,3)=0;
    else
        a(i,1)=0;
        a(i,2)=0;
        a(i,3)=1;
    end
end
for i=1:n-1                         %Standardization
    me=mean(a(:,i));
    s=std(a(:,i));
    for j=1:m
        a(j,i)=(a(j,i)-me)/s;
    end
end

a=[ones(m,1) a];                %Adding 1st column of ones
input_data = a(:,1:11) ;
output_data = a(:,12);
[row,col]=size(input_data);

lambda=zeros(1,10);
for j=1:10
    lambda(j)=0.1*j;                %Various lambda Values
end

frac=zeros(1,9);
error_test=zeros(9,10);
error_train=zeros(9,10);

for l=1:100                 %100 iterations corresponding to values of frac and lambda

    for i=1:9

        frac(i)=i/10;               %frac Values
        index=randperm(row,row);
        rows=floor(row*frac(i));
        
        train_in=zeros(rows,col);           
        train_out=zeros(rows,1);
        test_in=zeros((row-rows),col);       
        test_out=zeros((row-rows),1);
        
        for k=1:rows                                    %Extracting training input and output 
            train_in(k,:)=input_data(index(k),:);
            train_out(k,:)=output_data(index(k),:);
        end
        for k=rows+1:row                                %Extracting testing input and output
            test_in(k-rows,:)=input_data(index(k),:);
            test_out(k-rows,:)=output_data(index(k),:);
        end
        for idx=2:col                                   %Standardize using training input variables.
            me=mean(train_in(:,idx));
            s=std(train_in(:,idx));
            for jdx=1:rows
                train_in(jdx,idx)=(train_in(jdx,idx)-me)/s;
            end
            for jdx=rows+1:row
                test_in(jdx-rows,idx)=(test_in(jdx-rows,idx)-me)/s;
            end
        end
        
          
        for j=1:10                %computation of weights , predictions and errors
            weights=mylinridgereg(train_in ,train_out ,lambda(j));
            predict_train=mylinridgeregeval(train_in, weights);
            predict_test=mylinridgeregeval(test_in, weights);
            error_test(i,j)=error_test(i,j)+meansquarederr(predict_test,test_out);
            error_train(i,j)=error_train(i,j)+meansquarederr(predict_train,train_out);
        end
    end
end

figure
error_test=error_test./100;             %taking average
error_train=error_train./100;

for i=1:9                               %Ploting Lambda vs training errors for all values of fraction
    subplot(3,3,i)
    plot(lambda,error_train(i,:),'r');
    xlabel('Lambda')
    ylabel('Training Errors')
    
    lower=min(min(error_train));
    upper=max(max(error_train));
    ylim([lower,upper]);
    title(sprintf('Fraction = %f',frac(i) ))
end

figure                          %Ploting Lambda vs testing  errors for all values of fraction
for i=1:9
    subplot(3,3,i)
    plot(lambda,error_test(i,:),'r');
    xlabel('Lambda')
    ylabel('Testing Errors')
    lower=min(min(error_test));
    upper=max(max(error_test));
    ylim([lower,upper]);
   title(sprintf('Fraction = %f',frac(i) ))
end

figure                              %Plotting minimum testing errors vs fraction
min_test_error=zeros(1,9);
for i=1:9
    min_test_error(i)=min(error_test(i,:));
end
plot(frac,min_test_error)

xlabel('Fraction')
ylabel('Minimum Testing Error')
title('Minimum Testing Errors for the corresponding value of a fraction')

figure
lambda_min=zeros(9);                %Plotting lambda corresponding to minimum testing errors vs fraction
for i=1:9
    [e1,i1]=min(error_test(i,:));
    lambda_min(i)=lambda(i1);
end
plot(frac,lambda_min)
xlabel('Fraction')
ylabel('Lambda For minimum testing erros')
title('Lambda values corresponding to a fraction for the minimum Testing Errors')

[e1,i1]=min(error_test);                        %best choice of lambda and fraction
[a1,b1]=min(e1);
total_min_error=error_test(i1(1,b1),b1);
min_error_frac=i1(1,b1)/10;
min_error_lambda=lambda_min(b1);

disp(sprintf('Best choice of Fraction = %f',min_error_frac));
disp(sprintf('Best choice of Lambda = %f',min_error_lambda));
disp(sprintf('Minimum Error = %f',total_min_error));


rows=floor(row*min_error_frac);
train_in=input_data(1:rows,:);
test_in=input_data(rows+1:row,:);
train_out=output_data(1:rows,:);
test_out=output_data(rows+1:row,:);

weights=mylinridgereg(train_in ,train_out ,min_error_lambda);
predict_train=mylinridgeregeval(train_in, weights);
predict_test=mylinridgeregeval(test_in, weights);

figure                                  %Plotting Predicted Training vs actual values
plot(predict_train,train_out,'.')
xlabel('Predicted Values')
ylabel('Actual Values')
title('Training Set')
axis equal
xlim([0 20])
ylim([0 20])



figure                                          %Plotting Predicted Testing vs actual values

plot(predict_test,test_out,'.')
axis equal
title('Testing Set')
xlabel('Predicted Values')
ylabel('Actual Values')
xlim([0 20])
ylim([0 20])