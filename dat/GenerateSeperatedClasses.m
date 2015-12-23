% Generate data of three classes in (x, y) mode.
% Data is normal and is saved in train-seperated.txt and test-seperated.txt.
% The ranges of data are seperated totally.
% Author: [yikouniao]( github.com/yikouniao )
% To watch the project, visit https://github.com/yikouniao/basic-surpervised-classifications

clc
clear
close all

% 1 means class a, 2 means class b
% both data of two classes are generated normally.
% In this case, coordinate data of two classes is put closely.
% Thus a part of the borders of classes are overlapped.
N1=200; % quantity of points
sz1 = [N1,1]; % size of output random matrix
mu1=[100,100]; % mean vector
Sigma1=[40 2;2 40]; % Covariance matrix

N2=300;
sz2 = [N2,1];
mu2=[160,240];
Sigma2=[40 2;2 40];

N3=200;
sz3 = [N3,1];
mu3=[240,160];
Sigma3=[40 2;2 40];

width=300; height=300; % range of final data
file_name='test-seperated.txt';

% save in file
fID = fopen(file_name,'w');

% a means class a, b means class b
GenerateAClass(1,N1,sz1,mu1,Sigma1,width,height,'.b',fID,'a');
GenerateAClass(2,N2,sz2,mu2,Sigma2,width,height,'.r',fID,'b');
GenerateAClass(3,N3,sz3,mu3,Sigma3,width,height,'.g',fID,'c');

fprintf(fID,'#'); % end of data
fclose(fID);