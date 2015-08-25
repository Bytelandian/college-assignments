function [w] = mylinridgereg(X, T, lambda)
    [m,n]=size(X);
    size(X);
    size(X');
    w=pinv(X' * X + ( lambda * ( eye (n) ))) ;
    w=w* ( X' * T);
end