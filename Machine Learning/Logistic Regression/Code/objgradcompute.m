function [objval gradval] = objgradcompute(w, X, Y,lambda)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
   objval=0;
   [m,n]=size(X);
   for i=1:m
       g(i)=1/(1+exp(-X(i,:)*w ));
       objval=objval+(Y(i)*(log(g(i)))+(1-Y(i))*log(1-g(i)));
   end
   objval=-objval/m+(lambda*norm(w)^2)/m;
   for i=1:n
       gradval(i)=0;
       for j=1:m
           gradval(i)=gradval(i)+(g(j)-Y(j))*X(j,i);
       end
       gradval(i)=gradval(i)/m+(lambda*norm(w)^2)/m;
   end
   
end


