function []=GenerateAClass(class_num,N,sz,mu,Sigma,width,height,plot_type,fID,class_char)

[X,Y]=meshgrid(1:width,1:height); % generate grid data on XOY plane
p=mvnpdf([X(:) Y(:)],mu,Sigma); % calculate joint probability density
p=reshape(p,size(X)); % reshape to according coordinates
% reshape to one row
p=(p(:))'; % p=[p11 p21 p31...p12 p22 p32...]

% generate effective points
% r(i) = (x_final-1)*height+y_final
r = discretize(rand(sz),[0 cumsum(p)]);
figure;histogram(r,0.5:width*height+0.5)
%histogram(r,40000:50000)
title(['r',num2str(class_num)]);

% calculate final result (x, y)s
width=int32(300); height=int32(300);
r=int32(r);x_final=zeros(1,N,'int32'); y_final=zeros(1,N,'int32');
for i=1:N
    % r(i) = (x_final-1)*height+y_final
    x_final(i)=r(i)/height+1;
    y_final(i)=mod(r(i),height);
end
figure;
plot(x_final,y_final,plot_type,'MarkerSize',4);
axis([1,width,1,height]);title('final data');

% save in file
for i=1:N
    fprintf(fID,'%d\t%d\t',x_final(i),y_final(i));
    fprintf(fID,class_char);
    fprintf(fID,'\r\n');
end