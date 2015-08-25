function [ ans ] = ma( a,b,c )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
if (a>b)
    if (a>c)
        ans= 1;
    elseif (c>a)
        ans= 3;
    end
else
    if (b>c)
        ans= 2;
    else
        ans= 3;
    end
end

end

