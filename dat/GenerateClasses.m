% Generate data of three classes in (x, y) mode.
% The data is normal and is saved in train.txt and test.txt.
% The ranges of data are coincident partly.
% Author: [yikouniao]( github.com/yikouniao )
% To watch the project, visit https://github.com/yikouniao/basic-surpervised-classifications

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

N3=300;
sz3 = [N3,1];
mu3=[210,100];
Sigma3=[40 2;2 40];

width=300; height=300; % range of final data
file_name='train.txt';

% save in file
fID = fopen(file_name,'w');

% a means class a, b means class b
GenerateAClass(1,N1,sz1,mu1,Sigma1,width,height,'.b',fID,'a');
GenerateAClass(2,N2,sz2,mu2,Sigma2,width,height,'.r',fID,'b');
GenerateAClass(3,N3,sz3,mu3,Sigma3,width,height,'.g',fID,'c');

fprintf(fID,'#'); % end of data
fclose(fID);