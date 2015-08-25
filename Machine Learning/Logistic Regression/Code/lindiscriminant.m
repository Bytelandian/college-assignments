function [ output_args ] = lindiscriminant(input,output)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    [m,n]=size(input);
    features=n-1;
    counta=1;
    countb=1;
    b=[];
    a=[];
    for i=1:m
        if output(i)==1
            a(counta,:)=input(i,[2:features+1]);
            counta=counta+1;
        else
            b(countb,:)=input(i,[2:features+1]);
            countb=countb+1;
        end
    end
    counta=counta-1;
    countb=countb-1;
    p(1)=counta/(counta+countb);
    p(2)=countb/(counta+countb);

    for i=1:features
        m1(i)=mean(a(:,i));
    end

    s1=zeros(features);
    for j=1:counta
        s1=s1+(a(j,:)-m1)'*(a(j,:)-m1);
    end


    for i=1:features
        m2(i)=mean(b(:,i));
    end
    
    s2=zeros(features);
    for j=1:countb
        s2=s2+(b(j,:)-m2)'*(b(j,:)-m2);
    end
    
    s=(s1+s2)./98;
   
    for i=1:100
      xa(i)=7*i/100;
      yb(i)=7*i/100;
    end
    for i=1:100
        for j=1:100
            test(i,j,1)=xa(i);
            test(i,j,2)=yb(j);
        end
    end
    in=inv(s);
    for i=1:100
        for j=1:100
            aa=featuretransform([test(i,j,1) test(i,j,2)],3);
            aa=aa(:,[2:10]);
            
            g(i,j)=(aa*in*m1'-0.5*m1*in*m1'+log(p(1)))-(aa*in*m2'-0.5*m2*in*m2'+log(p(2)));
        end
    end
   contour(xa,yb,g',[0 0])
   
   
end

