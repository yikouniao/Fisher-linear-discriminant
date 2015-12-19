% Generate data of two classes in (x, y) mode. Data is normal and is saved in train.txt and test.txt.
% Author: yikouniao ( github.com/yikouniao )
% To watch the project, visit github.com/yikouniao/basic-surpervised-classifications

clc
clear
close all

% 1 means class a, 2 means class b
% both data of two classes are generated normally.
% In this case, coordinate data of two classes is put closely.
% Thus a part of the borders of classes are overlapped.
N1=400; % quantity of points
sz1 = [N1,1]; % size of output random matrix
mu1=[150,150]; % mean vector
Sigma1=[40 2;2 40]; % Covariance matrix
N2=300;
sz2 = [N2,1];
mu2=[170,170];
Sigma2=[40 2;2 40];
width=300; height=300; % range of final data
file_name='test.txt';

[X1,Y1]=meshgrid(1:width,1:height); % generate grid data on XOY plane
p1=mvnpdf([X1(:) Y1(:)],mu1,Sigma1); % calculate joint probability density
p1=reshape(p1,size(X1)); % reshape to according coordinates
% reshape to one row
p1=(p1(:))'; % p=[p11 p21 p31...p12 p22 p32...]
[X2,Y2]=meshgrid(1:width,1:height);
p2=mvnpdf([X2(:) Y2(:)],mu2,Sigma2);
p2=reshape(p2,size(X2));
p2=(p2(:))';

% generate effective points
% r(i) = (x_final-1)*height+y_final
r1 = discretize(rand(sz1),[0 cumsum(p1)]);
figure;histogram(r1,0.5:width*height+0.5)
%histogram(r1,40000:50000)
title('r1');
r2 = discretize(rand(sz2),[0 cumsum(p2)]);
figure;histogram(r2,0.5:width*height+0.5)
title('r2');

% calculate final result (x, y)s
width=int32(300); height=int32(300);
r1=int32(r1);x_final1=zeros(1,N1,'int32'); y_final1=zeros(1,N1,'int32');
for i=1:N1
    % r(i) = (x_final-1)*height+y_final
    x_final1(i)=r1(i)/height+1;
    y_final1(i)=mod(r1(i),height);
end
r2=int32(r2);x_final2=zeros(1,N2,'int32'); y_final2=zeros(1,N2,'int32');
for i=1:N2
    x_final2(i)=r2(i)/height+1;
    y_final2(i)=mod(r2(i),height);
end
figure;
plot(x_final1,y_final1,'.b',x_final2,y_final2,'.r','MarkerSize',4);
axis([1,width,1,height]);title('final data');

% save in file
fID = fopen(file_name,'w');
for i=1:N1
    % a means class a
    fprintf(fID,'%d %d a\r\n',x_final1(i),y_final1(i));
end
for i=1:N2
    % b means class b
    fprintf(fID,'%d %d b\r\n',x_final2(i),y_final2(i));
end
fprintf(fID,'#'); % end of data
fclose(fID);