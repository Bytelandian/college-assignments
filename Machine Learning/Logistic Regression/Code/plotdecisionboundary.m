function [ ] = plotdecisionboundary(w, X, Y)
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
    %x=2
    %y=3
    for i=1:100
     %   a(i)=x;
      %  b(i)=y;
       % x=x+0.01;
      %  y=y+0.01;
      a(i)=7*i/100;
      b(i)=7*i/100;
    end
    for i=1:100
        for j=1:100
            test(i,j,1)=a(i);
            test(i,j,2)=b(j);
        end
    end
    %stest=featuretransform(test,3);
    for i=1:100
        for j=1:100
            aa=featuretransform([test(i,j,1) test(i,j,2)],3);
            g(i,j)=1/(1+exp(-aa*w ));
        end
    end
   contour(a,b,g',0.5)
end

