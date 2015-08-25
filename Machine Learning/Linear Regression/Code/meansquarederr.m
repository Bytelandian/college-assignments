function [ error ] = meansquarederr(T, Tdash)
    error=sum((T-Tdash).^2);
    [row,col]=size(T);
     error=error/row;
end

