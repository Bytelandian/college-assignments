clear all
clc
x=zeros(30,1);
x([1:10],:)=normrnd(2,0.2,[10 1]);
x([1:10],:)=sort(x([1:10],:));
x([11:20],:)=normrnd(3,0.2,[10 1]);
x([11:20],:)=sort(x([11:20],:));
x([21:30],:)=normrnd(4,0.2,[10 1]);
x([21:30],:)=sort(x([21:30],:));

i=1;
test=[];
while i<=5.0
    test=[test i];
    i=i+0.1;
end
y=[0 0 0 0 0 0 0 0 0 0];
subplot(2,2,1)

plot(x([1:10],:),2,'ok','MarkerFaceColor','g');
hold on
plot(x([11:20],:),3,'ok','MarkerFaceColor','r');
hold on
plot(x([21:30],:),4,'ok','MarkerFaceColor','b');
xlabel('x')
ylabel('mean')
title('Color coded data')
%hold on
s=0;
mean(x([1:10],:));
s=norm(x([1:10],:)-mean(x([1:10],:)))^2+norm(x([11:20],:)-mean(x([11:20],:)))^2+norm(x([21:30],:)-mean(x([21:30],:)))^2;
s=s/27;

 for k=1:3    
     u(k)=mean(x([10*(k-1)+1:10*k],:));
 end
%     
%     for i=10*(k-1)+1:10*k
%         i
%         s=s+(x(i)-u(k))*(x(i)-u(k));
%     end
% end
% s=s/(27);
color(1)='r';
color(2)='b';
color(3)='g';

subplot(2,2,2)
for k=1:3
    for i=1:30
        h(k,i)=exp(-0.5*(x(i)-u(k))*inv(s)*(x(i)-u(k)))/(sqrt(2*pi*s));

    end
 %   h(:,[10*(k-1)+1:10*k])=sort(h(:,[10*(k-1)+1:10*k]))
    plot(x,h(k,:),color(k));
    
    hold on
end
title('Likelihood')
    ylabel('P(X = x | Y = k)')
    xlabel('x')
subplot(2,2,3)
for k=1:3
    for i=1:30
        p(k,i)=(h(k,i))/(h(1,i)+h(2,i)+h(3,i));
    end
    plot(x,p(k,:),color(k));
    hold on
end
ylabel('P(Y = k | X = x)');
title('posterior probability');
xlabel('x')

figure
subplot(2,2,1)
plot(x([1:10],:),2,'ok','MarkerFaceColor','g');
hold on
plot(x([11:20],:),3,'ok','MarkerFaceColor','r');
hold on
plot(x([21:30],:),4,'ok','MarkerFaceColor','b');
xlabel('x')
ylabel('mean')
title('Color coded data')


subplot(2,2,2)
for k=1:3
    for i=1:41
        d(k,i)=test(i)*inv(s)*u(k)-0.5*u(k)*inv(s)*u(k)+log(1.0/3.0);
    end
    plot(test,d(k,:),color(k))
    hold on
end
title('discriminant functions')
xlabel('x')
ylabel('LDA')

subplot(2,2,3)

for i=1:41
    cl(i)=ma(d(1,i),d(2,i),d(3,i));
    if (cl(i)==1)
        plot(test(i),d(1,i),'ok','MarkerFaceColor','g');
        hold on
    elseif (cl(i)==2)
        plot(test(i),d(2,i),'ok','MarkerFaceColor','r');
        hold on
    elseif (cl(i)==3)
        plot(test(i),d(3,i),'ok','MarkerFaceColor','b');
        hold on
    end
    hold on
end

title('class predicted')
xlabel('x')
ylabel('LDA')